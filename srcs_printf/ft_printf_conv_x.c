/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_x.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:31:05 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/06 16:26:37 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Permet de conv %x et X. On recup la conv dans un char, puis on
** effectue le format de celle-ci en fonction de si le flag reverse est
** present ou non. Dans le cas de .x avec x = 0 et preci > 0, on memset
** b_conv pour ne rien afficher. Gere aussi les variantes de size h et l.
*/

void	str_conv_x(t_elem *par, va_list ap)
{
	ft_memset(par->b_con, 0, BUFF_SIZE + 1);
	get_asterisk(par, ap);
	str_conv_x_suite(par, ap);
	simp_param(par);
	if ((par->b_con)[0] == '0')
		par->fl_has = 0;
	if ((par->b_con)[0] == '0' && par->boo_pre && par->val_pre >= 0)
		ft_memset(par->b_con, 0, BUFF_SIZE + 1);
	if (!par->fl_rev)
		str_conv_x2(par);
	else
		str_conv_x3(par);
}

void	str_conv_x_suite(t_elem *par, va_list ap)
{
	if (!strcmp(par->size_type, "x"))
		ft_itoa_base_buffer_uns(va_arg(ap, unsigned int),
					par->b_con, "0123456789abcdef");
	else if (!strcmp(par->size_type, "hx"))
		ft_itoa_base_buffer_uns((unsigned short)va_arg(ap, unsigned int),
					par->b_con, "0123456789abcdef");
	else if (!strcmp(par->size_type, "hhx"))
		ft_itoa_base_buffer_uns((unsigned char)va_arg(ap, unsigned int),
					par->b_con, "0123456789abcdef");
	else if (!strcmp(par->size_type, "X"))
		ft_itoa_base_buffer_uns(va_arg(ap, unsigned int),
					par->b_con, "0123456789ABCDEF");
	else if (!strcmp(par->size_type, "hX"))
		ft_itoa_base_buffer_uns((unsigned short)va_arg(ap, unsigned int),
					par->b_con, "0123456789ABCDEF");
	else if (!strcmp(par->size_type, "hhX"))
		ft_itoa_base_buffer_uns((unsigned char)va_arg(ap, unsigned int),
					par->b_con, "0123456789ABCDEF");
	else if (!strcmp(par->size_type, "lx") || !strcmp(par->size_type, "llx"))
		ft_itoa_base_buffer_uns(va_arg(ap, unsigned long),
					par->b_con, "0123456789abcdef");
	else
		ft_itoa_base_buffer_uns(va_arg(ap, unsigned long),
					par->b_con, "0123456789ABCDEF");
}

/*
** Converti %x et %X lorsque pas de reverse.
** Ordre	print : si fl_zero : has > width || si !flzero :
**					width > has, preci, si
** On diminue width de 2 si on place un has (et que width depasse la
** longueur de nb). Dans le cas de flag zero, si nb est neg on place le
** has, puis on print les zero de width. Le if du par->b_con)[0]
** == '0'  permet de gerer le cas de .x >> x = 0 avec une precision >= 0
** (affiche vide ou des zeros en fonction de la valeur de la precision)
*/

void	str_conv_x2(t_elem *par)
{
	if (par->fl_zer)
		str_conv_x2_suite(par);
	else
	{
		par->fl_has && par->val_wid > (int)ft_strlen(par->b_con) ?
						(par->val_wid) -= 2 : 0;
		if ((int)ft_strlen(par->b_con) > par->val_pre)
			buf_fill(par, NULL, ' ', par->val_wid - (int)ft_strlen(par->b_con));
		else
			buf_fill(par, NULL, ' ', par->val_wid - par->val_pre);
		par->fl_has && ft_strchr(par->size_type, 'x') ?
						buf_fill(par, "0x", 0, 0) : 0;
		par->fl_has && ft_strchr(par->size_type, 'X') ?
						buf_fill(par, "0X", 0, 0) : 0;
	}
	buf_fill(par, NULL, '0', par->val_pre - (int)ft_strlen(par->b_con));
	if ((par->b_con)[0] == '0' && par->boo_pre && par->val_pre >= 0)
		buf_fill(par, NULL, 0, 0);
	else
		buf_fill(par, par->b_con, 0, 0);
}

void	str_conv_x2_suite(t_elem *par)
{
	par->fl_has && ft_strchr(par->size_type, 'x') ?
					buf_fill(par, "0x", 0, 0) : 0;
	par->fl_has && ft_strchr(par->size_type, 'X') ?
					buf_fill(par, "0X", 0, 0) : 0;
	par->fl_has && par->val_wid > (int)ft_strlen(par->b_con) ?
					(par->val_wid) -= 2 : 0;
	if ((int)ft_strlen(par->b_con) > par->val_pre)
		buf_fill(par, NULL, '0', par->val_wid - (int)ft_strlen(par->b_con));
	else
		buf_fill(par, NULL, '0', par->val_wid - par->val_pre);
}

/*
** Converti %x et %X lorsque reverse ou width neg.
** Ordre	print : has, preci, conv, width
** On diminue width de 2 si on place un x0 (et que width depasse la
** longueur de nb), puis on print les zero de preci. Le if du par->b_con)[0]
** == '0'  permet de gerer le cas de .x >> x = 0 avec une precision >= 0
** (affiche vide ou des zeros en fonction de la valeur de la precision)
*/

void	str_conv_x3(t_elem *par)
{
	par->fl_has && ft_strchr(par->size_type, 'x') ?
				buf_fill(par, "0x", 0, 0) : 0;
	par->fl_has && ft_strchr(par->size_type, 'X') ?
				buf_fill(par, "0X", 0, 0) : 0;
	par->fl_has && par->val_wid > (int)ft_strlen(par->b_con) ?
				(par->val_wid) -= 2 : 0;
	buf_fill(par, NULL, '0', par->val_pre - (int)ft_strlen(par->b_con));
	if ((par->b_con)[0] == '0' && par->boo_pre && par->val_pre >= 0)
		buf_fill(par, NULL, 0, 0);
	else
		buf_fill(par, par->b_con, 0, 0);
	if ((int)ft_strlen(par->b_con) > par->val_pre)
		buf_fill(par, NULL, ' ', par->val_wid - (int)ft_strlen(par->b_con));
	else
		buf_fill(par, NULL, ' ', par->val_wid - par->val_pre);
}
