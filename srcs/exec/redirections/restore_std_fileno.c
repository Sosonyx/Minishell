#include "minishell.h"

void restore_std_fileno(t_minishell_p shell, t_ast_p ast)
{
    dup2(shell->std_fds[0], STDIN_FILENO);
    dup2(shell->std_fds[1], STDOUT_FILENO);
    close_secure(&shell->std_fds[0]);
    close_secure(&shell->std_fds[1]);
    close_fds(ast, PARENT);
}
