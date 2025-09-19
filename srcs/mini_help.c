#include "minishell.h"

#define R   "\033[1;31m"
#define G   "\033[1;32m"
#define Y   "\033[1;33m"
#define B   "\033[1;34m"
#define M   "\033[1;35m"
#define C   "\033[1;36m"
#define W   "\033[1;37m"
#define E   "\033[0m"   // reset
#define CV  "\033[46m"  // fond cyan
#define CR  "\033[41m"  // fond rouge

void minishell_help(void)
{
    printf("\n");
    ft_putstr_fd(CV "                       " CR ">>>"
                 G " Minishell Help " R "<<<" E "\n\n", 2);

    printf(C "Usage: " E W "./minishell [options]" E "\n\n");

    printf(Y "Options:\n" E);
    printf(G "  --help          " E "Show this help message\n");
    printf(G "  -c <command>    " E "Execute command string without prompt\n");
    printf(G "  -v, --version   " E "Show version info\n\n");

    printf(Y "Builtins supported:\n" E);
    printf(G "  echo            " E "Print arguments to stdout\n");
    printf(G "  cd              " E "Change the current working directory\n");
    printf(G "  pwd             " E "Print current working directory\n");
    printf(G "  export          " E "Set environment variables\n");
    printf(G "  unset           " E "Unset environment variables\n");
    printf(G "  env             " E "Print environment variables\n");
    printf(G "  exit            " E "Exit the shell\n\n");

    printf(Y "Notes:\n" E);
    printf("  • " C "Use " W "Ctrl+D" E " to exit\n");
    printf("  • " C "Signals: " W "Ctrl+C" E " interrupts foreground job\n");
    printf("  • " C "Operators: " W "pipes, redirections, &&, ||, ()" E " supported\n\n");

    printf(CV "======================================================" E "\n\n");
}

