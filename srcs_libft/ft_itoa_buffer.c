/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:14:06 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/05 19:30:06 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_itoa_buffer(long n, char *buffer)
{
	unsigned long	temp;
	unsigned long	temp2;
	unsigned long	len;

	len = 0;
	temp = n;
	if (n < 0)
	{
		len++;
		temp = -n;
		buffer[0] = '-';
	}
	temp2 = temp;
	while (temp2 > 9)
	{
		temp2 /= 10;
		len++;
	}
	while (temp > 9)
	{
		buffer[len--] = (temp % 10) + 48;
		temp /= 10;
	}
	buffer[len] = temp + 48;
	return (buffer);
}
