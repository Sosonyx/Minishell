/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_leaf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:04:07 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/10 12:28:21 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir_p	build_redir(t_tok_container_p tok_container, int i, int end)
{
	t_redir_p	head;
	t_redir_p	curr;
	t_redir_p	new;
	t_token_p	tok;

	head = NULL;
	curr = NULL;
	while (i <= end && tok_container->tokens[i])
	{
		tok = tok_container->tokens[i];
		if (tok->type == T_REDIR_IN || tok->type == T_REDIR_OUT
			|| tok->type == T_APPEND || tok->type == T_HEREDOC)
		{
			new = ft_calloc(1, sizeof(t_redir));
			if (!new)
				return (head);
			if (tok->type == T_REDIR_IN)
				new->type = R_IN;
			else if (tok->type == T_REDIR_OUT)
				new->type = R_OUT;
			else if (tok->type == T_APPEND)
				new->type = R_APPEND;
			else
				new->type = R_HDOC;
			if (new->type == R_HDOC)
				new->limiter = ft_strdup(tok_container->tokens[i + 1]->val);
			else
				new->target = ft_strdup(tok_container->tokens[i + 1]->val);
			free(tok_container->tokens[i]);
			tok_container->tokens[i] = NULL;
			free(tok_container->tokens[i + 1]);
			tok_container->tokens[i + 1] = NULL;
			if (!head)
				head = new;
			else
				curr->next = new;
			curr = new;
			i += 2;
			continue ;
		}
		i++;
	}
	return (head);
}

static int	count_tok_word(t_tok_container_p tok_container, int i, int end)
{
	int			words;
	t_token_p	tok;

	words = 0;
	tok = tok_container->tokens[i];	
	while (i <= end && tok_container->tokens[i])
	{
		tok = tok_container->tokens[i];			
		if (tok->type == T_WORD)
			words++;
		i++;			
	}
	return (words);
}

static t_return_status	build_cmd(char ***cmd, t_tok_container_p tok_container, int start, int end)
{
	int			words;
	int			j;
	int			i;
	t_token_p	tok;

	words = count_tok_word(tok_container, start, end);
	*cmd = ft_calloc(words + 1, sizeof(char *));
	if (!*cmd)
		return (RETURN_FAIL);
	j = 0;
	i = start;
	while (i <= end)
	{
		tok = tok_container->tokens[i];
		if (tok && tok->type == T_WORD)
		{
			(*cmd)[j++] = ft_strdup(tok->val);
			free(tok->val);
			free(tok);
			tok_container->tokens[i] = NULL;
		}
		i++;
	}
	return (RETURN_OK);
}

t_return_status	create_leaf(t_ast_p *ast, t_tok_container_p tok_container, int start, int end)
{
	*ast = ft_calloc(1, sizeof(t_ast));
	if (!*ast)
		return (RETURN_FAIL);
	(*ast)->leaf = ft_calloc(1, sizeof(struct s_leaf));
	if (!(*ast)->leaf)
		return (RETURN_FAIL);
	(*ast)->leaf->pipefd[0] = -2;
	(*ast)->leaf->pipefd[1] = -2;
	(*ast)->leaf->fds[0] = -2;
	(*ast)->leaf->fds[1] = -2;
	(*ast)->leaf->redir = build_redir(tok_container, start, end);
	build_cmd(&(*ast)->leaf->cmds, tok_container, start, end);
	return (RETURN_OK);
}
