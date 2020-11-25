/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_ints_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:59:31 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/05 19:17:11 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/float.h"

/*
** Permet de recuperer la valeur de l'exposant d'un double (stockee sur 11
** bits). Biaise celui-ci de -1075 si c'est un normalise (valeur pour des
** floats sur 64 bits), sinon de -1074 si c'est un denormalize.
*/

int				get_val_exp(char *strbits)
{
	char	*tmp;
	char	*expb10;
	int		valexp;

	if (!(tmp = ft_substr(strbits, 1, 11)))
		return (-1);
	if (!(expb10 = ft_convert_base(tmp, "01", "0123456789")))
		return (-1);
	valexp = ft_atoi(expb10);
	if (!valexp)
		valexp -= 1074;
	else
		valexp -= 1075;
	free(expb10);
	free(tmp);
	return (valexp);
}

/*
** Permet de recuperer la valeur de la mantissa stockee sur 52 bits pour
** les double en fonction de la valeur de l'exp. Si celui ci vaut 0 (non
** biaisee) alors on a un nombre denormalize et on n'ajoute pas 2^52
*/

unsigned long	get_val_man(char *strbits)
{
	char			*tmpman;
	char			*tmpexp;
	char			*manb10;
	char			*tmpb10;
	unsigned long	valman;

	if (!(tmpman = ft_substr(strbits, 12, 52)))
		return (-1);
	if (!(manb10 = ft_convert_base(tmpman, "01", "0123456789")))
		return (-1);
	if (!(tmpexp = ft_substr(strbits, 1, 11)))
		return (-1);
	if (!(tmpb10 = ft_convert_base(tmpexp, "01", "0123456789")))
		return (-1);
	valman = ft_atoi(manb10);
	if (ft_atoi(tmpexp) && (ft_atoi(tmpb10) - 1075) != 972)
		valman += (long)ft_pow(2, 52);
	free(manb10);
	free(tmpman);
	free(tmpexp);
	free(tmpb10);
	return (valman);
}

/*
** Initialise la valeur du numerateur qui est un big int dans un chaine.
** Rempli celui-ci en fonction de valexp. Si valexp > 0 :
** mantissa * 2^exponent. Sinon num = mantissa.
*/

char			*fill_numerator(char *num, unsigned long valman, long valexp)
{
	char	*tmp;
	char	exponent[BIG_INT + 1];

	if (!(tmp = ft_itoa(valman)))
		return (NULL);
	if (ft_strlen(tmp) >= BIG_INT)
	{
		ft_putstr_fd("chaine BIG_INT pas assez grande\n", 1);
		return (NULL);
	}
	if (valexp > 0)
	{
		ft_strlcpy(num + BIG_INT - ft_strlen(tmp), tmp, ft_strlen(tmp) + 1);
		big_int_reset(exponent, '+');
		exponent[BIG_INT - 1] = '2';
		if (!pow_table2(exponent, valexp))
			return (NULL);
		big_int_mult(num, exponent);
	}
	else
		ft_strlcpy(num + BIG_INT - ft_strlen(tmp), tmp, ft_strlen(tmp) + 1);
	free(tmp);
	return (num);
}

/*
** Initialise la valeur du denominateur qui est un big int dans un chaine.
** Rempli celui-ci en fonction de valexp. Si valexp > 0 : deno = 1.
** Sinon deno = 2 ^ -valexp. Si le double = 0, alors on mets le
** denominateur a 1 pour eviter de calculer la puissance de 2 (car 0 a un
** exp de -1074).
*/

char			*fill_denominator(char *deno, long valexp, double nb)
{
	if (valexp > 0)
	{
		big_int_reset(deno, '+');
		deno[BIG_INT - 1] = '1';
	}
	else if (nb != 0)
	{
		big_int_reset(deno, '+');
		deno[BIG_INT - 1] = '2';
		if (!pow_table2(deno, -valexp))
			return (NULL);
	}
	else
	{
		big_int_reset(deno, '+');
		deno[BIG_INT - 1] = '1';
	}
	return (deno);
}

/*
** Renvoit un int positif ou negatif en fonction du nombre de fois qu'il
** faudrait diviser par 10 ou multiplier par 10 un chiffre pour n'avoir
** qu'un seul digit avant la virgule. Permet ainsi d'ecrire en notation
** scientifique.
*/

int				get_digit_exp(double nb)
{
	int digitexp;

	digitexp = 0;
	if (nb < 0)
		nb = -nb;
	if (nb >= 10)
	{
		while (nb >= 10)
		{
			nb /= 10;
			digitexp++;
		}
	}
	else if (nb < 1 && nb != 0)
	{
		while (nb < 1)
		{
			nb *= 10;
			digitexp--;
		}
	}
	return (digitexp);
}
