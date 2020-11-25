/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_others.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:38:47 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/06 16:26:20 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Permet de gerer la conv de '%'. Gere les flags '0' '-' et la width
** + ' ' # et preci ne font par d'erreur de check et sont juste ignores.
*/

void	str_conv_modu(t_elem *par, va_list ap)
{
	ft_memset(par->b_con, 0, BUFF_SIZE + 1);
	get_asterisk(par, ap);
	(par->b_con)[0] = '%';
	if (par->boo_wid && par->val_wid < 0)
	{
		par->fl_rev = 1;
		par->val_wid *= -1;
	}
	if (!par->fl_rev)
	{
		if (par->fl_zer)
			buf_fill(par, NULL, '0', par->val_wid - 1);
		else
			buf_fill(par, NULL, ' ', par->val_wid - 1);
		buf_fill(par, NULL, '%', 1);
	}
	else
	{
		buf_fill(par, NULL, '%', 1);
		buf_fill(par, NULL, ' ', par->val_wid - (int)ft_strlen(par->b_con));
	}
}

/*
** Permet de gerer le format de +inf ou -inf pour les floats lorsque pas
** de reverse. Ordre print : space > width > signe > inf. On gere de 2
** facons differentes +inf et -inf car la fonction qui convertit les dbl
** renvoit inf pour +inf et -inf pour -inf. Si nan, appelle la fonc
** pour formater les nan. Pour inf a gerer : + ' ' - width
*/

void	str_conv_efg_inf(t_elem *par)
{
	if (!par->fl_rev && (par->b_str)[0] != 'n')
	{
		par->fl_spa ? buf_fill(par, NULL, ' ', 1) : 0;
		par->fl_spa && par->fl_sig && par->val_wid >
				(int)ft_strlen(par->b_str) ? (par->val_wid)-- : 0;
		par->fl_spa && !par->fl_sig && par->val_wid >
				(int)ft_strlen(par->b_str) - 1 ? (par->val_wid)-- : 0;
		if ((par->b_str)[0] == 'i')
			str_conv_efg_inf_suite(par);
		else
		{
			buf_fill(par, NULL, ' ', par->val_wid -
						((int)ft_strlen(par->b_str)));
			buf_fill(par, par->b_str, 0, 0);
		}
	}
	else if (par->fl_rev && (par->b_str)[0] != 'n')
		str_conv_efg_inf2(par);
	else
		str_conv_efg_nan(par);
}

void	str_conv_efg_inf_suite(t_elem *par)
{
	if (par->fl_sig)
		buf_fill(par, NULL, ' ', par->val_wid -
					((int)ft_strlen(par->b_str)) - 1);
	else
		buf_fill(par, NULL, ' ', par->val_wid - ((int)ft_strlen(par->b_str)));
	par->fl_sig ? buf_fill(par, NULL, '+', 1) : 0;
	buf_fill(par, par->b_str, 0, 0);
}

/*
** Permet de gerer le format de +inf ou -inf pour les floats lorsque
** reverse. Ordre print : signe > inf > width.
*/

void	str_conv_efg_inf2(t_elem *par)
{
	par->fl_spa ? buf_fill(par, NULL, ' ', 1) : 0;
	par->fl_spa && par->fl_sig && par->val_wid >
				(int)ft_strlen(par->b_str) ? (par->val_wid)-- : 0;
	par->fl_spa && !par->fl_sig && par->val_wid >
				(int)ft_strlen(par->b_str) - 1 ? (par->val_wid)-- : 0;
	if ((par->b_str)[0] == 'i')
	{
		par->fl_sig ? buf_fill(par, NULL, '+', 1) : 0;
		buf_fill(par, par->b_str, 0, 0);
		if (par->fl_sig)
			buf_fill(par, NULL, ' ', par->val_wid -
					((int)ft_strlen(par->b_str)) - 1);
		else
			buf_fill(par, NULL, ' ', par->val_wid -
					((int)ft_strlen(par->b_str)));
	}
	else
	{
		buf_fill(par, par->b_str, 0, 0);
		buf_fill(par, NULL, ' ', par->val_wid - ((int)ft_strlen(par->b_str)));
	}
}

/*
** Permet de gerer le format des nan pour les floats. Gere - et width.
*/

void	str_conv_efg_nan(t_elem *par)
{
	if (!par->fl_rev)
	{
		buf_fill(par, NULL, ' ', par->val_wid - ((int)ft_strlen(par->b_str)));
		buf_fill(par, par->b_str, 0, 0);
	}
	else
	{
		buf_fill(par, par->b_str, 0, 0);
		buf_fill(par, NULL, ' ', par->val_wid - ((int)ft_strlen(par->b_str)));
	}
}
