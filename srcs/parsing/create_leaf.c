/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_leaf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:04:07 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/03 18:48:26 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir_p	build_redir(t_tok_container_p tok_container, int i)
{
	t_redir_p	head;
	t_redir_p	curr;
	t_redir_p	new;
	t_token_p	tok;

	head = NULL;
	curr = NULL;
	while (tok_container->tokens[i]
		&& !is_control_op(tok_container->tokens[i]->type))
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
			new->target = ft_strdup(tok_container->tokens[i + 1]->val);
			// if (tok->type == T_HEREDOC)
			// 	new->quoted = tok_container->tokens[i + 1]->was_single_quoted;
			free(tok_container->tokens[i]);
			free(tok_container->tokens[i]->val);
			tok_container->tokens[i] = NULL;
			free(tok_container->tokens[i + 1]);
			free(tok_container->tokens[i + 1]->val);
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

static int	count_tok_word(t_tok_container_p tok_container, int i)
{
	int			words;
	t_token_p	tok;

	words = 0;
	tok = tok_container->tokens[i];	
	while (tok_container->tokens[i])
	{
		tok = tok_container->tokens[i];			
		if (tok->type == T_WORD)
			words++;
		i++;			
	}
	return (words);
}

static t_error_status	build_cmd(char ***cmd, t_tok_container_p tok_container, int i)
{
	t_token_p	tok;
	int			words;
	int			j;
	
	j = 0;
	*cmd = ft_calloc((count_tok_word(tok_container, i) + 1), sizeof(char *));
	if (!*cmd)
		return (RETURN_FAIL);
	tok = tok_container->tokens[i];
	while (tok && (tok->type == T_REDIR_IN || tok->type == T_REDIR_OUT \
		|| tok->type == T_APPEND || tok->type == T_HEREDOC || tok->type == T_WORD))
	{
		if (tok->type == T_REDIR_IN || tok->type == T_REDIR_OUT \
		|| tok->type == T_APPEND || tok->type == T_HEREDOC)
			i += 2;
		else
		{
			(*cmd)[j] = ft_strdup(tok->val);
			free(tok);
			tok_container->tokens[i] = NULL;
			// if (!cmd[j])
			// 	free ;
			i++;
			j++;
		}
		tok = tok_container->tokens[i];
	}
	(*cmd)[j] = NULL;
	return (RETURN_OK);
}

t_error_status	create_leaf(t_ast_p *ast, t_tok_container_p tok_container, int i)
{
	*ast = ft_calloc(1, sizeof(t_ast));
	(*ast)->leaf = ft_calloc(1, sizeof(struct s_leaf));
	if (!(*ast)->leaf)
		return (RETURN_FAIL);
	(*ast)->leaf->redir = build_redir(tok_container, i);
	build_cmd(&(*ast)->leaf->cmds, tok_container, i);
	// leaf->is_builtin =;

	return (RETURN_OK);
}
