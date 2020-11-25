/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round_dblstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 18:47:43 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/05 19:17:47 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/float.h"

/*
** Permet d'arrondir de +1 la partie entiere d'un nombre decimal stocke
** sur une chaine de char. Si le nombre ne prend pas une puissance de 10
** (ex 996 devient 997), on arrondit et on finit la chaine apres le '.'.
** Dams le cas contraire (999 > 1000), on decale la partie decimale en
** incluant le point (pour garder celui ci), puis on copie 1000 dans la
** chaine et on ajoute un '\0' derriere le '.' (on obtient donc 1000.).
*/

void	round_up_int(char *dblchar, char tmp[], int len, int i)
{
	char	un[BIG_INT + 1];

	big_int_reset(un, '+');
	un[BIG_INT - 1] = '1';
	len = --i;
	ft_strlcpy(tmp + BIG_INT - len, dblchar + 1, len + 1);
	big_int_add(tmp, un);
	if (tmp[BIG_INT - len - 1] == '0')
	{
		ft_memmove(dblchar + 1, tmp + BIG_INT - len, len);
		dblchar[i + 2] = '\0';
	}
	else
	{
		ft_memmove(dblchar + i + 2, dblchar + i + 1, BIG_INT - i - 2);
		ft_memmove(dblchar + 1, tmp + BIG_INT - len - 1, len + 1);
		dblchar[i + 3] = '\0';
	}
}

/*
** Permet d'arrondir un nombre decimale contenu dans une chaine de char
** de +1 en fonction de la precision passee en argument. Si l'arrondie de
** la partie decimale resulte de +1 pour la partie entiere, la fonction
** recurse en envoyant 0 en precision cette fois pour arrondir de 1 la
** partie entiere.
*/

void	round_up(char *dblchar, int prec, int i)
{
	char	tmp[BIG_INT + 1];
	char	un[BIG_INT + 1];
	int		len;

	len = 0;
	big_int_reset(tmp, '+');
	big_int_reset(un, '+');
	un[BIG_INT - 1] = '1';
	if (prec == 0)
		round_up_int(dblchar, tmp, len, i);
	else
	{
		while (dblchar[i - len] != '.')
			len++;
		ft_strlcpy(tmp + BIG_INT - len, dblchar + i - len + 1, len + 1);
		big_int_add(tmp, un);
		if (tmp[BIG_INT - len - 1] == '0')
			ft_strlcpy(dblchar + i - len + 1, tmp + BIG_INT - len, len + 1);
		else
			round_up(dblchar, 0, i - len);
	}
}
