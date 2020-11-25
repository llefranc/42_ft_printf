/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 18:18:25 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/05 19:17:30 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/float.h"

/*
** Permet de remplir de zeros sur la gauche pour completer le chiffre
** binaire precedemment obtenu, afin d'avoir ainsi une chaine qui
** represente un octet.
*/

char	*fill_zero(char *str)
{
	int		i;
	char	*zero;
	char	*tmp;

	i = 0;
	while (str[i])
		i++;
	if (i == 8)
		return (str);
	if (!(zero = malloc(8 - i + 1)))
		return (NULL);
	zero[8 - i] = '\0';
	ft_memset(zero, 48, 8 - i);
	tmp = zero;
	if (!(zero = ft_strjoin(zero, str)))
		return (NULL);
	free(tmp);
	free(str);
	return (zero);
}

/*
** Affiche la representation memoire du type envoyé en retournant
** une chaine malloc contenant cette representation
*/

char	*str_bits(void *type, size_t size)
{
	char			*rep;
	char			*tmp;
	char			*tmp2;
	unsigned char	*ptr;

	rep = NULL;
	ptr = (unsigned char *)type;
	while (size > 0)
	{
		tmp = NULL;
		if (!(tmp = ft_itoa_base(*ptr, "01")))
			return (NULL);
		if (!(tmp = fill_zero(tmp)))
			return (NULL);
		ptr++;
		size--;
		tmp2 = rep;
		if (!(rep = ft_strjoin(tmp, tmp2)))
			return (NULL);
		free(tmp);
		free(tmp2);
	}
	return (rep);
}

/*
** Affiche la valeur hexa d'un octet
*/

void	print_octet(char *str)
{
	int		i;
	char	*hexa;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		if ((i + 1) % 8 == 0 && str[i + 1])
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
	hexa = ft_convert_base(str, "01", "0123456789abcdef");
	ft_putstr_fd("conv hexa = ", 1);
	ft_putstr_fd(hexa, 1);
	write(1, "\n", 1);
	free(hexa);
}

/*
** Permet de print un double (64 bits) avec la representation
** signe ----- exposant ----- mantissa.
*/

void	print_mantissa(char *str)
{
	int i;

	i = 0;
	write(1, &str[i++], 1);
	write(1, " ", 1);
	while (i < 12)
		write(1, &str[i++], 1);
	write(1, " ", 1);
	while (str[i])
		write(1, &str[i++], 1);
	write(1, "\n", 1);
}
