/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_int_subs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:47:53 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/05 19:16:51 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/float.h"

/*
** La foonction big_int_subs (et les 6 autres qui en decoulent et qui sont
** necessaires a son fonctionnement) permet de realiser des soustractions
** sur des chaines de carac en realisant l'operation dans s1. Le signe de
** chaque chiffre doit etre precise dans la chaine en position zero de
** celle-ci. Les 2 chaines de caracteres doivent etre de meme longueur et
** ne contenir uniquement que des chiffres excepte pour le signe a l'index
** 0. Si s1 n'est pas assez grande pour contenir le resultat, NULL est renvoye.
*/

char	*big_int_subs(char *s1, char *s2)
{
	t_number	num;

	init_num_struct(s1, s2, &num);
	if (num.i == -1 || num.j == -1 || s2[num.s2fird] == '\0')
		return (s1);
	if (big_int_comp(s1, s2) == 0 && (s1[0] == s2[0]))
		return (big_int_subs3(s1));
	else if (s1[0] == '+' && s2[0] == '-')
		big_int_subs4(s1, s2);
	else if (s1[0] == '+' && s2[0] == '+' && big_int_comp(s1, s2) > 0)
		big_int_subs2(s1, s2, &num);
	else if (s1[0] == '+' && s2[0] == '+' && big_int_comp(s1, s2) < 0)
		big_int_subs5(s1, s2, &num);
	else if (s1[0] == '-' && s2[0] == '+')
		big_int_subs6(s1, s2);
	else if (s1[0] == '-' && s2[0] == '-' && big_int_comp(s1, s2) > 0)
		big_int_subs2(s1, s2, &num);
	else if (s1[0] == '-' && s2[0] == '-' && big_int_comp(s1, s2) < 0)
		big_int_subs7(s1, s2, &num);
	if (num.i == 0 && (num.j != (num.s2fird - 1) || s1[num.i] < '0'))
	{
		ft_putstr_fd("chaine BIG_INT pas assez grande\n", 1);
		return (NULL);
	}
	return (s1);
}

void	big_int_subs2(char *s1, char *s2, t_number *num)
{
	while (num->j >= num->s2fird && num->i != 0)
	{
		if (s1[num->i] < '0')
		{
			s1[num->i] += 10;
			s1[num->i - 1] -= 1;
		}
		if (s1[num->i] - s2[num->j] + 48 >= '0')
		{
			s1[num->i] += -s2[num->j] + 48;
		}
		else if (num->i != 0)
		{
			s1[num->i] += -s2[num->j] + 58;
			s1[num->i - 1] -= 1;
		}
		(num->j)--;
		(num->i)--;
	}
	while (s1[num->i] < '0' && num->i != 0)
	{
		s1[num->i--] += 10;
		s1[num->i] -= 1;
	}
}

char	*big_int_subs3(char *s1)
{
	ft_memset(s1, 48, BIG_INT);
	s1[0] = '+';
	return (s1);
}

void	big_int_subs4(char *s1, char *s2)
{
	char		tmp[BIG_INT + 1];

	ft_memset(tmp, 48, BIG_INT);
	tmp[BIG_INT] = '\0';
	ft_strlcpy(tmp, s2, BIG_INT + 1);
	tmp[0] = '+';
	big_int_add(s1, tmp);
}

void	big_int_subs5(char *s1, char *s2, t_number *num)
{
	char		tmp[BIG_INT + 1];

	ft_memset(tmp, 48, BIG_INT);
	tmp[BIG_INT] = '\0';
	ft_strlcpy(tmp, s1, BIG_INT + 1);
	ft_strlcpy(s1, s2, BIG_INT + 1);
	big_int_subs2(s1, tmp, num);
	s1[0] = '-';
}
