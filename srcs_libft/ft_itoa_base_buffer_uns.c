/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_buffer_uns.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:24:56 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/05 19:29:50 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_itoa_base_buffer_uns(unsigned long n, char *buf, const char *base)
{
	unsigned long		temp;
	unsigned long		len;
	unsigned long		basev;

	basev = ft_strlen(base);
	len = 0;
	temp = n;
	while (n > basev - 1)
	{
		n /= basev;
		len++;
	}
	while (temp > basev - 1)
	{
		buf[len--] = base[temp % basev];
		temp /= basev;
	}
	buf[len] = base[temp];
	return (buf);
}
