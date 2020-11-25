/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:07:54 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/05 19:28:59 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*octet;
	void	*ptr;
	size_t	i;

	ptr = NULL;
	i = 0;
	if ((size * count) == 0)
	{
		if (!(ptr = malloc(1)))
			return (NULL);
		((char *)ptr)[0] = 0;
	}
	else
	{
		if (!(ptr = malloc(size * count)))
			return (NULL);
		octet = ptr;
		while (i < (count * size))
			octet[i++] = 0;
	}
	return (ptr);
}
