/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 18:16:51 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/06 15:01:49 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOAT_H
# define FLOAT_H

# include "ft_printf.h"

# include <float.h>

# define MAX_DIGIT	1030
# define BIG_INT	1000

/*
** La struct s_number est utilisee pour des calculs sur des chaines de
** caracteres permettant de reprensenter des gros ints.
** i et j sont les indexs permettant de se deplacer dans la chaine 1 et
** la chaine 2. s1FirD represente líndex du premier chiffre different de
** zero dans la chaine 1. Meme chose pour s2FirD mais pour la seconde chaine.
*/

typedef struct	s_number
{
	int			i;
	int			j;
	int			s1fird;
	int			s2fird;
}				t_number;

/*
** --------- BIG_INT_ADD.C ---------
*/

char			*big_int_add(char *s1, char *s2);
void			big_int_add2(char *s1, char *s2, t_number *num);
char			*big_int_add3(char *s1);
char			*big_int_add4(char *s1, char *s2);
char			*big_int_add5(char *s1, char *s2);

/*
** --------- BIG_INT_SUBS.C && BIG_INT_SUBS2.C ---------
*/

char			*big_int_subs(char *s1, char *s2);
void			big_int_subs2(char *s1, char *s2, t_number *num);
char			*big_int_subs3(char *s1);
void			big_int_subs4(char *s1, char *s2);
void			big_int_subs5(char *s1, char *s2, t_number *num);
void			big_int_subs6(char *s1, char *s2);
void			big_int_subs7(char *s1, char *s2, t_number *num);

/*
** --------- BIG_INT_MULT_POW.C ---------
*/

char			*big_int_mult(char *s1, char *s2);
char			*big_int_mult2(char *s1, char *s2, t_number *num);
void			big_int_mult3(char *s1, t_number *num);
char			*big_int_pow(char *s1, unsigned int pow);

/*
** --------- BIG_INT_DIV.C ---------
*/

char			*big_int_div(char *s1, char *s2);
void			big_int_div2(char *s1, char *s2, char *res, t_number *num);
void			big_int_div3(char numer[], char denom[]);
void			big_int_div4(char *s1, char *s2, char *tmp, long *nb);

/*
** --------- PRINT_BITS.C ---------
*/

void			print_mantissa(char *str);
void			print_octet(char *str);
char			*str_bits(void *type, size_t size);
char			*fill_zero(char *str);

/*
** --------- BIG_INTS_INIT.C ---------
*/

int				get_val_exp(char *strbits);
unsigned long	get_val_man(char *strbits);
char			*fill_numerator(char *num, unsigned long valman, long valexp);
char			*fill_denominator(char *deno, long valexp, double nb);
int				get_digit_exp(double nb);

/*
** --------- BIG_INTS_CALC.C ---------
*/

void			init_num_struct(char *s1, char *s2, t_number *num);
int				big_int_comp(char *s1, char *s2);
char			*big_int_reset(char *str, char signe);
char			*pow_table2(char *bigint, unsigned long valexp);
void			frac_sci_notation(char *num, char *deno, int digitexp);

/*
** --------- DOUBLE_TO_CHAR.C && DOUBLE_TO_CHAR2 ---------
*/

char			*dbltoa(double dbl);
char			*fill_frac(double dbl, char num[], char den[]);
char			*fi_inf(double dbl, char *dblchar, char *strbits,
						unsigned long valman);
char			*fill_char_double(char *dbl, char *num,
						char *deno, int digitexp);
char			*fill_char_double2(char dix[], char zero[],
						int *digitexp, int *len);
void			fill_char_double3(char *dbl, char *num,
						int *len, int *digitexp);
int				fill_char_double4(char *dbl, char *num, char *deno);

/*
** --------- ROUND_DBLSTR.C && ROUND_DBLSTR2.C ---------
*/

void			round_up_int(char *dblchar, char tmp[], int len, int i);
void			round_up(char *dblchar, int prec, int i);
char			*round_dblstr(char *dblchar, int prec);
void			round_dblstr2(char *dblchar, int prec, int i, int j);
void			round_dblstr3(char *dblchar, int prec);
char			*round_dblstr4(char *dblchar, int i);

#endif
