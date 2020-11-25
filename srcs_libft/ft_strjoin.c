/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 11:12:23 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/05 19:32:00 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		len;
	int		temp;
	int		i;
	char	*str;

	len = 0;
	temp = 0;
	i = 0;
	while (s1 != NULL && s1[len])
		len++;
	while (s2 != NULL && s2[temp])
		temp++;
	len += temp;
	if ((s1 == NULL && s2 == NULL) || !(str = malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	temp = -1;
	while ((++temp + i) < len && s1 != NULL && s1[temp])
		str[temp] = s1[temp];
	i--;
	while ((temp + ++i) < len && s2 != NULL && s2[i])
		str[temp + i] = s2[i];
	str[temp + i] = 0;
	return (str);
}
