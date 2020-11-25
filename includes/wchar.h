/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchar.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:30:43 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/05 19:18:38 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WCHAR_H
# define WCHAR_H

# include "ft_printf.h"

char	*wchar_to_utf8(wchar_t carac);
char	*wcharstr_to_utf8(wchar_t *carac);
int		wchar_utf8_len(wchar_t carac);
void	conv_utf8_1oct(wchar_t carac, char *str_utf8);
void	conv_utf8_2oct(wchar_t carac, char *str_utf8);
void	conv_utf8_3oct(wchar_t carac, char *str_utf8);
void	conv_utf8_4oct(wchar_t carac, char *str_utf8);

#endif
