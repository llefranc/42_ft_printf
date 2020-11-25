/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_int_div.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:04:18 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/05 19:16:41 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/float.h"

/*
** Big_int_div permet de realiser des divisions signees entre deux chaines
** de caracteres. Elle retourne NULL et message d'erreur si la chaine s2
** vaut zero, sinon elle retourne s1 avec le resultat de celle-ci. Les 2
** chaines doivent etre de la meme taille, remplie uniquement de chiffre
** avec le signe + ou - precise a l'index 0.
*/

char	*big_int_div(char *s1, char *s2)
{
	t_number	num;
	char		signe;
	char		res[BIG_INT + 1];

	signe = '+';
	big_int_reset(res, '+');
	if (!big_int_comp(res, s2))
	{
		ft_putstr_fd("ERREUR : division par zero\n", 1);
		return (NULL);
	}
	else if (s1[0] != s2[0])
		signe = '-';
	else if (s1[0] == s2[0])
		signe = '+';
	s1[0] = '+';
	s2[0] = '+';
	big_int_div2(s1, s2, res, &num);
	ft_strlcpy(s1, res, BIG_INT + 1);
	s1[0] = signe;
	return (s1);
}

/*
** VRAIE VERSION DE LA DIVISION!!!!!!!!!!!!!!
**void	big_int_div2(char *s1, char *s2, char *res, t_number *num)
**{
**	int		nb;
**	int		len;
**	char	tmp1[BIG_INT + 1];
**	char	tmp2[BIG_INT + 1];
**
**	while (big_int_comp(s1, s2) >= 0)
**	{
**		len = 2;
**		nb = 0;
**		init_num_struct(s1, s2, num);
**		big_int_reset(tmp1, '+');
**		while (big_int_comp(tmp1, s2) < 0)
**		{
**			big_int_reset(tmp1, '+');
**			ft_strlcpy(tmp1 + BIG_INT + 1 - len, s1 + num->s1fird, len);
**			len++;
**		}
**		big_int_reset(tmp2, '+');
**		while (big_int_comp(big_int_add(tmp2, s2), tmp1) <= 0)
**			nb++;
**		big_int_reset(tmp1, '+');
**		printf("place value tmp = %d\n", (num->s1fird + len - 3));
**		tmp1[num->s1fird + len - 3] = nb + 48;
**		big_int_add(res, tmp1);
**		big_int_mult(tmp1, s2);
**		big_int_subs(s1, tmp1);
**	}
**}
*/

/*
** Version optimisee de la division sur bigint pour l'algorithme des floats.
** Celui-ci travaille la majorite du temps avec les 15 premiers chiffres
** des bigints pour obtenir le resultat de la div. Si num[15] / den[15]
** != de num[15] / div[15] + 1, alors on realise des operations cette
** fois sur les bigints pour etre sur du resultat.
*/

void	big_int_div2(char *s1, char *s2, char *res, t_number *num)
{
	long	nb;
	char	tmp[BIG_INT + 1];
	char	numer[16];
	char	denom[16];

	if (big_int_comp(s1, s2) < 0)
		return ;
	init_num_struct(s1, s2, num);
	big_int_div3(numer, denom);
	nb = BIG_INT - num->s2fird;
	if (nb > 15)
		nb = 15;
	ft_strlcpy(denom + 1, s2 + num->s2fird, nb);
	if (num->s1fird == num->s2fird)
		ft_strlcpy(numer + 1, s1 + num->s1fird, nb);
	else
		ft_strlcpy(numer, s1 + num->s1fird, nb + 1);
	if ((ft_atoi(numer) / ft_atoi(denom)) ==
			(ft_atoi(numer) / ((ft_atoi(denom) + 1))))
		nb = ft_atoi(numer) / ft_atoi(denom);
	else
		big_int_div4(s1, s2, tmp, &nb);
	res[BIG_INT - 1] = nb + 48;
}

void	big_int_div3(char numer[], char denom[])
{
	ft_memset(numer, 0, 10);
	ft_memset(denom, 0, 10);
	numer[0] = '0';
	denom[0] = '0';
}

void	big_int_div4(char *s1, char *s2, char *tmp, long *nb)
{
	*nb = 0;
	big_int_reset(tmp, '+');
	while (big_int_comp(big_int_add(tmp, s2), s1) <= 0)
		(*nb)++;
}
