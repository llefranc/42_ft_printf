/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_to_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 16:47:47 by llefranc          #+#    #+#             */
/*   Updated: 2020/11/25 14:00:43 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/float.h"

/*
** Permet de convertir un double (ou float avec une conv implicite quand
** la fonction recoit celui-ci en argument) dans une chaine de char.
** Renvoie NULL si une erreur survient. Travaille avec des BIG_INTS.
** Le signe se trouve a l'index zero de la chaine.
*/

char	*dbltoa(double dbl)
{
	int				digitexp;
	char			numerator[BIG_INT + 1];
	char			denominator[BIG_INT + 1];
	char			*dblchar;
	char			*strbits;

	dblchar = NULL;
	big_int_reset(numerator, '+');
	big_int_reset(denominator, '+');
	if ((dblchar = fill_frac(dbl, numerator, denominator)) != NULL)
		return (dblchar);
	digitexp = get_digit_exp(dbl);
	frac_sci_notation(numerator, denominator, digitexp);
	dblchar = fill_char_double(dblchar, numerator, denominator, digitexp);
	strbits = str_bits(&dbl, sizeof(dbl));
	if (strbits[0] == '0')
		dblchar[0] = '+';
	else
		dblchar[0] = '-';
	free(strbits);
	return (dblchar);
}

/*
** Permet d'initialiser la fraction pour dbltoa en lisant la
** representation memoire d'un double contenue dans une chaine de char que
** renvoie la fonction str_bits et renvoie NULL. Gere aussi les cas
** speciaux (inf et nan), dans ce cas renvoie une chaine contenant le cas.
*/

char	*fill_frac(double dbl, char num[], char den[])
{
	int				valexp;
	unsigned long	valman;
	char			*dblchar;
	char			*strbits;

	dblchar = NULL;
	strbits = str_bits(&dbl, sizeof(dbl));
	valexp = get_val_exp(strbits);
	valman = get_val_man(strbits);
	if (valexp == 972)
		return (fi_inf(dbl, dblchar, strbits, valman));
	fill_numerator(num, valman, valexp);
	fill_denominator(den, valexp, dbl);
	free(strbits);
	return (NULL);
}

char	*fi_inf(double dbl, char *dblchar, char *strbits, unsigned long valman)
{
	if (!(dblchar = malloc(5)))
		return (NULL);
	ft_memset(dblchar, 0, 5);
	if (!valman && dbl > 0)
		ft_strlcpy(dblchar, "inf", 4);
	else if (!valman && dbl < 0)
		ft_strlcpy(dblchar, "-inf", 5);
	else
		ft_strlcpy(dblchar, "nan", 4);
	free(strbits);
	return (dblchar);
}
