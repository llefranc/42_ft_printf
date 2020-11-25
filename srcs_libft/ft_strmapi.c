/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:11:07 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/05 19:32:20 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int				i;
	unsigned int	nb;
	char			*str;

	i = 0;
	nb = 0;
	while (s != NULL && s[i])
		i++;
	if (s == NULL || f == NULL || !(str = malloc(sizeof(*str) * (i + 1))))
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = (*f)(nb++, s[i]);
		i++;
	}
	str[i] = 0;
	return (str);
}
