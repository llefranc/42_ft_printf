# 42_Ft_printf (@42Born2Code)

"Because putnbr and putstr aren’t enough"

![Alt text](https://github.com/lucaslefrancq/42_Ft_printf/blob/main/ft_printf_example.png)

## About

Ft_printf is a project of the mandatory part of the 42cursus.
The main goal is to recreate the printf function in C.
In this case we had to understand how the different parameters in printf works (width, height...).
This ft_printf handles all the bonuses from the subject.

- Ft_printf will be able to work with :
    - Flags : -, 0, ., *
	- Conversions : %c, %s, %p, %d, %i, %u, %x, %X, %%
	- Bonus flags : l, ll, h, hh, #, +, and space
	- Bonus conversions : %n, %f, %e, %g

You can do combination between width / heigh / flags and conversions like the real printf.  

For the bonus flag l, I had to implement the wide_char conversion for ls and lc combination.
My ft_printf can so print unicode characters.

For the bonuses %f %e and %g (float conversion), I implemented the Dragon4 algorithm.  
My implementation of the Dragon4 algorithm works like the real printf, so this ft_printf is able to print all the possible floats :
from DBL_MAX (max double) to DBL_MIN (which will print 1024 numbers after the dot !).

In this case, I created a library (called BIG_INT library) that can do calculation on strings filled with number.
This was necessary because floats algorithm needs to represent bigger number than possible with a long long int.  
The BIG_INT library is able to perfom addition, subtraction, multiplication, division and pow.  

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

[1] https://github.com/lucaslefrancq/42_Ft_printf/blob/main/ft_printf.en.subject.pdf