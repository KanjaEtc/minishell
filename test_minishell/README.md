# Minishell test suite

## Usage
```
make
bash tests/run_tests.sh ./minishell     # 133 output/status tests vs bash
python3 tests/pty_test.py               # 8 interactive signal tests (needs a tty via pty)
```

The diff suite pipes scripts into minishell, strips readline's prompt echo,
and compares stdout + `$?` against bash run on the same script. The pty suite
spawns minishell on a pseudo-terminal and sends real ctrl-C / ctrl-\ / ctrl-D
to verify signal behavior (`$?` = 130/131, Quit message, heredoc interrupt...).

Recommended before defence:
```
valgrind --leak-check=full --suppressions=tests/readline.supp ./minishell
```
