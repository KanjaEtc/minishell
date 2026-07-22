*This project has been created as part of the 42 curriculum by marotsen and ranoumba.*

# Minishell

A simplified Unix shell written in C, inspired by bash.  
This project was created as part of the 42 curriculum by marotsen and ranoumba.

## Description

Minishell is a minimal shell that reads commands from a prompt, parses them, and executes them.  
It aims to reproduce core shell behavior such as:

- displaying a prompt and waiting for user input
- executing external commands
- supporting built-in commands like `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`
- handling pipes (`|`)
- supporting redirections (`<`, `>`, `>>`)
- managing heredocs (`<<`)
- handling environment variables
- managing signals in a shell-like way

## How it works

When the program starts, it displays a prompt and waits for the user to enter a command line.  
The shell then:

1. reads the input
2. parses it into commands and arguments
3. detects built-ins or external programs
4. executes the command
5. prints the prompt again until the user exits

Requirements:
- `make`
- `gcc`
- `readline` development libraries

Compile the project with make.
Run this command :

./minishell

Then inside :
$ echo Hello \
$ ls -la \
$ pwd\
$ echo "hello world" > output.txt \
$ cat < input.txt \
$ cat << EOF \
hello \
EOF \
$ ls | grep minishell \

## Resources
// "https://man7.org/
// "https://i.sstatic.net/lVx5P.gif"
// "https://42-cursus.gitbook.io/guide/3-rank-03/minishell/functions"
// "github"
// Gemini to explain what we didn't understand and help us catch well-hidden bugs
// Our peers obviously

## Authors
marotsen
ranoumba
