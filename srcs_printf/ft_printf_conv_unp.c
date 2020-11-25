/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_unp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:20:49 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/10 16:25:45 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Permet de conv %u. On recup la conv dans un char, puis on
** effectue le format de celle-ci en fonction de si le flag reverse est
** present ou non. Dans le cas de .u avec u = 0 et preci > 0, on memset
** b_conv pour ne rien afficher. Gere aussi les variantes de size h et l.
*/

void	str_conv_u(t_elem *par, va_list ap)
{
	ft_memset(par->b_con, 0, BUFF_SIZE + 1);
	get_asterisk(par, ap);
	if (!strcmp(par->size_type, "u"))
		ft_itoa_buffer_uns(va_arg(ap, unsigned int), par->b_con);
	else if (!strcmp(par->size_type, "hu"))
		ft_itoa_buffer_uns((unsigned short)va_arg(ap, unsigned int),
					par->b_con);
	else if (!strcmp(par->size_type, "hhu"))
		ft_itoa_buffer_uns((unsigned char)va_arg(ap, unsigned int),
					par->b_con);
	else
		ft_itoa_buffer_uns(va_arg(ap, unsigned long), par->b_con);
	simp_param(par);
	if (!ft_atoi(par->b_con) && par->boo_pre && par->val_pre >= 0)
		ft_memset(par->b_con, 0, BUFF_SIZE + 1);
	if (!par->fl_rev)
		str_conv_u2(par);
	else
		str_conv_u3(par);
}

/*
** Converti %u lorsque pas de reverse.
** Ordre	print : si fl_zero : width zero || si !flzero :
**					width space, preci, conv
** Le if de !ft_atoi permet de gerer le cas de .u >> u = 0 avec une
**  precision >= 0 (affiche vide)
*/

void	str_conv_u2(t_elem *par)
{
	if (par->fl_zer)
	{
		if ((int)ft_strlen(par->b_con) > par->val_pre)
			buf_fill(par, NULL, '0', par->val_wid - (int)ft_strlen(par->b_con));
		else
			buf_fill(par, NULL, '0', par->val_wid - par->val_pre);
	}
	else
	{
		if ((int)ft_strlen(par->b_con) > par->val_pre)
			buf_fill(par, NULL, ' ', par->val_wid - (int)ft_strlen(par->b_con));
		else
			buf_fill(par, NULL, ' ', par->val_wid - par->val_pre);
	}
	buf_fill(par, NULL, '0', par->val_pre - (int)ft_strlen(par->b_con));
	if (!ft_atoi(par->b_con) && par->boo_pre && par->val_pre >= 0)
		buf_fill(par, NULL, 0, 0);
	else
		buf_fill(par, par->b_con, 0, 0);
}

/*
** Converti %u lorsque reverse ou width neg.
** Ordre	print : preci, conv, width
** Le if du !ft_atoi permet de gerer le cas de .u >> u = 0 avec une
** precision >= 0 (affiche vide)
*/

void	str_conv_u3(t_elem *par)
{
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

/*
** Permet de conv %n. on cree les 4 types en fonction de la size de n
** saisi. Et ensuite on fait le va_arg dans la size qui correspond avec
** le cast de count qui correspond.
*/

void	str_conv_n(t_elem *par, va_list ap)
{
	char	*hhn;
	short	*hn;
	int		*n;
	long	*lnlln;

	if (!strcmp(par->size_type, "hhn"))
	{
		hhn = (char *)va_arg(ap, int *);
		hhn ? *hhn = (char)par->count : 0;
	}
	else if (!strcmp(par->size_type, "hn"))
	{
		hn = (short *)va_arg(ap, int *);
		hn ? *hn = (short)par->count : 0;
	}
	else if (!strcmp(par->size_type, "n"))
	{
		n = va_arg(ap, int *);
		n ? *n = (int)par->count : 0;
	}
	else
	{
		lnlln = va_arg(ap, long *);
		lnlln ? *lnlln = (long)par->count : 0;
	}
}

/*
** Permet de conv %p. On recup la conv dans un char apres un itoa base en
** unsigned long, puis on effectue le format de celle-ci en fonction de
** si le flag reverse est present ou non. On affiche toujours avant 0x,
** suivi de la valeur hexa de p. Dans le cas de .p avec p = 0 et
** preci non saisi (donc boo_preci == 3), on memset b_conv pour ne rien
** afficher.
*/

void	str_conv_p(t_elem *par, va_list ap)
{
	ft_memset(par->b_con, 0, BUFF_SIZE + 1);
	get_asterisk(par, ap);
	ft_itoa_base_buffer_uns(va_arg(ap, unsigned long),
					par->b_con, "0123456789abcdef");
	if ((par->b_con)[0] == '0' && par->boo_pre == 3)
		ft_memset(par->b_con, 0, BUFF_SIZE + 1);
	simp_param(par);
	par->fl_has = 1;
	if (!par->fl_rev)
	{
		par->fl_has && par->val_wid > (int)ft_strlen(par->b_con) ?
						(par->val_wid) -= 2 : 0;
		buf_fill(par, NULL, ' ', par->val_wid - (int)ft_strlen(par->b_con));
		par->fl_has ? buf_fill(par, "0x", 0, 0) : 0;
		buf_fill(par, par->b_con, 0, 0);
	}
	else
	{
		par->fl_has ? buf_fill(par, "0x", 0, 0) : 0;
		par->fl_has && par->val_wid > (int)ft_strlen(par->b_con) ?
						(par->val_wid) -= 2 : 0;
		buf_fill(par, par->b_con, 0, 0);
		buf_fill(par, NULL, ' ', par->val_wid - (int)ft_strlen(par->b_con));
	}
}
