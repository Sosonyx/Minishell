# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fox <fox@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/18 15:13:11 by ihadj             #+#    #+#              #
#    Updated: 2025/09/17 20:08:28 by fox              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ===========================[ Variables générales ]===========================

NAME        = minishell

SRC_DIR     = srcs
LIBFT_DIR   = libft
BUILD_DIR   = build

INC         = includes

CC          = cc
CFLAGS      =  -g3 -I$(INC) -I$(LIBFT_DIR)
LDFLAGS 	= -lreadline -lncurses

# -Wall -Wextra -Werror

LIBFT_A     = $(LIBFT_DIR)/libft.a

SRC         = \
				$(SRC_DIR)/main.c															\
				$(SRC_DIR)/error_and_event_manager/print_error.c							\
				$(SRC_DIR)/error_and_event_manager/print_hd_error.c							\
				$(SRC_DIR)/error_and_event_manager/signal_manager.c							\
				$(SRC_DIR)/error_and_event_manager/messager.c								\
				$(SRC_DIR)/exec/execute_ast.c												\
				$(SRC_DIR)/exec/execute_leaf.c												\
				$(SRC_DIR)/exec/execute_and.c												\
				$(SRC_DIR)/exec/execute_or.c												\
				$(SRC_DIR)/exec/execute_subshell.c											\
				$(SRC_DIR)/exec/execute_pipe.c												\
				$(SRC_DIR)/exec/execute_builtin.c											\
				$(SRC_DIR)/exec/extract_return_code.c										\
				$(SRC_DIR)/exec/redirections/close_secure.c									\
				$(SRC_DIR)/exec/redirections/preconfig_leaf.c								\
				$(SRC_DIR)/exec/redirections/redirect_leaf.c								\
				$(SRC_DIR)/exec/redirections/forward_fds.c									\
				$(SRC_DIR)/exec/redirections/close_fds.c									\
				$(SRC_DIR)/exec/redirections/save_std_fileno.c								\
				$(SRC_DIR)/exec/redirections/restore_std_fileno.c							\
				$(SRC_DIR)/exec/wait_if_leaf.c												\
				$(SRC_DIR)/exec/command_build/cmd_build.c									\
				$(SRC_DIR)/lexer/lexer.c													\
				$(SRC_DIR)/lexer/utils/utils.c												\
				$(SRC_DIR)/lexer/utils/stock_functions.c									\
				$(SRC_DIR)/lexer/utils/count_tokens.c										\
				$(SRC_DIR)/lexer/syntax_check.c												\
				$(SRC_DIR)/lexer/tokenize_input.c											\
				$(SRC_DIR)/parsing/build_ast.c												\
				$(SRC_DIR)/parsing/build_redir.c											\
				$(SRC_DIR)/parsing/destroy_ast.c											\
				$(SRC_DIR)/parsing/build_cmd.c												\
				$(SRC_DIR)/parsing/parse_tokens.c											\
				$(SRC_DIR)/parsing/parse_cntl_and_or.c										\
				$(SRC_DIR)/parsing/parse_cntl_pipe.c										\
				$(SRC_DIR)/parsing/parse_subshell.c											\
				$(SRC_DIR)/parsing/create_leaf.c											\
				$(SRC_DIR)/parsing/input_heredoc.c											\
				$(SRC_DIR)/shell/shell_init.c												\
				$(SRC_DIR)/shell/shell_destroy.c											\
				$(SRC_DIR)/shell/shell_kill.c												\
				$(SRC_DIR)/built-in/ft_exit.c												\
				$(SRC_DIR)/built-in/ft_cd.c													\
				$(SRC_DIR)/built-in/ft_echo.c												\
				$(SRC_DIR)/built-in/ft_env.c												\
				$(SRC_DIR)/built-in/ft_export.c												\
				$(SRC_DIR)/built-in/ft_unset.c												\
				$(SRC_DIR)/built-in/ft_pwd.c												\
				$(SRC_DIR)/built-in/utils.c

OBJ         = $(addprefix $(BUILD_DIR)/, $(subst $(SRC_DIR)/,,$(SRC:.c=.o)))

# ================================[ Couleurs ]================================

GREEN       = \033[0;32m
RED         = \033[0;31m
BLUE        = \033[0;34m
BROWN       = \033[0;33m
BLUE        = \033[1;34m
END         = \033[0m
TITLE       = \033[1m

# ================================[ Règles Make ]==============================

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A)
	@echo "$(GREEN)🔘 $(TITLE)make $(NAME)$(END)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS) $(LIBFT_A) > /dev/null && \
	echo "   $(GREEN)⤷ $(END)Executable: $(GREEN)$(NAME)$(END)"

$(LIBFT_A):
	@echo "$(GREEN)🔘 $(TITLE)compiling libft... $(END)"
	@make -s -C $(LIBFT_DIR) && echo "   $(GREEN)⤷ $(END)Success $(GREEN)(libft.a)$(END)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@if [ -z "$$(ls -A $(BUILD_DIR) 2>/dev/null)" ]; then \
		echo "$(GREEN)🔘 $(TITLE)Create object files$(END)"; fi
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null && \
	printf "   $(GREEN)⤷ $(BROWN)%-38s $(BLUE)⟹  $(BROWN)%s$(END)\n" "$<" "$@"

# ================================[ Nettoyage ]===============================

c clean:
	@echo "$(GREEN)🔘 $(TITLE)make clean$(END)"
	@rm -f $(OBJ) && echo "   $(GREEN)⤷ $(END)Removed object files"
	@make -s -C $(LIBFT_DIR) clean
	
fc fclean:
	@echo "$(GREEN)🔘 $(TITLE)make fclean$(END)"
	@if [ -f $(NAME) ]; then rm -f $(NAME) && echo "   $(GREEN)⤷ $(END)Removed binary $(NAME)"; fi
	@if [ -d $(BUILD_DIR) ]; then rm -rf $(BUILD_DIR) && echo "   $(GREEN)⤷ $(END)Removed build dir"; fi
	@make -s -C $(LIBFT_DIR) fclean


cpu: $(NAME)
	@echo "$(GREEN)🔘 $(TITLE)make cpu tests$(END)"
	@git clone https://github.com/Rz-Rz/thales_tester.git $(CPU) > /dev/null 2>&1; \
	echo "   $(GREEN)⤷ $(END)git clone $(CPU)"; \
	chmod +x $(CPU)/test.sh
	@./$(CPU)/test.sh ../$(NAME) 1

re: fc all

.PHONY: all clean c fclean fc re

#               $(SRC_DIR)/init/init_data.c \
              $(SRC_DIR)/init/init_philos.c \
              $(SRC_DIR)/parsing/parsing.c \
              $(SRC_DIR)/routine/routine.c \
              $(SRC_DIR)/routine/routine2.c	\
              $(SRC_DIR)/routine/alone.c	\
              $(SRC_DIR)/routine/time.c \
              $(SRC_DIR)/monitoring/monitoring.c \
              $(SRC_DIR)/simulation/simulation.c \
              $(SRC_DIR)/exit/exit.c \
              $(SRC_DIR)/exit/error.c \
              $(SRC_DIR)/utils/utils.c \
			  $(SRC_DIR)/utils/color.c
