/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_e.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:34:48 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/06 16:25:50 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Gere la conversion de 'e'. Convertit le double dans une chaine, puis
** joint l'arrondi et joint l'exposant derriere dans str_conv_e2. Si le
** flag # est present, on rajoute un '.' a la fin du chiffre avant
** l'exposant. Ensuite la conv e respescte les memes regles que la conv f
** donc on fait appelle aux fonctions de celle-ci.
*/

void	str_conv_e(t_elem *par, va_list ap)
{
	int i;

	i = 0;
	get_asterisk(par, ap);
	par->b_str = dbltoa(va_arg(ap, double));
	simp_param(par);
	if (!((par->b_str)[1] >= '0' && (par->b_str)[1] <= '9'))
		str_conv_efg_inf(par);
	else
	{
		str_conv_e2(par);
		if (par->fl_has && par->boo_pre && par->val_pre == 0)
		{
			while ((par->b_str)[i] != 'e')
				i++;
			ft_memmove(par->b_str + i + 1, par->b_str + i, 5);
			(par->b_str)[i] = '.';
		}
		(par->b_str)[0] == '-' ? par->fl_sig = 1 : 0;
		if (!par->fl_rev)
			str_conv_f2(par);
		else
			str_conv_f3(par);
	}
	free(par->b_str);
}

/*
** Permet d'arrondir puis de rajouter l'exposant a la suite de dblchar
** en fonction de si la valeur est > 1 (exp positif) ou comprise entre 0
** et 1 (exp neg) On deplace d'abord le '.' dans la chaine pour ne garder
** qu'un chiffre significatif avant la virgule, puis dans str_conv_e3 on
** arrondit et on join l'exposant derriere.
*/

int		str_conv_e2(t_elem *par)
{
	int		exp;
	int		i;

	exp = 0;
	i = 2;
	if ((par->b_str)[i - 1] == '0' && (par->b_str)[i] == '.'
				&& check_zero(par->b_str))
	{
		while ((par->b_str)[1] == '0')
		{
			(par->b_str)[1] = (par->b_str)[3];
			ft_strlcpy(par->b_str + 3, par->b_str + 4, MAX_DIGIT - 4 + 1);
			(par->b_str)[MAX_DIGIT - 1] = '0';
			exp--;
		}
	}
	else
	{
		while ((par->b_str)[i++] != '.')
			exp++;
		while (--i != 2)
			(par->b_str)[i] = (par->b_str)[i - 1];
		(par->b_str)[2] = '.';
	}
	return (str_conv_e2_suite(par, &i, exp));
}

/*
** Suite de conv e2. Appelle e3 si on a affaire a une conv 'e', appelle
** g4 si on a affaire a une conv 'g'.
*/

int		str_conv_e2_suite(t_elem *par, int *i, int exp)
{
	*i = exp;
	ft_strchr(par->size_type, 'e') ? str_conv_e3(par, &exp) :
				str_conv_g4(par, &exp);
	*i < 0 ? *i = -exp : 0;
	*i >= 0 ? *i = exp : 0;
	return (*i);
}

/*
** Permet d'arrondir le dblchar en fonction de la precision (arrondit a
** 6 si celle-ci absente ou negative), puis de joindre l'exposant. On
** la chaine contenant l'exposant fait 7 char pour : 2 '+e', 3 l'exp (peut
** aller jusqu'a 308), 1 pour flag le '.' du flag # et 1 pour '\0'.
*/

void	str_conv_e3(t_elem *par, int *exp)
{
	char	*str;
	char	*tmp;

	if (!par->boo_pre || par->val_pre < 0)
		par->b_str = round_dblstr(par->b_str, 6);
	else
		par->b_str = round_dblstr(par->b_str, par->val_pre);
	str_conv_e4(par, exp);
	str = malloc(7);
	ft_memset(str, 'A', 7);
	str[6] = '\0';
	*exp < 0 ? ft_strlcpy(str, "e-", 3) : ft_strlcpy(str, "e+", 3);
	*exp < 0 ? *exp *= -1 : 0;
	*exp < 10 ? str[2] = '0' : 0;
	*exp < 10 ? ft_itoa_buffer(*exp, str + 3) : ft_itoa_buffer(*exp, str + 2);
	tmp = par->b_str;
	par->b_str = ft_strjoin(par->b_str, str);
	ft_replace_char(par->b_str, '\0', 'A');
	free(tmp);
	free(str);
}

/*
** Gere le cas ou e est de la forme 9.9999....+-ex et ou l'on se retrouve
** apres l'arrondi avec un resultat de la forme 10.0000...+-ex. On
** decale la virgule d'une decimale et augmente l'exposant de un.
*/

void	str_conv_e4(t_elem *par, int *exp)
{
	int i;

	i = 0;
	if ((par->b_str)[1] == '1' && (par->b_str)[2] == '0'
					&& (par->b_str)[3] == '.')
	{
		(par->b_str)[2] = '.';
		(par->b_str)[3] = '0';
		while ((par->b_str)[i])
			i++;
		(par->b_str)[--i] = '\0';
		(*exp)++;
	}
	else if ((par->b_str)[1] == '1' && (par->b_str)[2] == '0')
	{
		while ((par->b_str)[i])
			i++;
		(par->b_str)[--i] = '\0';
		(*exp)++;
	}
}
