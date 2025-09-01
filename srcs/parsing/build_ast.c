/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:10:20 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/01 11:38:51 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// j ai lexee (tokeniser), ensuite j ai check les erreurs de syntax, 
// mtn je dois parser pour definir si les element sont des REDIR-IN etc ...

static void	create_node(t_ast_p ast, t_token_p token)
{
	if (token->type == T_WORD)
		;		
	else if (token->type == T_PIPE)
		;
	else if (token->type == T_REDIR_IN)
		;
	else if (token->type == T_REDIR_OUT)
		;
	else if (token->type == T_APPEND)
		;
	else if (token->type == T_HEREDOC)
		;
	else if (token->type == T_AND)
		;
	else if (token->type == T_OR)
		;
	else if (token->type == T_LPARENT)	
		;
	else if (token->type == T_RPARENT)	
		;
	else if (token->type == T_EXPAND)	
		;
}

static void	parse_tokens(t_ast_p ast, t_arg_p tok_container)
{
	t_token_p	*tokens;
	t_token_p	cur_token;

	tokens = tok_container->tokens;
	while (*tokens)
	{
		cur_token = *tokens;
		if (cur_token->val)								// null terminated
			printf("%s\n", cur_token->val);
		tokens++;
	}
}

t_error_status	build_ast(t_ast_p ast, t_arg_p tok_container)
{
	ast = ft_calloc(1, sizeof(t_ast));
	if (ast)
	{
		parse_tokens(ast, tok_container);
	}
	else
	{
		return (free(tok_container), RETURN_FAIL);
	}
	return (RETURN_OK);
}
