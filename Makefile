NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address
LDFLAGS = -lreadline

RM = rm -f

SRC_DIR = .
OBJ_DIR = obj

SRCS = main.c \
	   errors/free_exit.c \
	   initialize/init_structs.c \
	   initialize/env_lst_utils.c \
	   initialize/display_prompt.c \
	   builtins/ft_cd.c \
	   builtins/ft_echo.c \
	   builtins/ft_env.c \
	   builtins/ft_exit.c \
	   builtins/ft_export.c \
	   builtins/ft_pwd.c \
	   builtins/ft_unset.c \
	   signals/signals.c \
	   lexer/lexer.c \
	   lexer/lexer_utils.c \
	   lexer/lexer_lst_utils.c \
	   lexer/lexer_errors.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m
CHECKMARK = ✔

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) $(LDFLAGS) -lft
	@echo "$(GREEN)$(CHECKMARK) $(NAME) created.$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@$(RM) -r $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "$(YELLOW)$(CHECKMARK) $(NAME) cleaned.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(RED)$(CHECKMARK) $(NAME) removed.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
