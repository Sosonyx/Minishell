/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:59:35 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/07 16:59:49 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_exit_status(t_shell *shell, char *result)
{
	char	*status;
	char	*tmp;

	status = ft_itoa(extract_return_code(shell->exit_code));
	if (!status)
		return (NULL);
	tmp = ft_strjoin(result, status);
	free(result);
	free(status);
	return (tmp);
}

char	*expand_variable(t_shell *shell, char *str, int *i, char *result)
{
	int		j;
	char	*var_name;
	char	*var_value;
	char	*tmp;

	j = *i + 1;
	while ((ft_isalnum(str[j]) || str[j] == '_') && \
	str[j] != '"' && str[j] != '\'')
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

char	*append_char(char *str, char c)
{
	size_t	len;
	char	*res;
	size_t	i;

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

void	exp_case(t_shell_p shell, char *str, t_expanded *result, int *i)
{
	if (str[*i + 1] == '?')
	{
		(*result).value = expand_exit_status(shell, (*result).value);
		(*i)++;
	}
	else if (ft_isalpha(str[*i + 1]) || str[*i + 1] == '_')
		(*result).value = expand_variable(shell, str, i, (*result).value);
	else
		(*result).value = append_char((*result).value, str[*i]);
}
