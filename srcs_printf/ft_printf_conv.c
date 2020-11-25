/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:49:24 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/07 15:27:03 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Permet de write le buffer, le memset de '\0' et de remettre l'index
** au debut de la chaine.
*/

void	buf_pri_res(t_elem *par)
{
	write(1, par->b_wri, par->bw);
	ft_memset(par->b_wri, 0, BUFF_SIZE + 1);
	par->bw = 0;
}

/*
** Permet de recuperer les valeurs de la width et de la precision si
** celles-ci sont saisies en argument de printf.
*/

void	get_asterisk(t_elem *par, va_list ap)
{
	if (par->boo_wid == 2)
		par->val_wid = va_arg(ap, int);
	if (par->boo_pre == 2)
		par->val_pre = va_arg(ap, int);
}

/*
** Rempli le buffer pour print avec :
** si nbchar > 0, nbchar fois le char c passe en argument
** si !nbchar, la string str passe en argument.
** Si on arrive a la fin du buffer, on print celui-ci puis on le reset.
** Renvoie la position de b dans le buffer a la fin.
*/

void	buf_fill(t_elem *par, char *str, char c, int nbchar)
{
	int		i;

	i = 0;
	if (nbchar > 0)
	{
		while (nbchar > 0)
		{
			(par->b_wri)[(par->bw)++] = c;
			(par->count)++;
			if (par->bw == BUFF_SIZE)
				buf_pri_res(par);
			nbchar--;
		}
	}
	else if (str)
	{
		while (str[i])
		{
			(par->b_wri)[(par->bw)++] = str[i];
			(par->count)++;
			if (par->bw == BUFF_SIZE)
				buf_pri_res(par);
			i++;
		}
	}
}

/*
** Modifie les parametres de la structure pour simplifier celle-ci en
** fonction des ordres de priorite des flags, de width et precision.
** > si width neg > rev = 1 et wtidh en valeur absolue.
**			si |width| < nb len >>> rev = 0
** > si space et signe >>> space est ignore.
** > si zero et reverse >>> zero est ignore.
** > CHECK flagszero (si precision > 0 flag zero disparait,
**			si width < 0 flagzero disparait)
** > check espace (si nb negatif  ou si width > nblen (sans reverse,
**			sans flagzero, sans .d avec d = 0 (exception!!)), flag espace
**			disparait)
** > si presence flag_signe on diminue width de 1 pour pouvoir afficher
**			celui-ci
*/

void	simp_param(t_elem *par)
{
	if (par->boo_wid && par->val_wid < 0)
	{
		par->fl_rev = 1;
		par->val_wid *= -1;
	}
	if (par->fl_spa && par->fl_sig)
		par->fl_spa = 0;
	if (par->fl_zer)
		if (par->val_wid < 0 || par->fl_rev ||
					(!par->b_str && par->boo_pre && par->val_pre >= 0))
			par->fl_zer = 0;
	if (par->fl_spa && !par->b_str)
		if ((par->b_con)[0] == '-' || (!(par->fl_rev) && !(par->fl_zer)
					&& par->val_wid >= (int)ft_strlen(par->b_con)
					&& !ft_atoi(par->b_con)))
			par->fl_spa = 0;
	if (par->fl_spa && par->b_str)
		if ((par->b_str)[0] == '-')
			par->fl_spa = 0;
	if (par->fl_sig && !par->b_str && (par->b_con)[0] != '-')
		(par->val_wid)--;
}

/*
** Permet d'appeler les differentes fonctions de conversion en fonction
** du parametre recup dans size_type.
*/

void	str_conv(const char *str, t_elem *par, va_list ap, int *s)
{
	(*s)++;
	init_struct(par, 0);
	fill_param(str, s, par);
	!ft_strcmp(par->size_type, "%") ? str_conv_modu(par, ap) : 0;
	!ft_strcmp(par->size_type, "c") ? str_conv_c(par, ap) : 0;
	if (ft_strchr(par->size_type, 'd') || ft_strchr(par->size_type, 'i'))
		return (str_conv_di(par, ap));
	ft_strchr(par->size_type, 'u') ? str_conv_u(par, ap) : 0;
	if (ft_strchr(par->size_type, 'x') || ft_strchr(par->size_type, 'X'))
		return (str_conv_x(par, ap));
	ft_strchr(par->size_type, 'n') ? str_conv_n(par, ap) : 0;
	!ft_strcmp(par->size_type, "p") ? str_conv_p(par, ap) : 0;
	!ft_strcmp(par->size_type, "s") ? str_conv_s(par, ap) : 0;
	ft_strchr(par->size_type, 'f') ? str_conv_f(par, ap) : 0;
	ft_strchr(par->size_type, 'e') ? str_conv_e(par, ap) : 0;
	ft_strchr(par->size_type, 'g') ? str_conv_g(par, ap) : 0;
	!ft_strcmp(par->size_type, "lc") ? str_conv_lc(par, ap) : 0;
	!ft_strcmp(par->size_type, "ls") ? str_conv_ls(par, ap) : 0;
}
