/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:06:53 by fox               #+#    #+#             */
/*   Updated: 2025/10/03 17:03:21 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_tok_word(t_tok_container_p tok_container, int i, int end)
{
	int			words;
	t_token_p	tok;

	words = 0;
	tok = tok_container->tokens[i];
	while (i <= end)
	{
		tok = tok_container->tokens[i];			
		if (tok_container->tokens[i] && tok->type == T_WORD)
			words++;
		i++;
	}
	return (words);
}

static void	_build_cmd(t_minishell_p shell, t_ast_p ast, t_token_p	*tok, t_build_var *vars)
{
	ast->leaf->cmds[vars->i] = ft_strdup((*tok)->val);
	if (!ast->leaf->cmds[vars->i++])
		set_abort(shell, MEM_ERRMSG);
	free((*tok)->val);
	free(*tok);
	shell->tokens->tokens[vars->start] = NULL;
}

int	build_cmd(t_minishell_p shell, t_ast_p ast, t_build_var vars)
{
	int			words;
	t_token_p	tok;

	words = count_tok_word(shell->tokens, vars.start, vars.end);
	ast->leaf->cmds = ft_calloc(words + 1, sizeof(char *));
	if (ast->leaf->cmds)
	{
		vars.i = 0;
		while (vars.start <= vars.end)
		{
			tok = shell->tokens->tokens[vars.start];
			if (tok && tok->type == T_WORD)
				_build_cmd(shell, ast, &tok, &vars);
			if (!is_no_abort(shell))
				return (RETURN_FAIL);
			++vars.start;
		}
		return (RETURN_OK);
	}
	else
		return (set_abort(shell, MEM_ERRMSG), RETURN_FAIL);
}
