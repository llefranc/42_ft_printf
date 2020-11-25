/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_e2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:21:41 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/07 18:54:48 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Permet de verifier si le dblchar ne correspond pas a zero, utilise dans
** str_conv_e2 pour une condition d'entree de if.
*/

int		check_zero(char *dblchar)
{
	int i;

	i = 3;
	while (dblchar[i] && dblchar[i] == '0')
		i++;
	return (dblchar[i]);
}
