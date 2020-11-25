/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 13:53:01 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/05 19:31:11 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		lennb(unsigned int nb)
{
	int len;

	len = 1;
	while (nb > 9)
	{
		len *= 10;
		nb /= 10;
	}
	return (len);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	temp;
	unsigned int	len;
	char			carac;

	carac = '-';
	temp = n;
	if (n < 0)
	{
		write(fd, &carac, 1);
		temp = -n;
	}
	len = lennb(temp);
	while (len >= 10)
	{
		carac = temp / len + 48;
		write(fd, &carac, 1);
		temp %= len;
		len /= 10;
	}
	carac = temp + 48;
	write(fd, &carac, 1);
}
