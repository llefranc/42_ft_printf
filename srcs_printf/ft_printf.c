/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:28:27 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/10 16:42:42 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Lance la fonction check de la chaine. Si aucune erreur, lance le print
** de la chaine.
*/

int		ft_printf(const char *str, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, str);
	if (!str_check(str))
		return (-1);
	count = str_print(str, ap);
	va_end(ap);
	return (count);
}

/*
** Avance le long de la chaine et remplit le buffer au fur et a mesure si
** ce sont des chars normaux ou double %%. Si conversion, appelle la fonc
** conv. Reset et print le buffer a chaque fois que l'on arrive a la fin
** de celui-ci ou juste avant de sortir de la boucle quand on arrive a la
** fin de str.
*/

int		str_print(const char *str, va_list ap)
{
	int		s;
	t_elem	par;

	s = 0;
	init_struct(&par, 1);
	while (str[s])
	{
		if (str[s] == '%')
			str_conv(str, &par, ap, &s);
		else
		{
			(par.b_wri)[(par.bw)++] = str[s++];
			par.count++;
		}
		if (par.bw == BUFF_SIZE || (!str[s] && par.bw))
			buf_pri_res(&par);
	}
	return (par.count);
}

/*
** Check la chaine en entier en verifiant la validite des infos rentrees
** apres un '%'. Reinitialise completement la structure stockant les infos
** de conv, la remplit avec tout ce qui suit le '%' (sans faire de va_arg)
** et analyse tous les parametres ensembles pour verifier si c'est une
** conv correct. Si c'est le cas elle passe a la conv suivant, sinon elle
** retourme zero.
*/

int		str_check(const char *str)
{
	int		s;
	t_elem	par;

	s = 0;
	while (str[s])
	{
		if (str[s] == '%')
		{
			s++;
			init_struct(&par, 1);
			fill_param(str, &s, &par);
		}
		else
			s++;
	}
	return (1);
}
