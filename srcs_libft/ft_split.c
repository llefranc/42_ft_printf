/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 13:15:20 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/05 19:31:33 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		issep(char carac, char sep)
{
	if (carac == sep)
		return (1);
	return (0);
}

int		wordcount(const char *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s != NULL && s[i])
	{
		if (!issep(s[i], c) && (i == 0 || issep(s[i - 1], c)))
			count++;
		i++;
	}
	return (count);
}

char	**filltab(char **tab, const char *s, char c, int *nbmallocs)
{
	int i;
	int len;
	int words;

	i = 0;
	words = 0;
	while (s[i])
	{
		len = 0;
		while (issep(s[i], c))
			i++;
		if (s[i] && !issep(s[i], c))
		{
			while (s[i + len] && !issep(s[i + len], c))
				len++;
			if (!(tab[words] = malloc(sizeof(*tab) * (len + 1))))
				return (NULL);
			*nbmallocs += 1;
			len = 0;
			while (s[i] && !issep(s[i], c))
				tab[words][len++] = s[i++];
			tab[words++][len] = 0;
		}
	}
	return (tab);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	int		words;
	int		i;

	i = 0;
	words = wordcount(s, c);
	if (s == NULL || !(tab = malloc(sizeof(*tab) * (words + 1))))
		return (NULL);
	while (i++ <= words)
		tab[words] = NULL;
	words = 0;
	i = 0;
	tab = filltab(tab, s, c, &words);
	if (tab == NULL)
		while (i < words)
			free(tab[i]);
	return (tab);
}
