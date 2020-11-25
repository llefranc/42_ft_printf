/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:26:42 by llefranc          #+#    #+#             */
/*   Updated: 2020/11/25 14:04:21 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <locale.h>
# include <stdlib.h>

# include "libft.h"
# include "float.h"
# include "wchar.h"

# define BUFF_SIZE 1024

typedef struct	s_elem
{
	int			count;
	char		b_wri[BUFF_SIZE + 1];
	int			bw;
	char		b_con[BUFF_SIZE + 1];
	char		*b_str;
	char		size_type[4];
	void		*ptr_n;
	int			boo_pre;
	int			val_pre;
	int			boo_wid;
	int			val_wid;
	int			fl_has;
	int			fl_sig;
	int			fl_zer;
	int			fl_rev;
	int			fl_spa;
}				t_elem;

/*
** --------- FT_PRINTF.C ---------
*/

int				ft_printf(const char *str, ...);
int				str_check(const char *str);
int				str_print(const char *str, va_list ap);

/*
** ------------------------------------------
** --------- FT_PRINTF_FILL_PARAM.C ---------
** ------------------------------------------
*/

void			init_struct(t_elem *par, int resall);
void			fill_param(const char *str, int *i, t_elem *par);
int				fill_param_flags(const char *str, int *i, t_elem *par);
int				fill_param_boo_witdh(const char *str, int *i, t_elem *par);

/*
** --------- FT_PRINTF_FILL_PARAM2.C ---------
*/

int				fill_param_boo_preci(const char *str, int *i, t_elem *par);
void			fill_param_boo_preci2(const char *str, int *i, t_elem *par);
int				fill_param_size(const char *str, int *i, t_elem *par);
void			fill_param_size2(const char *str, int *i,
								t_elem *par, int nbchar);

/*
** --------- FT_PRINTF_FILL_PARAM3.C ---------
*/

int				fill_param_type(const char *str, int *i, t_elem *par);
int				fill_param_type2(char type, int *i, t_elem *par);
int				fill_param_type3(const char *str, int *i, t_elem *par);

/*
** -------------------------------------------
** --------- FT_PRINTF_CHECK_PARAM.C ---------
** -------------------------------------------
*/

int				check_param(t_elem *par);
int				check_size_type(t_elem *par);
int				check_precision(t_elem *par);
int				check_width(t_elem *par);
int				check_flags_zero(t_elem *par);

/*
** --------- FT_PRINTF_CHECK_PARAM2.C ---------
*/

int				check_flags_rev(t_elem *par);
int				check_flags_signed(t_elem *par);
int				check_flags_hashtag(t_elem *par);
int				check_flags_space(t_elem *par);

/*
** ------------------------------------
** --------- FT_PRINTF_CONV.C ---------
** ------------------------------------
*/

void			buf_pri_res(t_elem *par);
void			get_asterisk(t_elem *par, va_list ap);
void			simp_param(t_elem *par);
void			buf_fill(t_elem *par, char *str, char c, int nbchar);
void			str_conv(const char *str, t_elem *par, va_list ap, int *s);

/*
** --------- FT_PRINTF_CONV_CDI.C ---------
*/

void			str_conv_c(t_elem *par, va_list ap);
void			str_conv_di(t_elem *par, va_list ap);
void			str_conv_di2(t_elem *par);
void			str_conv_di2_suite(t_elem *par);
void			str_conv_di3(t_elem *par);

/*
** --------- FT_PRINTF_CONV_UNP.C ---------
*/

void			str_conv_u(t_elem *par, va_list ap);
void			str_conv_u2(t_elem *par);
void			str_conv_u3(t_elem *par);
void			str_conv_n(t_elem *par, va_list ap);
void			str_conv_p(t_elem *par, va_list ap);

/*
** --------- FT_PRINTF_CONV_x.C ---------
*/

void			str_conv_x(t_elem *par, va_list ap);
void			str_conv_x_suite(t_elem *par, va_list ap);
void			str_conv_x2(t_elem *par);
void			str_conv_x2_suite(t_elem *par);
void			str_conv_x3(t_elem *par);

/*
** --------- FT_PRINTF_CONV_S.C ---------
*/

void			str_conv_s(t_elem *par, va_list ap);
void			str_conv_s2(t_elem *par);
void			str_conv_s3(t_elem *par);

/*
** --------- FT_PRINTF_CONV_F.C ---------
*/

void			str_conv_f(t_elem *par, va_list ap);
void			str_conv_f_suite(t_elem *par, int *i);
void			str_conv_f2(t_elem *par);
void			str_conv_f2_suite(t_elem *par);
void			str_conv_f3(t_elem *par);

/*
** --------- FT_PRINTF_CONV_E.C ---------
*/

void			str_conv_e(t_elem *par, va_list ap);
int				str_conv_e2(t_elem *par);
int				str_conv_e2_suite(t_elem *par, int *i, int exp);
int				check_zero(char *dblchar);
void			str_conv_e3(t_elem *par, int *exp);
void			str_conv_e4(t_elem *par, int *exp);

/*
** --------- FT_PRINTF_CONV_G.C ---------
*/

void			str_conv_g(t_elem *par, va_list ap);
void			str_conv_g2(t_elem *par);
void			str_conv_g3(t_elem *par, double dbl);
void			str_conv_g31(t_elem *par, int i);
void			str_conv_g_nbsig(t_elem *par);
void			str_conv_g_nbsig_suite(t_elem *par, int nbsig, int nbzerbef);
void			str_conv_g_nbsig2(t_elem *par);
void			str_conv_g32(t_elem *par);
void			str_conv_g_trimzero(t_elem *par);
void			str_conv_g4(t_elem *par, int *exp);

/*
** --------- FT_PRINTF_CONV_LCLS.C ---------
*/

void			str_conv_lc(t_elem *par, va_list ap);
void			buf_fill_wchar(t_elem *par, char *str);
void			str_conv_ls(t_elem *par, va_list ap);
void			str_conv_ls2(t_elem *par);
void			str_conv_ls3(t_elem *par);

/*
** --------- FT_PRINTF_CONV_OTHERS.C ---------
*/

void			str_conv_modu(t_elem *par, va_list ap);
void			str_conv_efg_inf(t_elem *par);
void			str_conv_efg_inf_suite(t_elem *par);
void			str_conv_efg_inf2(t_elem *par);
void			str_conv_efg_nan(t_elem *par);

#endif
