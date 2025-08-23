/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:57:45 by ihadj             #+#    #+#             */
/*   Updated: 2025/08/23 19:13:43 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>
#include <string.h>

int ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

int is_blank_line(const char *s)
{
	while (*s)
	{
		if (!ft_isspace((unsigned char)*s))
			return (0);
		s++;
	}
	return (1);
}
/*
	Gere le CTRL C, reaffiche un prompt clean
	A utiliser que dans le PARENT
	Dans l enfant : signal(SIGINT, SIG_DFL);
					signal(SIGQUIT, SIG_DFL);
*/
void sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

char *ft_strcat(char *dest, const char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i])
		i++;
	j = 0;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

static int count_word(const char *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
		while (str[i] && str[i] == c)
			i++;
	}
	return (count);
}

static int is_special(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

static char *ft_strndup(const char *s, size_t len)
{
	char *dup;
	size_t i;

	if (!s)
		return (NULL);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static int skip_quotes(const char *line, int i)
{
	char quote;

	quote = line[i++];
	while (line[i] && line[i] != quote)
		i++;
	if (line[i] == quote)
		i++;
	return (i);
}

static int count_tokens(char *line)
{
	int i;
	int start;
	int words;
	char quote;

	i = 0;
	start = 0;
	words = 0;
	if (!line || !line[0])
		return (0);
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (!line[i])
			break;
		if (is_special(line[i]))
		{
			words++;
			i++;
		}
		else if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				i++;
			if (line[i] == quote)
				i++;
			words++;
		}
		else
		{
			while (line[i] && !ft_isspace(line[i]) && !is_special(line[i]) && line[i] != '\'' && line[i] != '"')
				i++;
			words++;
		}
	}
	return (words);
}

t_token	*create_token(const char *val, t_toktype type, bool sq, bool dq)
{
	t_token *tok;
	
	tok = malloc(sizeof(t_token));
	if (!tok)
		return NULL;
	tok->val = val;
	tok->type = type;
	tok->was_single_quoted = sq;
	tok->was_double_quoted = dq;
	return (tok);
}

t_toktype	get_token_type(const char *line)
{
	if (!line)
		return (T_WORD);
	if (line[0] == '|')
		return (T_PIPE);
	if (line[0] == '<' && line[1] == '<')
		return (T_HEREDOC);
	if (line[0] == '>' && line[1] == '>')
		return (T_APPEND);
	if (line[0] == '<')
		return (T_REDIR_IN);
	if (line[0] == '>')
		return (T_REDIR_OUT);
	return (T_WORD);
}

static void skip_spaces(const char *line, int *i)
{
	while (line[*i] && ft_isspace((unsigned char)line[*i]))
		(*i)++;
}

static int	special_len(const char *line, int i)
{
	if (line[i] == '<')
	{
		if (line[i + 1] == '<')
			return (2);
		return (1);
	}
	else if (line[i] == '>')
	{
		if (line[i + 1] == '>')
			return (2);
		return (1);
	}
	return (1);
}


static int stock_special(t_token **arr, int j, const char *line, int *i)
{
	int len;
	
	len = special_len(line, *i);
	arr[j++] = create_token(ft_strndup(&line[*i], (size_t)len), \
				get_token_type(&line[*i]), false, false);
	*i += len;
	return (j);
}

// Retourne -1 si quotes non fermees
static int stock_quoted(t_token **arr, int j, const char *line, int *i)
{
	char	quote;
	int		start;

	quote = line[*i];
	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (!line[*i])
		return (-1);
	arr[j++] = create_token(ft_strndup(&line[start], (size_t)(*i - start)), \
				T_WORD, (quote == '\''), (quote == '"'));
	(*i)++;
	return (j);
}

static int stock_word(t_token **arr, int j, const char *line, int *i)
{
	int start;
	
	start = *i;
	while (line[*i] && !ft_isspace((unsigned char)line[*i]) \
			&& !is_special(line[*i]) && line[*i] != '\'' && line[*i] != '"')
		(*i)++;
	arr[j++] = create_token(ft_strndup(&line[start], (size_t)(*i - start)), \
				T_WORD, false, false);
	return (j);
}

int	fill_tokens(t_token **arr, char *line)
{
	int i = 0;
	int j = 0;

	while (line[i])
	{
		skip_spaces(line, &i);
		if (!line[i])
			break ;
		if (is_special(line[i]))
			j = stock_special(arr, j, line, &i);
		else if (line[i] == '\'' || line[i] == '"')
		{
			j = stock_quoted(arr, j, line, &i);
			// if (j < 0) // quotes non fermees
			// 	return (-1);
		}
		else
			j = stock_word(arr, j, line, &i);
	}
	arr[j] = NULL;
	return (j);
}

int stock_tokens(t_arg *a, char *line)
{
	int words;
	
	words = count_tokens(line);
	a->cmds = malloc(sizeof(t_token *) * (words + 1));
	if (!a->cmds)
		return (0);
	return (fill_tokens(a->cmds, line));
}

// int check_syntax(t_arg *a)
// {
	
// }

static void print_tab(t_arg a)
{
	int i;

	i = -1;
	while ((a.cmds)[++i])
	{
		printf("TOKEN_value = [%s] ------- TOKEN_type == [%d]\nDQuoted = [%d]\n", (a.cmds)[i]->val, (a.cmds)[i]->type, (a.cmds)[i]->was_double_quoted);
		printf("======================================================================\n");
	}
}

static void free_array(char **arr)
{
	int i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
}

int main(int ac, char **av, char **env)
{
	char *line;

	// (void)ac;
	// (void)av;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);

	while (1)
	{
		line = readline("\001\033[48;5;57m\002minishell>\001\033[0m\002 ");
		if (!line)
		{
			printf("exit\n");
			break;
		}
		if (!is_blank_line(line))
			add_history(line);
		t_arg elem;
		stock_tokens(&elem, line);
		print_tab(elem);
		// free_array(elem.cmds);
		free(line);
	}
	rl_clear_history();
	return (0);
}