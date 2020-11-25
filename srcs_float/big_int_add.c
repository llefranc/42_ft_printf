/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_int_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 15:59:05 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/05 19:16:36 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/float.h"

/*
** La fonction big_int_add (et les 4 suivantes qui en decoulent et sont
** comprises dans le fonctionnement de celle-ci) permet de realiser des
** addictions signees  entre  2 chaines de caracteres representant des
** chiffres, avec le signe de chacune  precisé a l'index 0. Les 2
** chaines doivent etre de la meme taille et remplies uniquement de
** chiffre (excepte le signe a l'index 0). La chaine s1 est retournee
** avec le resultat de l'addition, NULL si celle-ci n'est pas suffisament
** grande.
*/

char	*big_int_add(char *s1, char *s2)
{
	t_number	num;

	init_num_struct(s1, s2, &num);
	if (num.i == -1 || num.j == -1 || s2[num.s2fird] == '\0')
		return (s1);
	if ((s1[0] == '+' && s2[0] == '+') || (s1[0] == '-' && s2[0] == '-'))
		big_int_add2(s1, s2, &num);
	else if (big_int_comp(s1, s2) == 0 && (s1[0] != s2[0]))
		return (big_int_add3(s1));
	else if (s1[0] == '+' && s2[0] == '-')
		return (big_int_add4(s1, s2));
	else if (s1[0] == '-' && s2[0] == '+')
		return (big_int_add5(s1, s2));
	if (num.i == 0 && (num.j != (num.s2fird - 1) || s1[num.i] > '9'))
	{
		ft_putstr_fd("chaine BIG_INT pas assez grande\n", 1);
		return (NULL);
	}
	return (s1);
}

void	big_int_add2(char *s1, char *s2, t_number *num)
{
	while (num->j >= num->s2fird && num->i != 0)
	{
		if (s1[num->i] > '9')
		{
			s1[num->i] -= 10;
			s1[num->i - 1] += 1;
		}
		if (s1[num->i] + s2[num->j] - 48 <= '9')
			s1[num->i] += s2[num->j] - 48;
		else if (num->i != 0)
		{
			s1[num->i] += s2[num->j] - 58;
			s1[num->i - 1] += 1;
		}
		(num->j)--;
		(num->i)--;
	}
	while (s1[num->i] > '9' && num->i != 0)
	{
		s1[num->i--] -= 10;
		s1[num->i] += 1;
	}
}

char	*big_int_add3(char *s1)
{
	ft_memset(s1, 48, BIG_INT);
	s1[0] = '+';
	return (s1);
}

char	*big_int_add4(char *s1, char *s2)
{
	char		tmp[BIG_INT + 1];

	ft_memset(tmp, 48, BIG_INT);
	tmp[BIG_INT] = '\0';
	ft_strlcpy(tmp, s2, BIG_INT + 1);
	tmp[0] = '+';
	return (big_int_subs(s1, tmp));
}

char	*big_int_add5(char *s1, char *s2)
{
	char		tmp[BIG_INT + 1];

	ft_memset(tmp, 48, BIG_INT);
	tmp[BIG_INT] = '\0';
	ft_strlcpy(tmp, s1, BIG_INT + 1);
	ft_strlcpy(s1, s2, BIG_INT + 1);
	tmp[0] = '+';
	return (big_int_subs(s1, tmp));
}
