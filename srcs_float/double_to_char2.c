/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_to_char2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:13:45 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/05 19:17:40 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/float.h"

/*
** Renvoie un char contenant le double qu'il faudra free. Ne gere pas le
** signe, il faut ensuite le rajouter a l'index 0 de dbl. Renvoie NULL si
** une erreur occure. digitexp permet d'obtenir la place de la virgule et
** de remplir precedemment de 0 si dbl < 1 et > 0. Si digitexp = 0
** (ex: 1.2), il faut realiser manuellement le premier tour de boucle dans
** fill4 pour remplir le premier digit et placer len juste apres le point
** pour pouvoir continuer.
*/

char	*fill_char_double(char *dbl, char *num, char *deno, int digitexp)
{
	int		len;
	char	tmp[BIG_INT + 1];
	char	dix[BIG_INT + 1];
	char	zero[BIG_INT + 1];

	len = 1;
	if (!(dbl = fill_char_double2(dix, zero, &digitexp, &len)))
		return (NULL);
	if (!digitexp)
		len = fill_char_double4(dbl, num, deno);
	else if (digitexp < 0)
		digitexp = 0;
	while (big_int_comp(num, zero) != 0 && len < MAX_DIGIT)
	{
		big_int_reset(tmp, '+');
		ft_strlcpy(tmp, num, BIG_INT + 1);
		if (!big_int_div(tmp, deno))
			return (NULL);
		dbl[len++] = tmp[BIG_INT - 1];
		while (tmp[BIG_INT - 1]-- != '0')
			big_int_subs(num, deno);
		big_int_mult(num, dix);
		fill_char_double3(dbl, num, &len, &digitexp);
	}
	return (dbl);
}

/*
** Permet d'initiliaser les differentes chaines, place la virgule et
** rajoute des zero pour les dbl < 1 et > 0.
*/

char	*fill_char_double2(char dix[], char zero[], int *digitexp, int *len)
{
	char *dbl;

	if (!(dbl = malloc(sizeof(*dbl) * (MAX_DIGIT + 1))))
		return (NULL);
	dbl[MAX_DIGIT] = '\0';
	ft_memset(dbl, 48, MAX_DIGIT);
	if (*digitexp < 0)
	{
		dbl[++(*len)] = '.';
		while (*len - 2 < -(*digitexp))
			(*len)++;
	}
	else if (!(*digitexp))
		dbl[++(*len)] = '.';
	big_int_reset(dix, '+');
	dix[BIG_INT - 2] = '1';
	big_int_reset(zero, '+');
	return (dbl);
}

/*
** Permet de placer la virgule (juste pour gagner place pour respecter
** la norme).
*/

void	fill_char_double3(char *dbl, char *num, int *len, int *digitexp)
{
	char	zero[BIG_INT + 1];
	int		i;

	i = 0;
	big_int_reset(zero, '+');
	if (*len - 1 > *digitexp && *digitexp)
	{
		dbl[(*len)++] = '.';
		*digitexp = 0;
	}
	if (!big_int_comp(num, zero))
	{
		while (dbl[i] && dbl[i] != '.')
			i++;
		if (!dbl[i])
			dbl[*digitexp + 2] = '.';
	}
}

/*
** Permet de gerer le cas ou digitexp est = 0. En effet la boucle va
** qui suit dans fill_char_double va commencer a remplir apres le '.' et
** ne va pas traiter le premier digit. La fonction ci-dessous permet de
** realiser ce premier tour de boucle.
*/

int		fill_char_double4(char *dbl, char *num, char *deno)
{
	int		len;
	char	tmp[BIG_INT + 1];
	char	dix[BIG_INT + 1];

	len = 1;
	big_int_reset(tmp, '+');
	big_int_reset(dix, '+');
	dix[BIG_INT - 2] = '1';
	ft_strlcpy(tmp, num, BIG_INT + 1);
	big_int_div(tmp, deno);
	dbl[len] = tmp[BIG_INT - 1];
	while (tmp[BIG_INT - 1]-- != '0')
		big_int_subs(num, deno);
	big_int_mult(num, dix);
	return (3);
}
