# Minishell

e parser lit ce tableau et construit un t_operator* (AST).
Tu fais ça avec des fonctions récursives :

parse_and_or()  découpe par && et || top-level.

parse_pipeline_or_subshell()  détecte si c’est un ( … ) ou une suite de commandes séparées par |.

parse_pipeline()  construit une liste chaînée de t_exec_line pour chaque pipeline.

parse_command()  récupère WORDs + redirs et les range dans t_exec_line.

À chaque étape, tu crées le bon nœud t_operator :

si tu rencontres &&  new_binop(OP_AND, left, right)

si ||  new_binop(OP_OR, left, right)

si (...)  new_subshell(subtree)

sinon  new_leaf(pipeline)
