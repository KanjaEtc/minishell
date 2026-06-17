CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.
LDFLAGS = -lreadline

SOURCES = main.c \
		  env/env.c \
		  env/ft_strlen.c \
		  env/ft_strchr.c \
		  env/ft_strlcpy.c \
		  env/ft_strdup.c \
		  env/ft_memcpy.c \

OBJECTS = $(SOURCES:.c=.o)
TARGET = minishell

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
