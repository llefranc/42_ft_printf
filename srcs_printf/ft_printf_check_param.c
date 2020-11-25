/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_check_param.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 19:27:31 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/06 16:25:07 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Appelle toutes les fonctions une par une pour checker chaque parametre
** de la structure.
*/

int		check_param(t_elem *par)
{
	if (!check_size_type(par) || !check_precision(par) || !check_width(par) ||
		!check_flags_zero(par) || !check_flags_rev(par) ||
		!check_flags_signed(par) ||
		!check_flags_hashtag(par) || !check_flags_space(par))
		return (0);
	return (1);
}

/*
** Renvoie zero si size_type ne correspond avec aucun des types existant.
*/

int		check_size_type(t_elem *par)
{
	if (!(par->size_type)[0])
		return (0);
	if (!strcmp(par->size_type, "c") || !strcmp(par->size_type, "d") ||
		!strcmp(par->size_type, "e") || !strcmp(par->size_type, "f") ||
		!strcmp(par->size_type, "g") || !strcmp(par->size_type, "i") ||
		!strcmp(par->size_type, "n") || !strcmp(par->size_type, "p") ||
		!strcmp(par->size_type, "s") || !strcmp(par->size_type, "u") ||
		!strcmp(par->size_type, "X") || !strcmp(par->size_type, "x") ||
		!strcmp(par->size_type, "hd") || !strcmp(par->size_type, "hi") ||
		!strcmp(par->size_type, "hn") || !strcmp(par->size_type, "hu") ||
		!strcmp(par->size_type, "hX") || !strcmp(par->size_type, "hx") ||
		!strcmp(par->size_type, "hhd") || !strcmp(par->size_type, "hhi") ||
		!strcmp(par->size_type, "hhn") || !strcmp(par->size_type, "hhu") ||
		!strcmp(par->size_type, "hhX") || !strcmp(par->size_type, "hhx") ||
		!strcmp(par->size_type, "lc") || !strcmp(par->size_type, "ld") ||
		!strcmp(par->size_type, "le") || !strcmp(par->size_type, "lf") ||
		!strcmp(par->size_type, "lg") || !strcmp(par->size_type, "li") ||
		!strcmp(par->size_type, "ln") || !strcmp(par->size_type, "ls") ||
		!strcmp(par->size_type, "lu") || !strcmp(par->size_type, "lX") ||
		!strcmp(par->size_type, "lx") || !strcmp(par->size_type, "lld") ||
		!strcmp(par->size_type, "lli") || !strcmp(par->size_type, "lln") ||
		!strcmp(par->size_type, "llu") || !strcmp(par->size_type, "llX") ||
		!strcmp(par->size_type, "llx") || !strcmp(par->size_type, "%"))
		return (1);
	return (0);
}

/*
** Renvoie zero si precision est associee avec un des types qu'elle ne
** prend pas en charge. Gere les exceptions du '.' seulement avec une preci
** qui vaut donc zero par defaut.
*/

int		check_precision(t_elem *par)
{
	if (par->boo_pre == 1 || par->boo_pre == 2)
	{
		if (!strcmp(par->size_type, "c") || !strcmp(par->size_type, "n") ||
			!strcmp(par->size_type, "p") || !strcmp(par->size_type, "hn") ||
			!strcmp(par->size_type, "hhn") || !strcmp(par->size_type, "lc") ||
			!strcmp(par->size_type, "ln") || !strcmp(par->size_type, "lln"))
			return (0);
	}
	return (1);
}

/*
** Renvoie zero si width est associee avec un des types qu'elle ne
** prend pas en charge.
*/

int		check_width(t_elem *par)
{
	if (par->boo_wid == 1 || par->boo_wid == 2)
	{
		if (!strcmp(par->size_type, "n") || !strcmp(par->size_type, "hn") ||
			!strcmp(par->size_type, "hhn"))
			return (0);
	}
	return (1);
}

/*
** Renvoie zero si flag_zero est associee avec un des types qu'il ne
** prend pas en charge.
*/

int		check_flags_zero(t_elem *par)
{
	if (par->fl_zer)
	{
		if (!strcmp(par->size_type, "c") || !strcmp(par->size_type, "n") ||
			!strcmp(par->size_type, "p") || !strcmp(par->size_type, "s") ||
			!strcmp(par->size_type, "hn") || !strcmp(par->size_type, "hhn") ||
			!strcmp(par->size_type, "lc") || !strcmp(par->size_type, "ln") ||
			!strcmp(par->size_type, "ls") || !strcmp(par->size_type, "lln"))
			return (0);
	}
	return (1);
}
