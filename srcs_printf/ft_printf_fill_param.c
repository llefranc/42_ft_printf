/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fill_param.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 17:57:01 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/06 16:26:47 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Met toutes les var int de la structure a 0. Mets les pointeurs a NULL.
** Memset les chaines sur leur taille entiere avec '\0'. Si on envoie 1,
** la fonction reset aussi les buffers pour ecrire et le compteur
** d'impression.
*/

void	init_struct(t_elem *par, int resall)
{
	if (resall == 1)
	{
		par->count = 0;
		ft_memset(par->b_wri, 0, BUFF_SIZE + 1);
		par->bw = 0;
		ft_memset(par->b_con, 0, BUFF_SIZE + 1);
	}
	par->b_str = NULL;
	ft_memset(par->size_type, 0, 4);
	par->ptr_n = NULL;
	par->boo_pre = 0;
	par->val_pre = 0;
	par->boo_wid = 0;
	par->val_wid = 0;
	par->fl_has = 0;
	par->fl_sig = 0;
	par->fl_zer = 0;
	par->fl_rev = 0;
	par->fl_spa = 0;
}

/*
** appelle toutes les fonctions une par une pour remplir les differents
** champs de la structure
*/

void	fill_param(const char *str, int *i, t_elem *par)
{
	fill_param_flags(str, i, par);
	fill_param_boo_witdh(str, i, par);
	fill_param_boo_preci(str, i, par);
	fill_param_size(str, i, par);
	fill_param_type(str, i, par);
}

/*
** Permet de remplir le champ flags de la structure par
*/

int		fill_param_flags(const char *str, int *i, t_elem *par)
{
	while (str[*i] == '0' || str[*i] == '#'
					|| str[*i] == '+' || str[*i] == '-' || str[*i] == ' ')
	{
		if (str[*i] == '#')
			par->fl_has = 1;
		if (str[*i] == '+')
			par->fl_sig = 1;
		if (str[*i] == '-')
			par->fl_rev = 1;
		if (str[*i] == '0')
			par->fl_zer = 1;
		if (str[*i] == ' ')
			par->fl_spa = 1;
		(*i)++;
	}
	return (1);
}

/*
** Met le champ boo_witdh de la structure par a 1 en fonction de si une
** width est entree ou non (gere l'asterisque).
*/

int		fill_param_boo_witdh(const char *str, int *i, t_elem *par)
{
	char	buff[100];
	size_t	len;

	len = 0;
	ft_memset(buff, 0, 100);
	if (str[*i] == '*')
	{
		par->boo_wid = 2;
		(*i)++;
		return (1);
	}
	while (str[*i + len] >= '0' && str[*i + len] <= '9' && len < 100)
	{
		buff[len] = str[*i + len];
		len++;
	}
	if (len > 0)
	{
		par->boo_wid = 1;
		par->val_wid = ft_atoi(buff);
		*i += len;
	}
	return (1);
}
