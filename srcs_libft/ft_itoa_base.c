/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:24:56 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/05 19:29:56 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*mallocstb(unsigned long temp, unsigned long *len, unsigned long basev)
{
	char	*str;

	while (temp > basev - 1)
	{
		temp /= basev;
		*len += 1;
	}
	if (!(str = malloc(sizeof(*str) * (*len + 1))))
		return (NULL);
	str[*len] = 0;
	*len -= 1;
	return (str);
}

char	*ft_itoa_base(long n, const char *base)
{
	char				*str;
	unsigned long		temp;
	unsigned long		len;
	unsigned long		basev;

	basev = ft_strlen(base);
	len = 1;
	temp = n;
	if (n < 0)
	{
		len++;
		temp = -n;
	}
	if (!(str = mallocstb(temp, &len, basev)))
		return (NULL);
	if (n < 0)
		str[0] = '-';
	while (temp > basev - 1)
	{
		str[len--] = base[temp % basev];
		temp /= basev;
	}
	str[len] = base[temp];
	return (str);
}
