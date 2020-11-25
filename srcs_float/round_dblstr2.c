/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round_dblstr2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:11:09 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/05 19:17:50 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/float.h"

/*
** Permet d'arrondir un float contenu dans une chaine de char en fonction
** d'une precision passee en argument. Si on doit arrondir en dessous,
** on met juste un '\0' en i + 1. Pour arrondir au dessus on appelle la
** fonction round_up. Round laisse toujours le signe. La fonction retourne
** la chaine modifiee, NULL si une erreur survient.
*/

char	*round_dblstr(char *dblchar, int prec)
{
	int i;
	int j;

	i = 0;
	while (dblchar[i] && dblchar[i] != '.')
		i++;
	if (dblchar[i] != '.')
		return (NULL);
	i += prec;
	if (i > MAX_DIGIT - 1)
		return (round_dblstr4(dblchar, i));
	j = i + 1;
	while (dblchar[j] && dblchar[j] == '0')
		j++;
	if (dblchar[j] == '\0')
		dblchar[i + 1] = '\0';
	else
		round_dblstr2(dblchar, prec, i, j);
	round_dblstr3(dblchar, prec);
	return (dblchar);
}

/*
** Suite de la fonction d'arrondi de float. Gere le cas de l'arrondi au
** pair le plus proche si le nombre fini par 5 suivi de 0
** (ex : 0.6250000). 0.625 donnera 0.62, 0.635 donnera 0.64. Gere aussi
** le cas quand le 5 est juste apres la virgule (ex 199.50 donnera 200).
*/

void	round_dblstr2(char *dblchar, int prec, int i, int j)
{
	j = i + 1;
	if (dblchar[j] == '5')
	{
		j++;
		while (dblchar[j] && dblchar[j] == '0')
			j++;
		if (dblchar[j] == '\0')
		{
			if (dblchar[i] == '.' && dblchar[i - 1] % 2 == 1)
				round_up(dblchar, prec, i);
			else if (dblchar[i] % 2 == 1)
				round_up(dblchar, prec, i);
			else
				dblchar[i + 1] = '\0';
		}
		else
			round_up(dblchar, prec, i);
	}
	else if (dblchar[j] > '5')
		round_up(dblchar, prec, i);
	else
		dblchar[i + 1] = '\0';
}

/*
** Permet de faire la mise en forme finale vis-a-vis de la precision
** (fait sauter le point si precision a 0, rajoute des 0 si precision = 5
** et nb = 0.55 >>> 0.55000).
*/

void	round_dblstr3(char *dblchar, int prec)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (dblchar[i] && dblchar[i] != '.')
		i++;
	if (!prec && dblchar[i] == '.')
		dblchar[i] = '\0';
	else
	{
		j = i;
		while (dblchar[j])
			j++;
		if (j - 1 - i != prec)
		{
			ft_memset(dblchar + j, 48, prec + j - 1 - i);
			dblchar[i + prec + 1] = '\0';
		}
	}
}

/*
** Permet de gerer le cas d'une precision plus elevee que la taille de
** la chaine dblchar. Dans ce cas on join en rajoutant des zeros.
*/

char	*round_dblstr4(char *dblchar, int i)
{
	char *tmp;
	char *tmp2;

	if (!(tmp = malloc(sizeof(*tmp) * (i - MAX_DIGIT + 2))))
		return (NULL);
	ft_memset(tmp, '0', i - MAX_DIGIT + 1);
	tmp[i - MAX_DIGIT + 1] = '\0';
	tmp2 = dblchar;
	dblchar = ft_strjoin(dblchar, tmp);
	free(tmp);
	free(tmp2);
	return (dblchar);
}
