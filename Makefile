CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.
LDFLAGS = -lreadline

SOURCES = sources/minishell.c \
		  sources/env/env_set.c \
		  sources/env/env_utils.c \
		  sources/exec/cd.c \
		  sources/exec/echo.c \
		  sources/exec/env.c \
		  sources/exec/exec_cmd.c \
		  sources/exec/exec_cmd_2.c \
		  sources/exec/export.c \
		  sources/exec/pwd.c \
		  sources/exec/unset.c \
		  sources/parsing_half/lexer.c \
		  sources/parsing_half/lexer_utils.c \
		  sources/parsing_half/expander.c \
		  sources/parsing_half/expander_utils.c \
		  sources/parsing_half/quote_stripper.c \
		  sources/signals/prompt_signals.c \
		  sources/pipes/pipes.c \
		  sources/pipes/redirs.c \
		  sources/pipes/heredoc.c \

S_LIBFT = s_libft/ft_strlen.c \
		  s_libft/ft_strcmp.c \
		  s_libft/ft_strdup.c \
		  s_libft/ft_strjoin.c \
		  s_libft/ft_substr.c \
		  s_libft/ft_strchr.c \
		  s_libft/ft_memcpy.c \
		  s_libft/ft_putstr_fd.c \
		  s_libft/ft_strlcpy.c \
		  s_libft/ft_split.c \
		  s_libft/ft_putendl_fd.c \

OBJECTS = $(SOURCES:.c=.o) $(S_LIBFT:.c=.o)
TARGET = minishell

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	echo "Compilation complete. Executable: $(TARGET)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
