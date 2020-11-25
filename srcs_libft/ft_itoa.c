/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:14:06 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/05 19:30:14 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*mallocstr(unsigned long temp, unsigned long *len)
{
	char *str;

	while (temp > 9)
	{
		temp /= 10;
		*len += 1;
	}
	if (!(str = malloc(sizeof(*str) * (*len + 1))))
		return (NULL);
	str[*len] = 0;
	*len -= 1;
	return (str);
}

char	*ft_itoa(long n)
{
	char			*str;
	unsigned long	temp;
	unsigned long	len;

	len = 1;
	temp = n;
	if (n < 0)
	{
		len++;
		temp = -n;
	}
	if (!(str = mallocstr(temp, &len)))
		return (NULL);
	if (n < 0)
		str[0] = '-';
	while (temp > 9)
	{
		str[len--] = (temp % 10) + 48;
		temp /= 10;
	}
	str[len] = temp + 48;
	return (str);
}
