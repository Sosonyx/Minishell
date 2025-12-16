<h1>Minishell Project</h1>

  <p align="center">
    For further information about 42cursus and its projects, see <a href="https://42.fr/le-campus-de-paris/diplome-informatique/"><b>42school</b></a>.
  </p>
  
  <p>
    <img src="https://img.shields.io/badge/language-C-blue?style=for-the-badge" />
    <img src="https://img.shields.io/github/repo-size/Sosonyx/minishell?style=for-the-badge&logo=github">
    <img src="https://img.shields.io/github/languages/count/Sosonyx/minishell?style=for-the-badge" />
    <img src="https://img.shields.io/github/languages/top/Sosonyx/minishell?style=for-the-badge" />
    <img src="https://img.shields.io/github/last-commit/Sosonyx/minishell?style=for-the-badge" />
  </p>

 <div align="center" style="font-size:1.3em; line-height:2;">
  <span><a href="#about-project" style="text-decoration:none; color:inherit;">📜 About Project</a></span>
  &nbsp;&bull;&nbsp;
  <span><a href="#mandatory-part" style="text-decoration:none; color:inherit;">🔷 Mandatory Part</a></span>
  &nbsp;&bull;&nbsp;
  <span><a href="#bonus-part" style="text-decoration:none; color:inherit;">🌟 Bonus Part</a></span>
  &nbsp;&bull;&nbsp;
  <span><a href="#usage" style="text-decoration:none; color:inherit;">👨‍💻 Usage</a></span>
</div>

</div>

## <a name="about-project"></a>📜 About Project

> 42 School Minishell project: Create a minimal shell implementation inspired by **bash**.  
> Learn **command parsing**, **process execution**, **file descriptors**, and **signal handling**.

**Contributors** : Cricriiii

```
🚀 TL;DR: Build a Unix shell from scratch.  
- Parse user input and command pipelines.  
- Execute external commands and built-ins.  
- Handle redirections (>, <, >>, <<).  
- Manage environment variables and signals.
```
> [!NOTE]    
> - Norminette compliant C code.  
> - Functions ≤ 25 lines.  
> - Only allowed functions.

---

## <a name="mandatory-part"></a>🔷 Mandatory Part

A **fully functional shell** supporting:

### Core Features
- **Command Parsing**: Parse user input into tokens and commands
- **Command Execution**: Execute external programs using `execve()`
- **Pipelines**: Connect multiple commands with pipes (`|`)
- **Redirections**:
  - Output redirection: `>` (overwrite) and `>>` (append)
  - Input redirection: `<` (read from file)
  - Here-document: `<<` (read from stdin until delimiter)
- **Built-in Commands**:
  - `echo` with `-n` flag
  - `cd` with relative/absolute paths
  - `pwd` - print working directory
  - `export` - add/modify environment variables
  - `unset` - remove environment variables
  - `env` - display environment
  - `exit` - exit the shell with optional status code
- **Environment Variables**: Access via `$VAR` or `$?` (last exit status)
- **Signal Handling**: Handle `CTRL+C` (SIGINT) and `CTRL+D` (EOF)

### Program Behavior
```
The shell displays a prompt and waits for user input.
User types a command or pipeline with optional redirections.
Shell parses, executes, and displays results.
Process repeats until user exits.
```

### Example Usage
```bash
$ minishell
minishell> ls -la | grep .c
minishell> cat < file.txt > output.txt
minishell> echo "Hello" >> log.txt
minishell> export VAR=value
minishell> cd /tmp && pwd
minishell> exit 42
```

---

## <a name="bonus-part"></a>🌟 Bonus Part

Advanced shell features:

### Bonus Features
- **Logical Operators**:
  - `&&` (AND) - execute next command if previous succeeded
  - `||` (OR) - execute next command if previous failed
- **Wildcard Expansion**:
  - `*` - match any number of characters
  - `?` - match single character
  - `[abc]` - match character set
- **Advanced Redirections**:
  - Support for file descriptor numbers: `2>`, `2>>`, `2<`
- **Command Substitution**:
  - `$(command)` - execute command and use output
- **Variable Expansion**:
  - `$VAR` - expand environment variables
  - `${VAR}` - braced variable expansion
  - `$?` - last command exit status
- **Quoting**:
  - Single quotes `'` - literal strings
  - Double quotes `"` - preserve variables and escapes
  - Backslash `\` - escape special characters

### Example Bonus Usage
```bash
$ minishell
minishell> test -f file.txt && echo "File exists" || echo "Not found"
minishell> ls *.c | wc -l
minishell> echo "Home is $HOME"
minishell> grep "pattern" $(find . -name "*.txt")
minishell> 2>> error.log command
```

---

## <a name="usage"></a>👨‍💻 Usage

### Requirements

- C language (C99 or later)
- GCC compiler
- Linux/Unix system with POSIX compliance
- GNU readline library (for input handling)

### Compiling the Program

**Mandatory Part:**

```shell
$ cd path/to/minishell && make
```

**Bonus Part:**
```shell
$ cd path/to/minishell && make bonus
```

### Running the Program

**Mandatory:**
```shell
$ ./minishell
```

**Bonus:**
```shell
$ ./minishell_bonus
```

### Example Session
```shell
$ ./minishell
minishell> echo "Welcome to Minishell"
Welcome to Minishell
minishell> pwd
/home/user/minishell
minishell> export USER_VAR=test
minishell> echo $USER_VAR
test
minishell> ls | grep -E "\\.c$"
minishell> cd .. && pwd
minishell> exit
$
```

---

## <a name="project-structure"></a>📁 Project Structure

```
minishell/
├── Makefile                 # Build configuration
├── README.md               # This file
├── includes/               # Header files
│   ├── minishell.h
│   ├── minishell_parsing.h
│   ├── minishell_exec.h
│   └── ...
├── srcs/                   # Source files
│   ├── parsing/            # Parsing and tokenization
│   ├── exec/               # Command execution
│   ├── shell/              # Shell initialization
│   ├── destroy/            # Cleanup and memory
│   ├── builtins/           # Built-in commands
│   └── main.c
└── libft/                  # Utility library (if used)
```

---

## 🌳 Abstract Syntax Tree (AST) Recursion

A key concept in Minishell is building an **Abstract Syntax Tree** to represent the command structure:

### What is an AST?

An AST is a **tree representation** of the syntactic structure of shell commands. Instead of executing commands linearly, you parse them into a tree that respects operator precedence and pipes.

### Example: Building an AST

```
Command: ls -la | grep .c && echo done

                    AND
                   /   \
                  /     \
               PIPE      CMD(echo)
              /    \
           CMD     CMD
          (ls)    (grep)
```

### Recursive Parsing Strategy

**1. Parse logical operators first** (`&&`, `||`):
```c
t_ast *parse_logical_operators(t_tokens *tokens)
{
    t_ast *left = parse_pipes(tokens);      // Parse lower precedence
    while (current_token() == "&&" || current_token() == "||")
    {
        t_operator op = get_operator();
        t_ast *right = parse_pipes(tokens);
        left = create_node(op, left, right); // Combine into tree
    }
    return (left);
}
```

**2. Parse pipes** (`|`):
```c
t_ast *parse_pipes(t_tokens *tokens)
{
    t_ast *left = parse_redirections(tokens);
    while (current_token() == "|")
    {
        advance_token();
        t_ast *right = parse_redirections(tokens);
        left = create_node(PIPE, left, right);
    }
    return (left);
}
```

### Benefits of Recursive AST Parsing

| Feature | Benefit |
|---------|---------|
| **Operator Precedence** | Pipes execute before logical operators |
| **Complex Pipelines** | `cmd1 \| cmd2 \| cmd3` handled naturally |
| **Error Recovery** | Easier to identify and handle syntax errors |
| **Execution Control** | Can decide execution order before running |
| **Variable Expansion** | Expand variables at the right time |

### Execution from AST

Once the AST is built, **recursive execution**:

```c
void execute_ast(t_ast *node)
{
    if (node->type == COMMAND)
        execute_command(node);
    else if (node->type == PIPE)
    {
        fork_and_pipe(node->left, node->right);
    }
    else if (node->type == AND)
    {
        execute_ast(node->left);
        if (last_exit_status == 0)
            execute_ast(node->right);
    }
    else if (node->type == OR)
    {
        execute_ast(node->left);
        if (last_exit_status != 0)
            execute_ast(node->right);
    }
}
```

---

## Key Learning Outcomes

✅ Understanding **process management** (`fork`, `execve`, `wait`)  
✅ Working with **file descriptors** and **pipes**  
✅ **Signal handling** in Unix  
✅ **Parsing and tokenization** of shell commands  
✅ **Recursive AST parsing** and operator precedence  
✅ **Tree-based execution** models  
✅ **Environment variables** and process inheritance  
✅ **Memory management** and resource cleanup  
✅ Advanced **string manipulation** in C

---

## Notes

- The shell should handle edge cases gracefully (empty input, quotes, escapes)
- Error messages follow bash conventions
- Memory must be properly managed (no leaks)
- The program behaves as closely as possible to bash for compatibility
