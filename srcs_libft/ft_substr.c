/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 10:50:08 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/05 19:32:46 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	lentemp;

	i = 0;
	lentemp = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	i = (i < start) ? 1 : 0;
	while (!i && s[start + lentemp] && lentemp < len)
		lentemp++;
	if (!(str = malloc(sizeof(*str) * (lentemp + 1))))
		return (NULL);
	while (i < lentemp && s[(size_t)start + i])
	{
		str[i] = s[(size_t)start + i];
		i++;
	}
	if (!lentemp)
		str[0] = 0;
	else
		str[i] = 0;
	return (str);
}
