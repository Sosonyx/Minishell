#include "minishell.h"

void save_std_fileno(t_minishell_p shell)
{
    shell->std_fds[0] = dup(STDIN_FILENO);
    shell->std_fds[1] = dup(STDOUT_FILENO);
}   
