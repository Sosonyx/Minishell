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

void	ft_free_split(char **arr)
{
	int i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

static char    *get_env_value(t_minishell *shell, char *name)
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
static int	update_state(int state, char c, t_expanded *exp)
{
	if (c == '\'' && state == 0)
		return (1);
	else if (c == '\'' && state == 1)
		return (0);
	else if (c == '"' && state == 0)
	{
		exp->split_allowed = 0;
		return (2);
	}
	else if (c == '"' && state == 2)
		return (0);
	return (state);
}

static char	*expand_exit_status(t_minishell *shell, char *result)
{
	char	*status;
	char	*tmp;

	status = ft_itoa(extract_return_code(shell->last_status));
	if (!status)
		return (NULL);
	tmp = ft_strjoin(result, status);
    free(result);
	free(status);
	return (tmp);
}

static char *expand_variable(t_minishell *shell, char *str, int *i, char *result)
{
    int     j;
    char    *var_name;
    char    *var_value;
    char    *tmp;

    j = *i + 1;
    while ((ft_isalnum(str[j]) || str[j] == '_') && str[j] != '"' && str[j] != '\'')
        j++;
    var_name = ft_substr(str, *i + 1, j - (*i + 1));
    if (!var_name)
        return (NULL);
    var_value = get_env_value(shell, var_name);
    free(var_name);
    if (!var_value)
        var_value = ft_strdup("");
    tmp = ft_strjoin(result, var_value);
    free(result);
    free(var_value);
    if (!tmp)
        return (NULL);
    *i = j - 1;
    return (tmp);
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

static char    *append_char(char *str, char c)
{
    size_t  len;
    char    *res;
    size_t  i;

    if (!str)
        return (NULL);
    len = ft_strlen(str);
    res = malloc(len + 2);
    if (!res)
        return (NULL);
    i = 0;
    while (i < len)
    {
        res[i] = str[i];
        i++;
    }
    res[len] = c;
    res[len + 1] = '\0';
    free(str);
    return (res);
}

static t_expanded expand_old_cmd(t_minishell *shell, char *str)
{
    int         i;
    int         state;
    int         new_state;
    t_expanded  result;

    result.value = ft_strdup("");
    result.split_allowed = 1;
    if (!result.value)
        return (result);
    state = 0;
    i = 0;
    while (str[i])
    {
        new_state = update_state(state, str[i], &result);
        if (new_state != state)
            state = new_state;
        else if (str[i] == '$' && state != 1)
        {
            if (str[i + 1] == '?')
            {
                result.value = expand_exit_status(shell, result.value);
                i++;
            }
            else if (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
                result.value = expand_variable(shell, str, &i, result.value);
            else
                result.value = append_char(result.value, str[i]);
        }
        else
            result.value = append_char(result.value, str[i]);
        // if (!result.value)
        //     return (result);
        i++;
    }
    return (result);
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
            return (ft_free_split(new_cmds), NULL);
        if (exp.split_allowed == true)
            splitted = ft_split(exp.value, ' ');
        else
            splitted = ft_split(exp.value, '\0');
        free(exp.value);
        tmp = ft_join_array(new_cmds, splitted);
        ft_free_split(new_cmds);
        ft_free_split(splitted);
        new_cmds = tmp;
        i++;
    }
    return (new_cmds);
}
