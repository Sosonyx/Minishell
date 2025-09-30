/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_leaf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:50:56 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/30 15:45:22 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *get_env_value(t_minishell *shell, char *name)
{
    int     i;
    size_t  len;

    len = ft_strlen(name);
    i = 0;
    while (shell->environ[i])
    {
        if (!ft_strncmp(shell->environ[i], name, len)
            && shell->environ[i][len] == '=')
            return (ft_strdup(shell->environ[i] + len + 1));
        i++;
    }
    return (NULL);
}

static char    **ft_join_array(char **tab1, char **tab2)
{
    int     len1;
    int     len2;
    char    **res;
    int     i;
    int     j;

    len1 = get_array_size(tab1);
    len2 = get_array_size(tab2);
    res = malloc(sizeof(char *) * (len1 + len2 + 1));
    if (!res)
        return (NULL);
    i = -1;
    while (++i < len1)
    {
        res[i] = ft_strdup(tab1[i]);
        if (!res[i])
            return (NULL);
    }
    j = -1;
    while (++j < len2)
    {
        res[len1 + j] = ft_strdup(tab2[j]);
        if (!res[len1 + j])
            return (NULL);
    }
    res[len1 + len2] = NULL;
    return (res);
}

char	**_variable_expand(t_minishell *shell, char **cmds)
{
    char		**new_cmds;
    char		**tmp;
    char		**splitted;
    t_expanded	exp;
    int			i;

    new_cmds = ft_calloc(1, sizeof(char *));
    if (!new_cmds)
        return (NULL);
    i = 0;
    while (cmds[i])
    {
        exp = expand_old_cmd(shell, cmds[i]);
        if (!exp.value)
            return (ft_split_free(new_cmds), NULL);
        if (exp.split_allowed == true)
            splitted = ft_split(exp.value, ' ');
        else
        {
            splitted = malloc(sizeof(char *) * 2);
            if (!splitted)
            {
                free(exp.value);
                return (ft_split_free(new_cmds), NULL);
            }
            splitted[0] = ft_strdup(exp.value);
            if (!splitted[0])
            {
                free(splitted);
                free(exp.value);
                return (ft_split_free(new_cmds), NULL);
            }
            splitted[1] = NULL;
        }
        free(exp.value);
        tmp = ft_join_array(new_cmds, splitted);
        ft_split_free(new_cmds);
        ft_split_free(splitted);
        new_cmds = tmp;
        i++;
    }
    return (new_cmds);
}

static void free_redirs(t_redir_p list)
{
    t_redir_p tmp;
    while (list)
    {
        tmp = list->next;
        free(list->target);
        free(list->limiter);
        free(list);
        list = tmp;
    }
}

t_redir_p	_redirs_expand(t_minishell *shell, t_redir_p redirs)
{
	t_redir_p	head;
	t_redir_p	curr;
	t_redir_p	new;
    char		**splitted;
    t_expanded	exp;
    int         i;

	head = NULL;
	curr = NULL;
	while (redirs)
	{
        exp = expand_old_cmd(shell, redirs->target);
        if (!exp.value)
            return (free_redirs(head), NULL);
        if (exp.split_allowed == true)
            splitted = ft_split(exp.value, ' ');
        else
            splitted = ft_split(exp.value, '\0');
        free(exp.value);
        i = 0;
        while (splitted[i])
        {
            new = ft_calloc(1, sizeof(t_redir));
            if (!new)
            {
                ft_split_free(splitted);
                return (free_redirs(head), NULL);
            }
            new->type = redirs->type;
            new->target = ft_strdup(splitted[i]);
            if (redirs->limiter)
                new->limiter = ft_strdup(redirs->limiter);
            new->fd = redirs->fd;
            new->next = NULL;
            
            if (!head)
                head = new;
            else
                curr->next = new;
            curr = new;
            i++;
        }
        ft_split_free(splitted);
		redirs = redirs->next;
    }
	return (head);
}

void	variable_expand(t_minishell *shell, t_ast_p ast)
{
	char	**new_cmds;
	t_redir_p new_redirs;
	
	new_cmds = _variable_expand(shell, ast->leaf->cmds);
	ft_split_free(ast->leaf->cmds);
    ast->leaf->cmds = new_cmds;

	new_redirs = _redirs_expand(shell, ast->leaf->redir);
	free_redirs(ast->leaf->redir);
	ast->leaf->redir = new_redirs;
}
