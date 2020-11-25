/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 12:46:50 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/05 19:32:42 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		istrim(char carac, const char *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (carac == set[i])
			return (1);
		i++;
	}
	return (0);
}

int		trimvalue(const char *s1, const char *set)
{
	int trim;
	int i;

	if (set == NULL)
		return (0);
	trim = 0;
	i = 0;
	while (s1[i] && istrim(s1[i], set) && (i == 0 || istrim(s1[i - 1], set)))
		i++;
	trim = i;
	if (!s1[i])
		return (trim);
	while (s1[i])
		i++;
	while (--i > 0 && istrim(s1[i], set) && (s1[i + 1] == 0 ||
			istrim(s1[i + 1], set)))
		trim++;
	return (trim);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		trim;
	int		len;
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	trim = trimvalue(s1, set);
	if (!(str = malloc(sizeof(*str) * (len - trim + 1))))
		return (NULL);
	str[len - trim] = 0;
	while (set != NULL && s1[i] && istrim(s1[i], set) &&
			(i == 0 || istrim(s1[i - 1], set)))
		i++;
	trim -= i;
	j = i;
	while (i < (len - trim))
	{
		str[i - j] = s1[i];
		i++;
	}
	return (str);
}
