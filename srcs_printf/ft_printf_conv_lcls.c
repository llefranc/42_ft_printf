/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_lcls.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:37:25 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/06 16:26:16 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Permet la conversion de %lc. Converti le caractere widechar en chaine
** de char, puis gere le format comme %c.
*/

void	str_conv_lc(t_elem *par, va_list ap)
{
	par->b_str = NULL;
	get_asterisk(par, ap);
	par->b_str = wchar_to_utf8(va_arg(ap, wchar_t));
	simp_param(par);
	if (!par->fl_rev)
	{
		buf_fill(par, NULL, ' ', par->val_wid - ft_strlen(par->b_str));
		buf_fill_wchar(par, par->b_str);
	}
	else
	{
		buf_fill_wchar(par, par->b_str);
		buf_fill(par, NULL, ' ', par->val_wid - ft_strlen(par->b_str));
	}
	free(par->b_str);
	par->b_str = NULL;
}

/*
** Rempli le buffer pour print les widechar convertis en str.
** Si on arrive a la fin du buffer, on print celui-ci puis on le reset.
** Incremente l'index bw pour se bositionner dans le buffer. Si on detecte
** une sequence sur plusieurs chars (char commence par 110bbbbb minimum),
** on verifie qu'il reste suffisamment de place pour print sans couper au
** maximum 4 chars d'affile.
*/

void	buf_fill_wchar(t_elem *par, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if ((unsigned char)str[i] >= 0xC0 && par->bw > (BUFF_SIZE - 10))
			buf_pri_res(par);
		(par->b_wri)[(par->bw)++] = str[i];
		(par->count)++;
		if (par->bw == BUFF_SIZE)
			buf_pri_res(par);
		i++;
	}
}

/*
** Permet de conv %ls. On essaye d'abord de faire un va_arg. Si on recup
** NULL on l'ecrit dans b_str, sinon on convertit le widechar en chaine
** de char que l'on recupere sur b_str. Si precision insignifiante, on va
** dans convls2 qui fonctionne uniquement par rapport a la taille de str.
** Sinon on va dans convs3 qui fonctionne par rapport a la precision.
*/

void	str_conv_ls(t_elem *par, va_list ap)
{
	wchar_t *tmp;

	par->b_str = NULL;
	ft_memset(par->b_con, 0, BUFF_SIZE + 1);
	get_asterisk(par, ap);
	tmp = va_arg(ap, wchar_t *);
	if (!tmp)
		par->b_str = ft_strdup("(null)");
	else
		par->b_str = wcharstr_to_utf8(tmp);
	simp_param(par);
	if (!par->boo_pre || par->val_pre < 0 || par->val_pre >=
					(int)ft_strlen(par->b_str))
		str_conv_ls2(par);
	else
		str_conv_ls3(par);
	free(par->b_str);
	par->b_str = NULL;
}

/*
** Permet de conv %ls quand la precision est insignificative, et en fonction
** de si l'on doit reverse ou non.
*/

void	str_conv_ls2(t_elem *par)
{
	int i;

	i = 0;
	if (!par->fl_rev)
	{
		buf_fill(par, NULL, ' ', par->val_wid - (int)ft_strlen(par->b_str));
		buf_fill_wchar(par, par->b_str);
	}
	else
	{
		buf_fill_wchar(par, par->b_str);
		buf_fill(par, NULL, ' ', par->val_wid - (int)ft_strlen(par->b_str));
	}
}

/*
** Permet de conv %ls quand la precision est significative, et en fonction
** de si l'on doit reverse ou non.
*/

void	str_conv_ls3(t_elem *par)
{
	int i;

	i = 0;
	if (par->val_pre && (unsigned char)((par->b_str)[par->val_pre]) > 0x7F)
	{
		while (par->val_pre && (unsigned char)((par->b_str)[par->val_pre])
				> 0x7F && (unsigned char)((par->b_str)[par->val_pre]) < 0xC0)
			(par->val_pre)--;
	}
	(par->b_str)[par->val_pre] = '\0';
	if (!par->fl_rev)
	{
		buf_fill(par, NULL, ' ', par->val_wid - par->val_pre);
		buf_fill_wchar(par, par->b_str);
	}
	else
	{
		buf_fill_wchar(par, par->b_str);
		buf_fill(par, NULL, ' ', par->val_wid - par->val_pre);
	}
}
