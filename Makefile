# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/05 21:19:13 by hyeunkim          #+#    #+#              #
#    Updated: 2024/04/23 14:04:59 by hyeunkim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL = all

NAME = minishell
# **************************************************************************** #
LIB_DIR = ./libs/libft

CFLAGS = -Wall -Wextra -Werror -MMD -MP
CPPFLAGS = -I$(LIB_DIR)

LDFLAGS = -L$(LIB_DIR)
LDLIBS = -lft -lreadline
# **************************************************************************** #
ifdef DEBUG
	CFLAGS += -O0 -g3 -fsanitize=address
endif
# **************************************************************************** #
RESET = \033[0m

BOLD = \033[1m

RED = \033[31m
GREEN = \033[32m
GRAY = \033[90m

Q = @
# **************************************************************************** #
MAN_DIR = ./mandatory
BON_DIR = ./bonus

COMP_SRCS = $(if $(filter bonus,$(MAKECMDGOAL)),$(bon_src),$(SRCS_M))
COMP_OBJS = $(COMP_SRCS:.c=.o)
COMP_DEPS = $(COMP_SRCS:.c=.d)
# **************************************************************************** #
src_m =	main.c\
		free.c\
		error.c\
		string.c\
		heredoc.c\
		signal.c\
		signal_set.c\
		tokenize.c\
		token_util.c\
		tree_pipe.c\
		tree_simple.c\
		tree_standard.c\
		tree_compound.c\
		tree_util.c\
		expand.c\
		expand_envp.c\
		expand_util.c\
		wildcard.c\
		wildcard_util.c\
		execute.c\
		execute_util.c\
		execute_pipe.c\
		execute_builtin.c\
		builtin_cd.c\
		builtin_env.c\
		builtin_pwd.c\
		builtin_echo.c\
		builtin_util.c\
		builtin_exit.c\
		builtin_unset.c\
		builtin_export.c\

SRCS_M = $(addprefix $(MAN_DIR)/, $(src_m))
OBJS_M = $(SRCS_M:.c=.o)
DEPS_M = $(SRCS_M:.c=.d)

src_b =main_bonus.c\
		free_bonus.c\
		error_bonus.c\
		string_bonus.c\
		heredoc_bonus.c\
		signal_bonus.c\
		signal_set_bonus.c\
		tokenize_bonus.c\
		token_util_bonus.c\
		tree_pipe_bonus.c\
		tree_simple_bonus.c\
		tree_standard_bonus.c\
		tree_compound_bonus.c\
		tree_util_bonus.c\
		expand_bonus.c\
		expand_envp_bonus.c\
		expand_util_bonus.c\
		wildcard_bonus.c\
		wildcard_util_bonus.c\
		execute_bonus.c\
		execute_util_bonus.c\
		execute_pipe_bonus.c\
		execute_builtin_bonus.c\
		builtin_cd_bonus.c\
		builtin_env_bonus.c\
		builtin_pwd_bonus.c\
		builtin_echo_bonus.c\
		builtin_util_bonus.c\
		builtin_exit_bonus.c\
		builtin_unset_bonus.c\
		builtin_export_bonus.c\

SRCS_B = $(addprefix $(BON_DIR)/,$(src_b))
OBJS_B = $(SRCS_B:.c=.o)
DEPS_B = $(SRCS_B:.c=.d)

-include $(DEPS_M) $(DEPS_B)
# **************************************************************************** #
.PHONY : all clean fclean re bonus

all : $(NAME)

%.o : %.c
	$(Q) $(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME) : $(OBJS_M)
	$(Q) $(MAKE) .mandatory

clean :
	$(Q) $(MAKE) -C $(LIB_DIR) clean
	$(Q) $(RM) $(wildcard $(MAN_DIR)/*.o) $(wildcard $(MAN_DIR)/*.d)
	$(Q) $(RM) $(wildcard $(BON_DIR)/*.o) $(wildcard $(BON_DIR)/*.d)
	$(Q) $(RM) .mandatory .bonus
	$(Q) echo "\t$(RED)$@$(RESET) $(BOLD)MINISHELL$(RESET) object files OK"

fclean : clean
	$(Q) $(MAKE) -C $(LIB_DIR) fclean
	$(Q) $(RM) $(NAME)
	$(Q) echo "\t$(RED)$@$(RESET) $(BOLD)MINISHELL$(RESET) OK"

re : fclean
	$(Q) $(MAKE) -C $(LIB_DIR)
	$(Q) $(MAKE) $(NAME)

bonus : .bonus

.mandatory : $(OBJS_M)
	$(Q) echo "$(GRAY)---------------- start compiling ----------------$(RESET)"
	$(Q) $(MAKE) -C $(LIB_DIR)
	$(Q) $(RM) .bonus $(OBJS_B) $(DEPS_B)
	$(Q) touch $@
	$(Q) $(CC) $(CFLAGS) $(OBJS_M) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	$(Q) echo "\t$(GREEN)make$(RESET) $(BOLD)MINISHELL$(RESET) mandatory OK"

.bonus : $(OBJS_B)
	$(Q) echo "$(GRAY)---------------- start compiling ----------------$(RESET)"
	$(Q) $(MAKE) -C $(LIB_DIR) all
	$(Q) $(RM) .mandatory $(OBJS_M) $(DEPS_M)
	$(Q) touch $@
	$(Q) $(CC) $(CFLAGS) $(OBJS_B) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	$(Q) echo "\t$(GREEN)make$(RESET) $(BOLD)MINISHELL$(RESET) bonus OK"
# **************************************************************************** #
