/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_s.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:32:00 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/06 16:26:25 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Permet de conv %s. On essaye d'abord de faire un va_arg. Si on recup
** NULL on l'ecrit dans b_conv et on branche b_str sur b_conv, sinon on
** travaille avec b_str. Si precision insignifiante, on va dans convs2
** qui fonctionne uniquement par rapport a la taille de str. Sinon on va
** dans convs3 qui fonctionne par rapport a la precision.
*/

void	str_conv_s(t_elem *par, va_list ap)
{
	ft_memset(par->b_con, 0, BUFF_SIZE + 1);
	get_asterisk(par, ap);
	par->b_str = va_arg(ap, char *);
	simp_param(par);
	if (!(par->b_str))
	{
		ft_strlcpy(par->b_con, "(null)", 7);
		par->b_str = par->b_con;
	}
	if (!par->boo_pre || par->val_pre < 0 || par->val_pre >=
					(int)ft_strlen(par->b_str))
		str_conv_s2(par);
	else
		str_conv_s3(par);
}

/*
** Permet de conv %s quand la precision est insignificative, et en fonction
** de si l'on doit reverse ou non.
*/

void	str_conv_s2(t_elem *par)
{
	int i;
	int size;

	i = 0;
	size = (int)ft_strlen(par->b_str);
	if (!par->fl_rev)
	{
		buf_fill(par, NULL, ' ', par->val_wid - (int)ft_strlen(par->b_str));
		while (i < size)
			buf_fill(par, NULL, (par->b_str)[i++], 1);
	}
	else
	{
		while (i < size)
			buf_fill(par, NULL, (par->b_str)[i++], 1);
		buf_fill(par, NULL, ' ', par->val_wid - (int)ft_strlen(par->b_str));
	}
}

/*
** Permet de conv %s quand la precision est significative, et en fonction
** de si l'on doit reverse ou non.
*/

void	str_conv_s3(t_elem *par)
{
	int i;

	i = 0;
	if (!par->fl_rev)
	{
		buf_fill(par, NULL, ' ', par->val_wid - par->val_pre);
		while (i < par->val_pre)
			buf_fill(par, NULL, (par->b_str)[i++], 1);
	}
	else
	{
		while (i < par->val_pre)
			buf_fill(par, NULL, (par->b_str)[i++], 1);
		buf_fill(par, NULL, ' ', par->val_wid - par->val_pre);
	}
}
