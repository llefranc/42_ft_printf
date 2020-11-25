/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fill_param3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 17:56:52 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/06 16:26:54 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Permet de remplir le champ size_type de la structure par avec le
** parametre type a la suite du par size s'il existe.
*/

int		fill_param_type(const char *str, int *i, t_elem *par)
{
	if (str[*i] == 'c')
		return (fill_param_type2('c', i, par));
	else if (str[*i] == 's')
		return (fill_param_type2('s', i, par));
	else if (str[*i] == 'p')
		return (fill_param_type2('p', i, par));
	else if (str[*i] == 'd')
		return (fill_param_type2('d', i, par));
	else if (str[*i] == 'i')
		return (fill_param_type2('i', i, par));
	else if (str[*i] == 'u')
		return (fill_param_type2('u', i, par));
	else if (str[*i] == 'x')
		return (fill_param_type2('x', i, par));
	else if (str[*i] == 'X')
		return (fill_param_type2('X', i, par));
	else if (str[*i] == 'n')
		return (fill_param_type2('n', i, par));
	else if (str[*i] == 'e')
		return (fill_param_type2('e', i, par));
	else if (str[*i] == 'f')
		return (fill_param_type2('f', i, par));
	else if (str[*i] == 'g')
		return (fill_param_type2('g', i, par));
	return (fill_param_type3(str, i, par));
}

int		fill_param_type2(char type, int *i, t_elem *par)
{
	int		len;

	len = 0;
	while ((par->size_type)[len])
		len++;
	(par->size_type)[len] = type;
	(*i)++;
	return (1);
}

int		fill_param_type3(const char *str, int *i, t_elem *par)
{
	if (str[*i] == '%')
		return (fill_param_type2('%', i, par));
	return (1);
}
