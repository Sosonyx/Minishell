/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:05:23 by fox               #+#    #+#             */
/*   Updated: 2025/10/03 13:26:46 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_redir_ptrs(t_ast_p ast, t_redir_p redir, t_redir_p *curr)
{
	if (!ast->leaf->redir)
		ast->leaf->redir = redir;
	else
		(*curr)->next = redir;
	*curr = redir;
	ast->leaf->r_in = redir->type & (R_IN | R_HDOC);
	ast->leaf->r_out = redir->type & (R_OUT | R_APPEND);
}

static void	config_redir(t_minishell_p shell, t_redir_p redir, t_build_var vars)
{
	if (redir->type == R_HDOC)
	{
		redir->limiter = ft_strdup(shell->tokens->tokens[vars.start + 1]->val);
		if (!redir->limiter)
			set_abort(shell, MEM_ERRMSG);
	}
	else
	{
		redir->target = ft_strdup(shell->tokens->tokens[vars.start + 1]->val);
		if (!redir->target)
			set_abort(shell, MEM_ERRMSG);
	}	
}

static void	set_redir_type(t_redir_p redir, t_token_p token)
{
	if (token->type == T_REDIR_IN)
		redir->type = R_IN;
	else if (token->type == T_REDIR_OUT)
		redir->type = R_OUT;
	else if (token->type == T_APPEND)
		redir->type = R_APPEND;
	else
		redir->type = R_HDOC;
}

static void	_build_redir(t_minishell_p shell, t_redir_p redir, t_token_p token, t_build_var *vars)
{
	set_redir_type(redir, token);
	config_redir(shell, redir, *vars);
	discard_token(shell, vars->start++);
	discard_token(shell, vars->start++);
}

int	build_redir(t_minishell_p shell, t_ast_p ast, t_build_var vars)
{
	t_redir_p	curr;
	t_redir_p	new;
	t_token_p	tok;

	while (vars.start <= vars.end && shell->tokens->tokens[vars.start])
	{
		tok = shell->tokens->tokens[vars.start];
		if (tok->type & (T_REDIR_IN | T_REDIR_OUT | T_APPEND | T_HEREDOC))
		{
			new = ft_calloc(1, sizeof(t_redir));
			if (new)
			{
				_build_redir(shell, new, tok, &vars);
				set_redir_ptrs(ast, new, &curr);
			}
			else
				return (set_abort(shell, MEM_ERRMSG), RETURN_FAIL);
		}
		else
			++vars.start;
	}
	return (shell->abort == false);
}
