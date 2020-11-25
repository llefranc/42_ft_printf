/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_f.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:33:05 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/06 16:25:58 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Permet de conv %f. On recup la conv dans un char, puis on l'arrondit
** par defaut a 6 si preci non saisi ou negative, sinon on arrondit de
** la precision saisie. On rajoute un '.' dans la chaine dblchar si le
** flag '#' est saisi. On formate ensuite en fonction de si on doit rev
** ou pas.
*/

void	str_conv_f(t_elem *par, va_list ap)
{
	int i;

	i = 0;
	ft_memset(par->b_con, 0, BUFF_SIZE + 1);
	get_asterisk(par, ap);
	par->b_str = dbltoa(va_arg(ap, double));
	simp_param(par);
	if (!((par->b_str)[1] >= '0' && (par->b_str)[1] <= '9'))
		str_conv_efg_inf(par);
	else
	{
		if (!par->boo_pre || par->val_pre < 0)
			par->b_str = round_dblstr(par->b_str, 6);
		else
			par->b_str = round_dblstr(par->b_str, par->val_pre);
		if (par->fl_has && par->boo_pre && par->val_pre == 0)
			str_conv_f_suite(par, &i);
		(par->b_str)[0] == '-' ? par->fl_sig = 1 : 0;
		if (!par->fl_rev)
			str_conv_f2(par);
		else
			str_conv_f3(par);
	}
	free(par->b_str);
}

void	str_conv_f_suite(t_elem *par, int *i)
{
	while ((par->b_str)[*i])
		(*i)++;
	(par->b_str)[*i] = '.';
	(par->b_str)[*i + 1] = '\0';
}

/*
** Converti %f lorsque pas de reverse.
** Ordre	print : space, si fl_zero : signe > width || si !flzero :
**					width > signe, conv
** On diminue width de 1 si on place un espace (et que width depasse la
** longueur de b_str (-1 si on ne doit pas print le signe car celui-ci est
** toujours present dans la chaine dblchar)). Dans le cas de flag zero,
** si nb est signe on place le signe, puis on print les zero de width
** (et on retire -1 de ft_strlen de nb si celui-ci est signe)
*/

void	str_conv_f2(t_elem *par)
{
	par->fl_spa ? buf_fill(par, NULL, ' ', 1) : 0;
	par->fl_spa && par->fl_sig && par->val_wid >
					(int)ft_strlen(par->b_str) ? (par->val_wid)-- : 0;
	par->fl_spa && !par->fl_sig && par->val_wid >
					(int)ft_strlen(par->b_str) - 1 ? (par->val_wid)-- : 0;
	if (par->fl_zer)
	{
		par->fl_sig ? buf_fill(par, NULL, (par->b_str)[0], 1) : 0;
		if (par->fl_sig)
			buf_fill(par, NULL, '0', par->val_wid -
							((int)ft_strlen(par->b_str)));
		else
			buf_fill(par, NULL, '0', par->val_wid -
							((int)ft_strlen(par->b_str) - 1));
	}
	else
		str_conv_f2_suite(par);
	buf_fill(par, &((par->b_str)[1]), 0, 0);
}

void	str_conv_f2_suite(t_elem *par)
{
	if (par->fl_sig)
		buf_fill(par, NULL, ' ', par->val_wid - ((int)ft_strlen(par->b_str)));
	else
		buf_fill(par, NULL, ' ', par->val_wid -
						((int)ft_strlen(par->b_str) - 1));
	par->fl_sig ? buf_fill(par, NULL, (par->b_str)[0], 1) : 0;
}

/*
** Converti %f lorsque reverse ou width neg.
** Ordre	print : space, signe, conv, width
** On diminue width de 1 si on place un espace (et que width depasse la
** longueur de nb ou nb -1 en fonction de si l'on doit afficher le signe
** ou non). On place ensuite le signe si on doit, puis la conv et enfin
** la width.
*/

void	str_conv_f3(t_elem *par)
{
	par->fl_spa ? buf_fill(par, NULL, ' ', 1) : 0;
	par->fl_spa && par->fl_sig && par->val_wid >
				(int)ft_strlen(par->b_str) ? (par->val_wid)-- : 0;
	par->fl_spa && !par->fl_sig && par->val_wid >
				(int)ft_strlen(par->b_str) - 1 ? (par->val_wid)-- : 0;
	par->fl_sig ? buf_fill(par, NULL, (par->b_str)[0], 1) : 0;
	buf_fill(par, &((par->b_str)[1]), 0, 0);
	if (par->fl_sig)
		buf_fill(par, NULL, ' ', par->val_wid - ((int)ft_strlen(par->b_str)));
	else
		buf_fill(par, NULL, ' ', par->val_wid -
						((int)ft_strlen(par->b_str) - 1));
}
