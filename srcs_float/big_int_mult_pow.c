/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_int_mult_pow.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 12:27:32 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/02/05 19:16:47 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/float.h"

/*
** Big_int_mult permet de realiser des multiplications signees entre deux
** chaines de caracteres. Elle retourne NULL si la chaine s1 n'est pas
** suffisament grande pour l'operation, sinon elle retourne s1 avec le
** resultat de celle-ci. Les 2 chaines doivent etre de la meme taille,
** remplie uniquement de chiffre avec le signe + ou - precise a l'index 0.
*/

char	*big_int_mult(char *s1, char *s2)
{
	t_number	num;
	char		signe;

	init_num_struct(s1, s2, &num);
	if (num.i < num.s1fird || num.j < num.s2fird)
	{
		ft_memset(s1, 48, BIG_INT);
		s1[0] = '+';
		return (s1);
	}
	else if (s1[0] != s2[0])
		signe = '-';
	else if (s1[0] == s2[0])
		signe = '+';
	if (num.s2fird == (BIG_INT - 2) && s2[num.s2fird] == '1' && s2[num.j] == '0'
			&& num.s1fird > 1)
		big_int_mult3(s1, &num);
	else if (!big_int_mult2(s1, s2, &num))
	{
		ft_putstr_fd("chaine BIG_INT pas assez grande\n", 1);
		return (NULL);
	}
	s1[0] = signe;
	return (s1);
}

char	*big_int_mult2(char *s1, char *s2, t_number *num)
{
	int			nb;
	char		tmp[BIG_INT + 1];
	char		tmp2[BIG_INT + 1];

	big_int_reset(tmp, '+');
	while (num->j >= num->s2fird && (num->i - (BIG_INT - 1 - num->j)) > 1)
	{
		while (num->i >= num->s1fird && (num->i - (BIG_INT - 1 - num->j)) > 1)
		{
			big_int_reset(tmp2, '+');
			nb = s1[num->i] - 48;
			nb *= (s2[num->j] - 48);
			tmp2[num->i - (BIG_INT - 1 - num->j)] = nb % 10 + 48;
			tmp2[num->i - (BIG_INT - 1 - num->j) - 1] = nb / 10 + 48;
			if (!big_int_add(tmp, tmp2))
				return (NULL);
			(num->i)--;
		}
		if ((num->i - (BIG_INT - 1 - num->j)) <= 1)
			return (NULL);
		(num->j)--;
		num->i = BIG_INT - 1;
	}
	ft_strlcpy(s1, tmp, BIG_INT + 1);
	return (s1);
}

/*
** Permet d'accelerer le calcul lors d'une multiplication par 10. Au lieu
** de faire le calcul on decale juste d'un char et on rajoute un 0 a la
** fin (a la place du \0 de ft_strlcpy).
*/

void	big_int_mult3(char *s1, t_number *num)
{
	ft_strlcpy(s1 + num->s1fird - 1, s1 + num->s1fird,
			BIG_INT + 1 - num->s1fird);
	s1[BIG_INT - 1] = '0';
}

/*
** passe la chaine s1 a la puissance pow passee en argument qui se doit
** d'etre non signee. Renvoit la chaine s1, imprime un message d'erreur
** si chaine s1 pas assez grande.
*/

char	*big_int_pow(char *s1, unsigned int pow)
{
	char	signe;
	char	valnb[BIG_INT + 1];

	signe = s1[0];
	s1[0] = '+';
	if (pow == 0)
	{
		big_int_reset(s1, signe);
		s1[BIG_INT - 1] = '1';
		return (s1);
	}
	big_int_reset(valnb, '+');
	if (!big_int_comp(s1, valnb) && pow != 0)
		return (s1);
	ft_strlcpy(valnb, s1, BIG_INT + 1);
	while (pow > 1)
	{
		if (!big_int_mult(s1, valnb))
			return (NULL);
		pow--;
	}
	s1[0] = signe;
	return (s1);
}
