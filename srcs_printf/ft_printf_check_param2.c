/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_check_param2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:05:20 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/06 16:25:10 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Renvoie zero si flag_rev est associe avec un des types qu'il ne
** prend pas en charge.
*/

int		check_flags_rev(t_elem *par)
{
	if (par->fl_rev)
	{
		if (!strcmp(par->size_type, "n") || !strcmp(par->size_type, "hn")
			|| !strcmp(par->size_type, "hhn"))
			return (0);
	}
	return (1);
}

/*
** Renvoie zero si flag_signed est associe avec un des types qu'il ne
** prend pas en charge.
*/

int		check_flags_signed(t_elem *par)
{
	if (par->fl_sig)
	{
		if (!strcmp(par->size_type, "c") || !strcmp(par->size_type, "n") ||
			!strcmp(par->size_type, "p") || !strcmp(par->size_type, "s") ||
			!strcmp(par->size_type, "u") || !strcmp(par->size_type, "X") ||
			!strcmp(par->size_type, "x") || !strcmp(par->size_type, "hn") ||
			!strcmp(par->size_type, "hu") || !strcmp(par->size_type, "hX") ||
			!strcmp(par->size_type, "hx") || !strcmp(par->size_type, "hhn") ||
			!strcmp(par->size_type, "hhu") || !strcmp(par->size_type, "hhX") ||
			!strcmp(par->size_type, "hhx") || !strcmp(par->size_type, "lc") ||
			!strcmp(par->size_type, "ln") || !strcmp(par->size_type, "ls") ||
			!strcmp(par->size_type, "lu") || !strcmp(par->size_type, "lX") ||
			!strcmp(par->size_type, "lx") || !strcmp(par->size_type, "lln") ||
			!strcmp(par->size_type, "llu") || !strcmp(par->size_type, "llX") ||
			!strcmp(par->size_type, "llx"))
			return (0);
	}
	return (1);
}

/*
** Renvoie zero si flag_hashtag est associe avec un des types qu'il ne
** prend pas en charge.
*/

int		check_flags_hashtag(t_elem *par)
{
	if (par->fl_has)
	{
		if (!strcmp(par->size_type, "c") || !strcmp(par->size_type, "d") ||
			!strcmp(par->size_type, "i") || !strcmp(par->size_type, "n") ||
			!strcmp(par->size_type, "p") || !strcmp(par->size_type, "s") ||
			!strcmp(par->size_type, "u") || !strcmp(par->size_type, "hd") ||
			!strcmp(par->size_type, "hi") || !strcmp(par->size_type, "hn") ||
			!strcmp(par->size_type, "hu") || !strcmp(par->size_type, "hhd") ||
			!strcmp(par->size_type, "hhi") || !strcmp(par->size_type, "hhn") ||
			!strcmp(par->size_type, "hhu") || !strcmp(par->size_type, "lc") ||
			!strcmp(par->size_type, "ld") || !strcmp(par->size_type, "li") ||
			!strcmp(par->size_type, "ln") || !strcmp(par->size_type, "ls") ||
			!strcmp(par->size_type, "lu") || !strcmp(par->size_type, "lld") ||
			!strcmp(par->size_type, "lli") || !strcmp(par->size_type, "lln") ||
			!strcmp(par->size_type, "llu"))
			return (0);
	}
	return (1);
}

/*
** Renvoie zero si flag_space est associe avec un des types qu'il ne
** prend pas en charge.
*/

int		check_flags_space(t_elem *par)
{
	if (par->fl_spa)
	{
		if (!strcmp(par->size_type, "c") || !strcmp(par->size_type, "n") ||
			!strcmp(par->size_type, "p") || !strcmp(par->size_type, "s") ||
			!strcmp(par->size_type, "u") || !strcmp(par->size_type, "X") ||
			!strcmp(par->size_type, "x") || !strcmp(par->size_type, "hn") ||
			!strcmp(par->size_type, "hu") || !strcmp(par->size_type, "hX") ||
			!strcmp(par->size_type, "hx") || !strcmp(par->size_type, "hhn") ||
			!strcmp(par->size_type, "hhu") || !strcmp(par->size_type, "hhX") ||
			!strcmp(par->size_type, "hhx") || !strcmp(par->size_type, "lc") ||
			!strcmp(par->size_type, "ln") || !strcmp(par->size_type, "ls") ||
			!strcmp(par->size_type, "lu") || !strcmp(par->size_type, "lX") ||
			!strcmp(par->size_type, "lx") || !strcmp(par->size_type, "lln") ||
			!strcmp(par->size_type, "llu") || !strcmp(par->size_type, "llX") ||
			!strcmp(par->size_type, "llx"))
			return (0);
	}
	return (1);
}
