/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:04:19 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/05 19:16:10 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wchar.h"

/*
** Retourne le nombre de char (ou d'octet) que necessite ce wchar pour
** etre converti vers l'utf8. Ex : é est stocke sur 2 octets, a sur 1.
*/

int		wchar_utf8_len(wchar_t carac)
{
	if ((unsigned)carac <= 0x007F)
		return (1);
	else if ((unsigned)carac > 0x007F && (unsigned)carac <= 0x07FF)
		return (2);
	else if ((unsigned)carac > 0x07FF && (unsigned)carac <= 0xFFFF)
		return (3);
	else
		return (4);
}

/*
** Permet de convertir un caractere wchar en un carac utf8 retournee
** dans une chaine de char malloc qui fera entre 1 a 4 char de longueur
** + le '\0'.
*/

char	*wchar_to_utf8(wchar_t carac)
{
	char	*str_utf8;
	int		len;

	len = wchar_utf8_len(carac);
	if (!(str_utf8 = malloc(sizeof(*str_utf8) * (len + 1))))
		return (NULL);
	ft_memset(str_utf8, 0, len + 1);
	if ((unsigned)carac <= 0x007F)
		conv_utf8_1oct(carac, str_utf8);
	else if ((unsigned)carac > 0x007F && (unsigned)carac <= 0x07FF)
		conv_utf8_2oct(carac, str_utf8);
	else if ((unsigned)carac > 0x07FF && (unsigned)carac <= 0xFFFF)
		conv_utf8_3oct(carac, str_utf8);
	else
		conv_utf8_4oct(carac, str_utf8);
	return (str_utf8);
}

/*
** Permet de convertir une chaine wchar en une chaine utf8 retournee
** dans une chaine de char malloc qui fera entre 1 a 4 char de longueur
** pour chaque caractere + le '\0'.
*/

char	*wcharstr_to_utf8(wchar_t *carac)
{
	char	*str_utf8;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (carac[i])
		len += wchar_utf8_len(carac[i++]);
	if (!(str_utf8 = malloc(sizeof(*str_utf8) * (len + 1))))
		return (NULL);
	ft_memset(str_utf8, 0, len + 1);
	i = 0;
	while (carac[i])
	{
		if ((unsigned)carac[i] <= 0x007F)
			conv_utf8_1oct(carac[i], str_utf8);
		else if ((unsigned)carac[i] > 0x007F && (unsigned)carac[i] <= 0x07FF)
			conv_utf8_2oct(carac[i], str_utf8);
		else if ((unsigned)carac[i] > 0x07FF && (unsigned)carac[i] <= 0xFFFF)
			conv_utf8_3oct(carac[i], str_utf8);
		else
			conv_utf8_4oct(carac[i], str_utf8);
		i++;
	}
	return (str_utf8);
}
