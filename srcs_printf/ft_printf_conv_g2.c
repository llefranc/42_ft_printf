/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_g2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:19:24 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/06 16:26:12 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Suite de la gestion des arrondis dans qui vont aboutir a un chiffre
** significatif en plus (ex 0.9999 > 0.100 ou 0.09999 > 0.0100 avec preci
** de 2).
*/

void	str_conv_g_nbsig_suite(t_elem *par, int nbsig, int nbzerbef)
{
	if (nbsig == 1 && par->val_pre == 1 && (par->b_str)[1] == '1')
		(par->b_str)[3] = '\0';
	else if (par->val_pre < 0 || !par->boo_pre)
	{
		(par->b_str)[1] == '0' &&
					(9 + nbzerbef) <= (int)ft_strlen(par->b_str) ?
					(par->b_str)[3 + 6 + nbzerbef] = '\0' : 0;
		(par->b_str)[1] == '1' ? (par->b_str)[3 + 6 - 1] = '\0' : 0;
	}
	else
	{
		(par->b_str)[1] == '0' &&
				(3 + par->val_pre + nbzerbef) <= (int)ft_strlen(par->b_str) ?
				(par->b_str)[3 + par->val_pre + nbzerbef] = '\0' : 0;
		(par->b_str)[1] == '1' ? (par->b_str)[3 + par->val_pre - 1] = '\0' : 0;
	}
}

/*
** Permet de gerer le cas ou on arrondi a une dizaine superieur et que
** l'on a donc un nb significatif en plus. On tronque alors le dernier
** chiffre (ex : 9.9999 > 10.00 avec 3 au lieu de 10.0).
*/

void	str_conv_g_nbsig2(t_elem *par)
{
	int i;
	int nbsig;

	i = 0;
	nbsig = 0;
	while ((par->b_str)[i])
	{
		if ((par->b_str)[i] >= '0' && (par->b_str)[i] <= '9')
			nbsig++;
		i++;
	}
	nbsig > par->val_pre && par->boo_pre &&
					par->val_pre >= 0 ? (par->b_str)[i - 1] = '\0' : 0;
	par->val_pre < 0 && nbsig > 6 ? (par->b_str)[i - 1] = '\0' : 0;
}

/*
** Permet de gerer le cas du flag '#' lorsque l'on doit remettre le '.'
** derriere un chiffre entier.
*/

void	str_conv_g32(t_elem *par)
{
	int i;

	i = 0;
	while ((par->b_str)[i] && (par->b_str)[i] != '.')
		i++;
	if ((par->b_str)[i] != '.' && (((!par->boo_pre ||
				par->val_pre < 0) && i == 7) || par->val_pre == i - 1))
	{
		(par->b_str)[i] = '.';
		(par->b_str)[i + 1] = '\0';
	}
}

/*
** Permet de supprimer les zero derriere la conv g lorsque le flag '#' est
** absent en fonction de si elle a debouche sur une conv e ou une conv f.
*/

void	str_conv_g_trimzero(t_elem *par)
{
	int i;
	int point;

	i = 0;
	point = 0;
	while ((par->b_str)[i] && (par->b_str)[i] != 'e')
		(par->b_str)[i++] == '.' ? point = 1 : 0;
	if (par->fl_has || !point)
		return ;
	if ((par->b_str)[i] == 'e')
	{
		while ((par->b_str)[--i] == '0')
			ft_strlcpy(par->b_str + i, par->b_str + i + 1,
							ft_strlen(par->b_str) - i);
		if ((par->b_str)[i] == '.')
			ft_strlcpy(par->b_str + i, par->b_str + i + 1,
							ft_strlen(par->b_str) - i);
	}
	else
	{
		while ((par->b_str)[--i] == '0')
			(par->b_str)[i] = '\0';
		if ((par->b_str)[i] == '.')
			(par->b_str)[i] = '\0';
	}
}

/*
** Permet juste d'arrondir a un chiffre de moins pour le cas g
** qui donne sur une conversion e car il y a toujours un chiffre
** significatif devant la virgule, donc on diminue la valeur d'arrondi
** (= preci) de 1.
*/

void	str_conv_g4(t_elem *par, int *exp)
{
	char	*str;
	char	*tmp;

	if (!par->boo_pre || par->val_pre < 0)
		par->b_str = round_dblstr(par->b_str, 6 - 1);
	else
		par->b_str = round_dblstr(par->b_str, par->val_pre - 1);
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
