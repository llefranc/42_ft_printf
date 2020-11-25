/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 18:33:12 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/02/05 19:30:51 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

double	ft_pow(double nb, double power)
{
	if (power > 0)
	{
		while (power > 1)
		{
			nb *= 2;
			power--;
		}
	}
	else if (power < 0)
	{
		while (power < 1)
		{
			nb /= 2;
			power++;
		}
	}
	else
		return ((double)1);
	return (nb);
}
