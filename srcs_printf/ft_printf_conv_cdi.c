/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_cdi.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:18:57 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/06 16:25:15 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Converti %c. Gere '-', width.
** Ordre    print : width > conv.
** Ordre  reverse : conv > width.
*/

void	str_conv_c(t_elem *par, va_list ap)
{
	ft_memset(par->b_con, 0, BUFF_SIZE + 1);
	get_asterisk(par, ap);
	(par->b_con)[0] = va_arg(ap, int);
	simp_param(par);
	if (!par->fl_rev)
	{
		buf_fill(par, NULL, ' ', par->val_wid - 1);
		buf_fill(par, NULL, (par->b_con)[0], 1);
	}
	else
	{
		buf_fill(par, NULL, (par->b_con)[0], 1);
		buf_fill(par, NULL, ' ', par->val_wid - 1);
	}
}

/*
** Permet de conv %d et %i. On recup la conv dans un char, puis on
** effectue le format de celle-ci en fonction de si le flag reverse est
** present ou non. Dans le cas de .d avec d = 0 et preci > 0, on memset
** b_conv pour ne rien afficher. Gere aussi les variantes de size h et l.
*/

void	str_conv_di(t_elem *par, va_list ap)
{
	ft_memset(par->b_con, 0, BUFF_SIZE + 1);
	get_asterisk(par, ap);
	if (!strcmp(par->size_type, "d") || !strcmp(par->size_type, "i"))
		ft_itoa_buffer(va_arg(ap, int), par->b_con);
	else if (!strcmp(par->size_type, "hd") || !strcmp(par->size_type, "hi"))
		ft_itoa_buffer((short)va_arg(ap, int), par->b_con);
	else if (!strcmp(par->size_type, "hhd") || !strcmp(par->size_type, "hhi"))
		ft_itoa_buffer((char)va_arg(ap, int), par->b_con);
	else
		ft_itoa_buffer(va_arg(ap, long long), par->b_con);
	simp_param(par);
	if (!ft_atoi(par->b_con) && par->boo_pre && par->val_pre >= 0)
		ft_memset(par->b_con, 0, BUFF_SIZE + 1);
	if (!par->fl_rev)
		str_conv_di2(par);
	else
		str_conv_di3(par);
}

/*
** Converti %d et %i lorsque pas de reverse.
** Ordre	print : space, si fl_zero : signe > width || si !flzero :
**					width > signe, preci, si
** On diminue width de 1 si on place un espace (et que width depasse la
** longueur de nb). Dans le cas de flag zero, si nb est neg on place le
** signe, puis on print les zero de width (et on garde le -1 en plus du
** ft_strlen de nb car on a pas encore retire le 0, et ensuite on decale)
** nb de 1 index pour supprimer le signe. Le if de !ft_atoi
** permet de gerer le cas de .d >> d = 0 avec une precision >= 0 (affiche vide)
*/

void	str_conv_di2(t_elem *par)
{
	par->fl_spa ? buf_fill(par, NULL, ' ', 1) : 0;
	par->fl_spa && par->val_wid > (int)ft_strlen(par->b_con) ?
					(par->val_wid)-- : 0;
	if (par->fl_zer)
	{
		par->fl_sig && ft_atoi(par->b_con) >= 0 ?
					buf_fill(par, NULL, '+', 1) : 0;
		ft_atoi(par->b_con) < 0 ? buf_fill(par, NULL, '-', 1) : 0;
		if ((int)ft_strlen(par->b_con) > par->val_pre)
			buf_fill(par, NULL, '0',
					par->val_wid - (int)ft_strlen(par->b_con));
		else
			buf_fill(par, NULL, '0', par->val_wid - par->val_pre);
	}
	str_conv_di2_suite(par);
}

void	str_conv_di2_suite(t_elem *par)
{
	if (!par->fl_zer)
	{
		ft_atoi(par->b_con) < 0 && par->val_pre >=
					(int)ft_strlen(par->b_con) ? (par->val_wid)-- : 0;
		if ((int)ft_strlen(par->b_con) > par->val_pre)
			buf_fill(par, NULL, ' ', par->val_wid -
					(int)ft_strlen(par->b_con));
		else
			buf_fill(par, NULL, ' ', par->val_wid - par->val_pre);
		par->fl_sig && ft_atoi(par->b_con) >= 0 ?
					buf_fill(par, NULL, '+', 1) : 0;
		ft_atoi(par->b_con) < 0 ? buf_fill(par, NULL, '-', 1) : 0;
	}
	ft_atoi(par->b_con) < 0 ? ft_strlcpy(par->b_con, par->b_con + 1,
					ft_strlen(par->b_con)) : 0;
	buf_fill(par, NULL, '0', par->val_pre - (int)ft_strlen(par->b_con));
	if (!ft_atoi(par->b_con) && par->boo_pre && par->val_pre >= 0)
		buf_fill(par, NULL, 0, 0);
	else
		buf_fill(par, par->b_con, 0, 0);
}

/*
** Converti %d et %i lorsque reverse ou width neg.
** Ordre	print : space, signe, preci, conv, width
** On diminue width de 1 si on place un espace (et que width depasse la
** longueur de nb). Si nb est neg on place le signe, et on diminue width
** de -1, puis on print les zero de preci. Le if du !ft_atoi
** permet de gerer le cas de .d >> d = 0 avec une precision >= 0 (affiche vide)
*/

void	str_conv_di3(t_elem *par)
{
	par->fl_spa ? buf_fill(par, NULL, ' ', 1) : 0;
	par->fl_spa && par->val_wid > (int)ft_strlen(par->b_con) ?
					(par->val_wid)-- : 0;
	par->fl_sig && ft_atoi(par->b_con) >= 0 ? buf_fill(par, NULL, '+', 1) : 0;
	if (ft_atoi(par->b_con) < 0)
	{
		buf_fill(par, NULL, '-', 1);
		(par->val_wid)--;
		ft_strlcpy(par->b_con, par->b_con + 1, ft_strlen(par->b_con));
	}
	buf_fill(par, NULL, '0', par->val_pre - (int)ft_strlen(par->b_con));
	if (!ft_atoi(par->b_con) && par->boo_pre && par->val_pre >= 0)
		buf_fill(par, NULL, 0, 0);
	else
		buf_fill(par, par->b_con, 0, 0);
	if ((int)ft_strlen(par->b_con) > par->val_pre)
		buf_fill(par, NULL, ' ', par->val_wid - (int)ft_strlen(par->b_con));
	else
		buf_fill(par, NULL, ' ', par->val_wid - par->val_pre);
}
