/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_int_subs2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:47:53 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/05 19:16:55 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/float.h"

void	big_int_subs6(char *s1, char *s2)
{
	char		tmp[BIG_INT + 1];

	ft_memset(tmp, 48, BIG_INT);
	tmp[BIG_INT] = '\0';
	ft_strlcpy(tmp, s2, BIG_INT + 1);
	tmp[0] = '-';
	big_int_add(s1, tmp);
}

void	big_int_subs7(char *s1, char *s2, t_number *num)
{
	char		tmp[BIG_INT + 1];

	ft_memset(tmp, 48, BIG_INT);
	tmp[BIG_INT] = '\0';
	ft_strlcpy(tmp, s1, BIG_INT + 1);
	ft_strlcpy(s1, s2, BIG_INT + 1);
	big_int_subs2(s1, tmp, num);
	s1[0] = '+';
}
