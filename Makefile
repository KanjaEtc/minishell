CC = gcc
CFLAGS = -Wall -Wextra -Werror -I. -Iincludes -Ilibft
LDFLAGS = -lreadline

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# S_LIBFT = s_libft/ft_strlen.c \
# 		  s_libft/ft_strdup.c \
# 		  s_libft/ft_strjoin.c \
# 		  s_libft/ft_substr.c \
# 		  s_libft/ft_strchr.c \
# 		  s_libft/ft_memcpy.c \
# 		  s_libft/ft_putstr_fd.c \
# 		  s_libft/ft_strlcpy.c \
# 		  s_libft/ft_split.c \
# 		  s_libft/ft_putendl_fd.c \
# 		  s_libft/ft_strncmp.c \
# 		  s_libft/ft_itoa.c \
# 		  s_libft/ft_atoi.c \

SOURCES = sources/minishell.c \
		  sources/debug_utils.c \
		  sources/env/env_set.c \
		  sources/env/env_utils.c \
		  sources/env/env_utils_bis.c \
		  sources/exec/cd.c \
		  sources/exec/echo.c \
		  sources/exec/env.c \
		  sources/exec/exit.c \
		  sources/exec/exec_cmd.c \
		  sources/exec/exec_cmd_bis.c \
		  sources/exec/export.c \
		  sources/exec/pwd.c \
		  sources/exec/unset.c \
		  sources/parsing/lexer.c \
		  sources/parsing/lexer_utils.c \
		  sources/parsing/expander.c \
		  sources/parsing/expander_utils.c \
		  sources/parsing/quote_stripper.c \
		  sources/parsing/parser.c \
		  sources/parsing/parser_utils.c \
		  sources/parsing/parser_utils_bis.c \
		  sources/parsing/syntax_check.c \
		  sources/parsing/word_split.c \
		  sources/signals/prompt_signals.c \
		  sources/signals/exec_signals.c \
		  sources/pipes/pipes.c \
		  sources/pipes/redirs.c \
		  sources/pipes/heredoc.c \

OBJECTS = $(SOURCES:.c=.o)
TARGET = minishell

all: $(TARGET)

$(TARGET): $(OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(TARGET) $(LDFLAGS)
	echo "Compilation complete. Executable: $(TARGET)"

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(TARGET)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
