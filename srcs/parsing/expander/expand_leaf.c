/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:50:56 by ihadj             #+#    #+#             */
/*   Updated: 2025/08/25 13:51:42 by ihadj            ###   ########.fr       */
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
        res[i] = ft_strdup(tab1[i]);
    j = -1;
    while (++j < len2)
        res[len1 + j] = ft_strdup(tab2[j]);
    res[len1 + len2] = NULL;
    return (res);
}

char	**expand_leaf(t_minishell *shell, char **cmds)
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
            splitted = ft_split(exp.value, '\0');
        free(exp.value);
        tmp = ft_join_array(new_cmds, splitted);
        ft_split_free(new_cmds);
        ft_split_free(splitted);
        new_cmds = tmp;
        i++;
    }
    return (new_cmds);
}
