# # **************************************************************************** #
# #                                                                              #
# #                                                         :::      ::::::::    #
# #    Makefile                                           :+:      :+:    :+:    #
# #                                                     +:+ +:+         +:+      #
# #    By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+         #
# #                                                 +#+#+#+#+#+   +#+            #
# #    Created: 2024/03/05 21:19:13 by hyeunkim          #+#    #+#              #
# #    Updated: 2024/03/13 16:43:20 by hyeunkim         ###   ########.fr        #
# #                                                                              #
# # **************************************************************************** #

# .DEFAULT_GOAL = all

# NAME = pipex
# # **************************************************************************** #
# LIB_DIR = ./libs/libft

# CFLAGS = -Wall -Wextra -Werror -MMD -MP
# CPPFLAGS = -I$(LIB_DIR)

# LDFLAGS = -L$(LIB_DIR)
# LDLIBS = -lft
# # **************************************************************************** #
# ifdef DEBUG
# 	CFLAGS += -O0 -g3 -fsanitize=address
# endif
# # **************************************************************************** #
# RESET = \033[0m

# BOLD = \033[1m

# RED = \033[31m
# GREEN = \033[32m
# GRAY = \033[90m

# Q = @
# # **************************************************************************** #
# man_src = pipex.c\
# 			error.c\
# 			parse_path.c\
# 			process.c\
# 			parse_cmd.c\

# man_objs = $(man_src:.c=.o)
# man_deps = $(man_src:.c=.d)

# bonus_src = pipex_bonus.c\
# 			error_bonus.c\
# 			parse_path_bonus.c\
# 			process_bonus.c\
# 			parse_cmd_bonus.c\
# 			here_doc_bonus.c\

# bonus_objs = $(bonus_src:.c=.o)
# bonus_deps = $(bonus_src:.c=.d)

# -include $(man_deps) $(bonus_deps)
# # **************************************************************************** #
# .PHONY : all clean fclean re bonus

# all : $(NAME)

# %.o : %.c
# 	$(Q) $(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# $(NAME) : $(man_objs)
# 	$(Q) $(MAKE) .mandatory

# clean :
# 	$(Q) $(MAKE) -C $(LIB_DIR) clean
# 	$(Q) $(RM) $(wildcard *.o) $(wildcard *.d)
# 	$(Q) $(RM) .mandatory .bonus
# 	$(Q) echo "\t$(RED)$@$(RESET) $(BOLD)PIPEX$(RESET) object files OK"

# fclean : clean
# 	$(Q) $(MAKE) -C $(LIB_DIR) fclean
# 	$(Q) $(RM) $(NAME)
# 	$(Q) echo "\t$(RED)$@$(RESET) $(BOLD)PIPEX$(RESET) OK"

# re : fclean
# 	$(Q) $(MAKE) -C $(LIB_DIR) $@
# 	$(Q) $(MAKE) $(NAME)

# bonus : .bonus

# .mandatory : $(man_objs)
# 	$(Q) echo "$(GRAY)---------------- start compiling ----------------$(RESET)"
# 	$(Q) $(MAKE) -C $(LIB_DIR)
# 	$(Q) $(RM) .bonus $(bonus_objs) $(bonus_deps)
# 	$(Q) touch $@
# 	$(Q) $(CC) $(CFLAGS) $(man_objs) $(LDFLAGS) $(LDLIBS) -o $(NAME)
# 	$(Q) echo "\t$(GREEN)make$(RESET) $(BOLD)PIPEX$(RESET) mandatory OK"

# .bonus : $(bonus_objs)
# 	$(Q) echo "$(GRAY)---------------- start compiling ----------------$(RESET)"
# 	$(Q) $(MAKE) -C $(LIB_DIR) all
# 	$(Q) $(RM) .mandatory $(man_objs) $(man_deps)
# 	$(Q) touch $@
# 	$(Q) $(CC) $(CFLAGS) $(bonus_objs) $(LDFLAGS) $(LDLIBS) -o $(NAME)
# 	$(Q) echo "\t$(GREEN)make$(RESET) $(BOLD)PIPEX$(RESET) bonus OK"
# # **************************************************************************** #
