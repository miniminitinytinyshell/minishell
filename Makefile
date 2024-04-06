# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/05 21:19:13 by hyeunkim          #+#    #+#              #
#    Updated: 2024/04/06 18:54:08 by hyeunkim         ###   ########.fr        #
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
man_src = main.c\
			tokenize.c\
			token_util.c\
			tree_pipe.c\
			tree_simple.c\
			tree_standard.c\
			tree_compound.c\
			tree_util.c\
			expand.c\
			expand_util.c\
			expand_wildcard.c\
			free.c\
			string.c\
			error.c\
			error_system.c\
			heredoc.c\
			execute.c\
			execute_pipe.c\
			execute_builtin.c\
			builtin_echo.c\
			builtin_cd.c\
			builtin_env.c\
			builtin_pwd.c\

man_objs = $(man_src:.c=.o)
man_deps = $(man_src:.c=.d)

# bonus_src = pipex_bonus.c\
# 			error_bonus.c\
# 			parse_path_bonus.c\
# 			process_bonus.c\
# 			parse_cmd_bonus.c\
# 			here_doc_bonus.c\

# bonus_objs = $(bonus_src:.c=.o)
# bonus_deps = $(bonus_src:.c=.d)

-include $(man_deps)
#$(bonus_deps)
# **************************************************************************** #
.PHONY : all clean fclean re
# bonus

all : $(NAME)

%.o : %.c
	$(Q) $(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME) : $(man_objs)
	$(Q) $(MAKE) .mandatory

clean :
	$(Q) $(MAKE) -C $(LIB_DIR) clean
	$(Q) $(RM) $(wildcard *.o) $(wildcard *.d)
	$(Q) $(RM) .mandatory .bonus
	$(Q) echo "\t$(RED)$@$(RESET) $(BOLD)MINISHELL$(RESET) object files OK"

fclean : clean
	$(Q) $(MAKE) -C $(LIB_DIR) fclean
	$(Q) $(RM) $(NAME)
	$(Q) echo "\t$(RED)$@$(RESET) $(BOLD)MINISHELL$(RESET) OK"

re : fclean
	$(Q) $(MAKE) -C $(LIB_DIR) $@
	$(Q) $(MAKE) $(NAME)

bonus : .bonus

.mandatory : $(man_objs)
	$(Q) echo "$(GRAY)---------------- start compiling ----------------$(RESET)"
	$(Q) $(MAKE) -C $(LIB_DIR)
	$(Q) $(RM) .bonus $(bonus_objs) $(bonus_deps)
	$(Q) touch $@
	$(Q) $(CC) $(CFLAGS) $(man_objs) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	$(Q) echo "\t$(GREEN)make$(RESET) $(BOLD)MINISHELL$(RESET) mandatory OK"

# .bonus : $(bonus_objs)
# 	$(Q) echo "$(GRAY)---------------- start compiling ----------------$(RESET)"
# 	$(Q) $(MAKE) -C $(LIB_DIR) all
# 	$(Q) $(RM) .mandatory $(man_objs) $(man_deps)
# 	$(Q) touch $@
# 	$(Q) $(CC) $(CFLAGS) $(bonus_objs) $(LDFLAGS) $(LDLIBS) -o $(NAME)
# 	$(Q) echo "\t$(GREEN)make$(RESET) $(BOLD)MINISHELL$(RESET) bonus OK"
# **************************************************************************** #
