# 42_Ft_printf (@42Born2Code)

"Because putnbr and putstr aren’t enough"

![Alt text](https://github.com/lucaslefrancq/42-06_minishell/blob/master/minishell_example.png)

## About

Minishell is the 6th project of the mandatory part of the cursus that I made with my friend [Corentin Debraix][1].
It's only made in C and the main goal was to create a shell working like bash.
In this case we had to understand how processes, redirections, pipes, execve and bash builtins work.
We also had to learn how bash was handling a command line (lexer / parser / exec).

- Here is the [subject][1]

`This project was code for MACOS`

### Building and running the project

1. Download/Clone this repo

        git clone https://github.com/lucaslefrancq/42_Ft_printf

2. `cd` into the root directory, and run `make`

        cd 42_ft_printf
        make

3.  Compile your `main.c` with the lib `printf.a` created

        gcc -Wall -Werror -Wextra main.c printf.a

## Sources

- [Tutorial for writing a small shell in C][5]

[1]