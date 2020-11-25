/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_g.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:36:12 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/06 16:26:06 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Permet de gerer la conv g + format. Met la preci a 1 si elle vaut 0 car
** on doit toujours avoir 1 nb significatif. On recup la valeur de l'exp
** et on effectue conv e (voir g2) ou f (voir g3) en focntion de celui-ci.
*/

void	str_conv_g(t_elem *par, va_list ap)
{
	double	dbl;
	int		exp;

	ft_memset(par->b_con, 0, BUFF_SIZE + 1);
	get_asterisk(par, ap);
	dbl = va_arg(ap, double);
	par->b_str = dbltoa(dbl);
	simp_param(par);
	if (!((par->b_str)[1] >= '0' && (par->b_str)[1] <= '9'))
		str_conv_efg_inf(par);
	else
	{
		par->boo_pre && par->val_pre == 0 ? par->val_pre = 1 : 0;
		exp = str_conv_e2(par);
		if ((exp > 0 && exp >= par->val_pre && par->val_pre >= 0
					&& par->boo_pre) || exp < -4 || ((par->val_pre < 0 ||
					!par->boo_pre) && exp >= 6))
			str_conv_g2(par);
		else
			str_conv_g3(par, dbl);
	}
	free(par->b_str);
}

/*
** Permet de gerer le flag '#' dans le cas d'une gonv g qui aboutit sur
** une conv e. Appelle la fonction pour trim les zeros si celui-ci est
** absent. Appelle ensuite les fonctions f qui formatent les floats
** (car format e <=> a format f).
*/

void	str_conv_g2(t_elem *par)
{
	int i;

	i = 0;
	if (par->fl_has && par->boo_pre && par->val_pre == 1)
	{
		while ((par->b_str)[i] != 'e')
			i++;
		ft_memmove(par->b_str + i + 1, par->b_str + i, 5);
		(par->b_str)[i] = '.';
	}
	else
		str_conv_g_trimzero(par);
	(par->b_str)[0] == '-' ? par->fl_sig = 1 : 0;
	if (!par->fl_rev)
		str_conv_f2(par);
	else
		str_conv_f3(par);
}

/*
** Si la conv e ne remplit pas les criteres, on free et realise a nouveau
** une conv mais cette fois ci de format f. Les fonctions f2 et f3
** permettent de faire le format une fois qu'on a gere les arrondis (g31)
** et le cas de la presence ou non du flag '#'.
*/

void	str_conv_g3(t_elem *par, double dbl)
{
	int i;

	i = 0;
	free(par->b_str);
	par->b_str = dbltoa(dbl);
	simp_param(par);
	while ((par->b_str)[i] != '.')
		i++;
	str_conv_g31(par, i);
	if (par->fl_has)
		str_conv_g32(par);
	else
		str_conv_g_trimzero(par);
	(par->b_str)[0] == '-' ? par->fl_sig = 1 : 0;
	if (!par->fl_rev)
		str_conv_f2(par);
	else
		str_conv_f3(par);
}

/*
** Permet de gerer l'arrondi de g qui donne une conv f. On distingue
** les cas 0.xx et x.xxx. Pour 0.xxx, on retire 3 pour le '+0.'. Les fonct
** nbsig permettent de gerer le cas ou l'arrondi fait passer a une valeur
** superieur le dbl (ex 0.99 => 1, 9.9 => 10).
*/

void	str_conv_g31(t_elem *par, int i)
{
	if ((par->b_str)[1] == '0' && (par->b_str)[2] == '.')
	{
		i++;
		while ((par->b_str)[i] == '0')
			i++;
		(par->b_str)[i] == '\0' ? i = 2 : 0;
		if (!par->boo_pre || par->val_pre < 0)
			par->b_str = round_dblstr(par->b_str, 6 + i - 3);
		else if (par->val_pre == 1)
			par->b_str = round_dblstr(par->b_str, i - 2);
		else
			par->b_str = round_dblstr(par->b_str, par->val_pre + i - 3);
		str_conv_g_nbsig(par);
	}
	else
	{
		if (!par->boo_pre || par->val_pre < 0)
			par->b_str = round_dblstr(par->b_str, 6 - --i);
		else
			par->b_str = round_dblstr(par->b_str, par->val_pre - --i);
		str_conv_g_nbsig2(par);
	}
}

/*
** Permet de gerer les arrondis dans qui vont aboutir a un chiffre
** significatif en plus (ex 0.9999 > 0.100 ou 0.09999 > 0.0100 avec preci
** de 2).
*/

void	str_conv_g_nbsig(t_elem *par)
{
	int i;
	int nbsig;
	int nbzerbef;

	i = 0;
	nbsig = 0;
	nbzerbef = 0;
	if ((par->b_str)[1] == '0')
		i = 3;
	while ((par->b_str)[i])
	{
		if ((par->b_str)[i] >= '0' && (par->b_str)[i] <= '9')
			nbsig++;
		i++;
	}
	if ((par->b_str)[1] == '0')
	{
		i = 3;
		while ((par->b_str)[i + nbzerbef] && (par->b_str)[i + nbzerbef] == '0')
			nbzerbef++;
		if ((par->b_str)[i + nbzerbef] == '\0')
			nbzerbef = 0;
	}
	str_conv_g_nbsig_suite(par, nbsig, nbzerbef);
}
