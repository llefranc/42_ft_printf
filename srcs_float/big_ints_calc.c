/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_ints_calc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:08:27 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/05 19:17:06 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/float.h"

/*
** Initie la structure pour les bigs ints. s1fird represente la postition
** du premier nombre dans la chaine s1. i represente la place du dernier
** carac de la chaine s1 (donc le dernier chiffre). s2fird et j meme chose
** pour s2.
*/

void	init_num_struct(char *s1, char *s2, t_number *num)
{
	num->i = 0;
	num->j = 0;
	num->s1fird = 0;
	num->s2fird = 0;
	while (s1[num->i])
		num->i++;
	num->i--;
	while (s2[num->j])
		num->j++;
	num->j--;
	while (s1[num->s1fird] && (s1[num->s1fird] == '+'
			|| s1[num->s1fird] == '-'))
		num->s1fird++;
	while (s1[num->s1fird] && s1[num->s1fird] == '0')
		num->s1fird++;
	while (s2[num->s2fird] && (s2[num->s2fird] == '+'
			|| s2[num->s2fird] == '-'))
		num->s2fird++;
	while (s2[num->s2fird] && s2[num->s2fird] == '0')
		num->s2fird++;
}

/*
** Compare deux ints en chaine de carac entre eux en valeur absolue et
** retourne une valeur positive si s1 est plus grand, une valeur negative
** si s1 est plus petit, 0 si s1 == s2.
*/

int		big_int_comp(char *s1, char *s2)
{
	t_number num;

	init_num_struct(s1, s2, &num);
	if ((num.i - num.s1fird) != (num.j - num.s2fird))
		return ((num.i - num.s1fird) - (num.j - num.s2fird));
	while (s1[num.s1fird] == s2[num.s2fird] && s1[num.s1fird] && s2[num.s2fird])
	{
		(num.s1fird)++;
		(num.s2fird)++;
	}
	return ((unsigned char)(s1[num.s1fird]) - (unsigned char)(s2[num.s2fird]));
}

/*
** Permet d'initialiser une chaine big_int nouvellement cree. Ajoute un
** '/0', rempli la chaine de zero et donne un signe a celle-ci en index 0
** en fonction du char '+'ou du char '-'.
*/

char	*big_int_reset(char *str, char signe)
{
	str[BIG_INT] = '\0';
	ft_memset(str, 48, BIG_INT);
	if (signe == '+')
		str[0] = '+';
	if (signe == '-')
		str[0] = '-';
	return (str);
}

/*
** Eleve 2 (contenu dans un big int passe en argument, doit etre unsigned)
** a une puissance valexp unsigned en additionant en boucle le resultat
** (2 + 2 + 4 + 8 + 16....).
*/

char	*pow_table2(char *bigint, unsigned long valexp)
{
	char	pow2_50[BIG_INT + 1];

	if (!valexp)
	{
		big_int_reset(bigint, '+');
		bigint[BIG_INT - 1] = '1';
	}
	else
	{
		while (valexp-- > 1)
		{
			ft_strlcpy(pow2_50, bigint, BIG_INT + 1);
			if (!big_int_add(bigint, pow2_50))
				return (NULL);
		}
	}
	return (bigint);
}

/*
** Transforme la fraction envoyee en ecriture scientifique pour n'avoir
** qu'un seul chiffre avant la virgule. Multiplie denominateur par des
** puissances de 10 si digitexp > 0 (122.5 > 1.225), multiplie numerateur
** par des puissances de 10 si digitexp < 0 (0.024 > 2.4).
*/

void	frac_sci_notation(char *num, char *deno, int digitexp)
{
	char	dix[BIG_INT + 1];

	if (digitexp > 0)
	{
		big_int_reset(dix, '+');
		dix[BIG_INT - digitexp - 1] = '1';
		big_int_mult(deno, dix);
	}
	else if (digitexp < 0)
	{
		big_int_reset(dix, '+');
		dix[BIG_INT + digitexp - 1] = '1';
		big_int_mult(num, dix);
	}
}
