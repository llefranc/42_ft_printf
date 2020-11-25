/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fill_param2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 17:53:44 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/06 16:26:51 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Met le champ boo_pre de la structure par a 1 ou 2 en fonction de si
** une precision est entree ou non (gere l'asterisque et celui du '.'
** suivi d'un nombre). Si juste le '.' seulement, met le champ de preci a
** 3 (la precision existe mais aucun nombre rentre donc par defaut mis
** a 0).
*/

int		fill_param_boo_preci(const char *str, int *i, t_elem *par)
{
	if (str[*i] == '.' && !((str[*i + 1] >= '0' && str[*i + 1] <= '9')
					|| str[*i + 1] == '*'))
	{
		par->boo_pre = 3;
		(*i)++;
	}
	else if (str[*i] == '.' && str[*i + 1] == '*')
	{
		par->boo_pre = 2;
		(*i) += 2;
	}
	else if (str[*i] == '.')
		fill_param_boo_preci2(str, i, par);
	return (1);
}

void	fill_param_boo_preci2(const char *str, int *i, t_elem *par)
{
	int		len;
	char	buff[100];

	len = 0;
	ft_memset(buff, 0, 100);
	(*i)++;
	while (str[*i + len] >= '0' && str[*i + len] <= '9' && len < 100)
	{
		buff[len] = str[*i + len];
		len++;
	}
	par->boo_pre = 1;
	par->val_pre = ft_atoi(buff);
	*i += len;
}

/*
** Permet de remplir le champ size_type de la structure par avec le
** parametre size.
*/

int		fill_param_size(const char *str, int *i, t_elem *par)
{
	if (str[*i] == 'h' && str[*i + 1] == 'h')
		fill_param_size2(str, i, par, 2);
	else if (str[*i] == 'h')
		fill_param_size2(str, i, par, 1);
	else if (str[*i] == 'l' && str[*i + 1] == 'l')
		fill_param_size2(str, i, par, 2);
	else if (str[*i] == 'l')
		fill_param_size2(str, i, par, 1);
	return (1);
}

void	fill_param_size2(const char *str, int *i, t_elem *par, int nbchar)
{
	if (nbchar == 1)
	{
		(par->size_type)[0] = str[*i];
		(*i)++;
	}
	if (nbchar == 2)
	{
		(par->size_type)[0] = str[*i];
		(par->size_type)[1] = str[(*i) + 1];
		(*i) += 2;
	}
}
