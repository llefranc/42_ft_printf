/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchar_conv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:53:15 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/05 19:16:20 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wchar.h"

/*
** Converti un wchar vers une chaine de carac en utf8 si celui-ci
** necessite 1 octet pour etre stocke. Ex : a.
*/

void	conv_utf8_1oct(wchar_t carac, char *str_utf8)
{
	int i;

	i = 0;
	while (str_utf8[i])
		i++;
	str_utf8[i++] = (unsigned int)carac;
}

/*
** Converti un wchar vers une chaine de carac en utf8 si celui-ci
** necessite 2 octets pour etre stocke. Ex : é.
** Forme : 110bbbbb 10bbbbbbb, ou b sont les bits utilises pour
** representer la valeur unicode (ou le wchar cast en unsigned).
** Pour é : unicode value = 233, 11000011 10101001 // c3 a9.
*/

void	conv_utf8_2oct(wchar_t carac, char *str_utf8)
{
	int				i;
	unsigned int	tmp;

	i = 0;
	while (str_utf8[i])
		i++;
	tmp = (unsigned)carac;
	tmp >>= 6;
	str_utf8[i++] = tmp + 0xC0;
	tmp = (unsigned)carac;
	tmp <<= 2;
	tmp &= 0xFF;
	tmp >>= 2;
	str_utf8[i++] = tmp + 0x80;
}

/*
** Converti un wchar vers une chaine de carac en utf8 si celui-ci
** necessite 3 octets pour etre stocke. Ex : ☀.
** Forme : 1110bbbb 10bbbbbbb 10bbbbbbb, ou b sont les bits utilises
** pour representer la valeur unicode (ou le wchar cast en unsigned).
** Pour ☀ : unicode value = 9728, 11100010 10011000 10000000 // e2 98 80.
*/

void	conv_utf8_3oct(wchar_t carac, char *str_utf8)
{
	int				i;
	unsigned int	tmp;

	i = 0;
	while (str_utf8[i])
		i++;
	tmp = (unsigned)carac;
	tmp >>= 12;
	str_utf8[i++] = tmp + 0xE0;
	tmp = (unsigned)carac;
	tmp &= 0xFC0;
	tmp >>= 6;
	str_utf8[i++] = tmp + 0x80;
	tmp = (unsigned)carac;
	tmp &= 0x3F;
	str_utf8[i++] = tmp + 0x80;
}

/*
** Converti un wchar vers une chaine de carac en utf8 si celui-ci
** necessite 4 octets pour etre stocke. Ex : 😍.
** Forme : 11110bbb 10bbbbbbb 10bbbbbbb 10bbbbbbb, ou b sont les bits
** utilises pour representer la valeur unicode (ou le wchar cast en
** unsigned). Pour 😍 : unicode value = 128525,
** 11110000 10011111 10011000 10001101 // f0 9f 98 8d.
*/

void	conv_utf8_4oct(wchar_t carac, char *str_utf8)
{
	int				i;
	unsigned int	tmp;

	i = 0;
	while (str_utf8[i])
		i++;
	tmp = (unsigned)carac;
	tmp >>= 18;
	str_utf8[i++] = tmp + 0xF0;
	tmp = (unsigned)carac;
	tmp &= 0x3F000;
	tmp >>= 12;
	str_utf8[i++] = tmp + 0x80;
	tmp = (unsigned)carac;
	tmp &= 0xFC0;
	tmp >>= 6;
	str_utf8[i++] = tmp + 0x80;
	tmp = (unsigned)carac;
	tmp &= 0x3F;
	str_utf8[i++] = tmp + 0x80;
}
