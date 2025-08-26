#ifndef MINISHELL_STRUCTURES_ENUMS_H
# define MINISHELL_STRUCTURES_ENUMS_H

# include "minishell.h"

/********************************************************************************/
/*            Enums                                                                */
/********************************************************************************/

enum e_toktype
{
    T_WORD,
    T_PIPE,
    T_REDIR_IN,
    T_REDIR_OUT,
    T_APPEND,
    T_HEREDOC,
    T_AND,
    T_OR,
    T_LPARENT,
    T_RPARENT,
    T_EXPAND,
};

enum e_redirtype
{
    R_IN,
    R_OUT,
    R_APPEND,
    R_HDOC
};

enum e_optype
{
    // OP_PIPE,
    OP_AND,
    OP_OR,
    OP_SUBSHELL
};

/********************************************************************************/
/*            Structures                                                            */
/********************************************************************************/

struct s_token
{
    t_toktype        type;
    char            *val;
    bool            was_single_quoted;         // pour heredoc (si delim etait quote)
    bool            was_double_quoted;         // on autorise l expansion
    bool            expandable; 
};

typedef struct s_redir
{
    t_redirtype            type;
    char                *target;
    struct s_redir        *next;
}    t_redir;

typedef struct s_exec_line
{
    char                **cmd_plus_args;
    t_redir                *redirs; // tableau de redirs in et de redirs out 
    struct s_exec_line    *next; // pointeur vers le bloc suivant  a executer 
    bool                is_builtin;    /* 0/1 ou petit enum */
}    t_exec_line;

typedef struct s_operator
{
    t_optype type;
    union
    {
        struct { struct s_operator *left; struct s_operator *right; } binop; //binary operation (OR et AND)
        struct { struct s_operator *child; } subshell;
        struct { t_exec_line *pipeline; } leaf;
    } u;
} t_operator;

#endif