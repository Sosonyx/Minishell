/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_old_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:45:36 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/07 18:16:22 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_state(int state, char c, t_expanded *exp)
{
	state = quote_state(state, c);
	
	if (exp && state)
			exp->split_allowed = 0;
	return (state);
}

static char	*expand_exit_status(t_shell *shell, char *result)
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

static char	*expand_variable(t_shell *shell, char *str, int *i, char *result)
{
	int		j;
	char	*var_name;
	char	*var_value;
	char	*tmp;

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

static void	exp_case(t_shell_p shell, char *str, t_expanded *result, int *i)
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

static int	has_a_star(int state, char *str, int i)
{
	if (state == 0)
	{
		if (i > 0)
			i--;
		while (i > 0 && str[i] != '\'' && str[i] != '"')
		{
			if (str[i] == '*')
				return (1);
			i--;
		}
	}
	else
	{
		i++;
		while (str[i])
		{
			if ((state == 1 && str[i] == '\'') || (state == 2 && str[i] == '"'))
				break ;
			if (str[i] == '*')
				return (1);
			i++;
		}
	}
	return (0);
}

t_expanded	expand_command(t_shell *shell, char *str)
{
	int			i;
	int			state;
	int			new_state;
	t_expanded	result;

	result.value = ft_strdup("");
	result.split_allowed = 1;
	if (!result.value)
		return (result);
	state = 0;
	i = 0;
	while (str && str[i])
	{
		while (str && str[i])
		{
			new_state = update_state(state, str[i], &result);
			if (new_state != state)
			{
				state = new_state;
				if (has_a_star(state, str, i))
					result.value = append_char(result.value, str[i]);
			}
			else if (str[i] == '$' && state != 1)
				exp_case(shell, str, &result, &i);
			else
				result.value = append_char(result.value, str[i]);
			if (!result.value)
				return (result);
			i++;
		}
	}
	return (result);
}
