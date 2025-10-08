/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_leaf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:50:56 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/07 17:02:32 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_shell *shell, char *name)
{
	int		i;
	size_t	len;

	len = ft_strlen(name);
	i = 0;
	while (shell->environ[i])
	{
		if (!ft_strncmp(shell->environ[i], name, len) && \
		shell->environ[i][len] == '=')
			return (ft_strdup(shell->environ[i] + len + 1));
		i++;
	}
	return (NULL);
}

static char	**ft_join_array(char **tab1, char **tab2)
{
	int		len1;
	int		len2;
	char	**res;
	int		i;

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
	i = -1;
	while (++i < len2)
	{
		res[len1 + i] = ft_strdup(tab2[i]);
		if (!res[len1 + i])
			return (NULL);
	}
	return (res[len1 + len2] = NULL, res);
}

char	**commands_expand(t_shell *shell, char **cmds)
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
		exp = expand_command(shell, cmds[i]);
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

void	pipeline_expand(t_shell *shell, t_ast_p ast)
{
	char		**new_cmds;
	t_redir_p	new_redirs;

	new_cmds = commands_expand(shell, ast->leaf->cmds);
	ft_split_free(ast->leaf->cmds);
	ast->leaf->cmds = new_cmds;
	new_redirs = _redirs_expand(shell, ast->leaf->redir);
	free_redirs(ast->leaf->redir);
	ast->leaf->redir = new_redirs;
}
