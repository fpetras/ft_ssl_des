/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cipher.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 12:41:38 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/10 11:33:09 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	debug(void)
{
	ft_printf("%s\n", g_cmd);
	g_opts[OPT_A] ? ft_printf("-a\n") : 0;
	g_opts[OPT_D] ? ft_printf("-d\n") : 0;
	g_opts[OPT_E] ? ft_printf("-e\n") : 0;
	g_opts[OPT_I] ? ft_printf("-i %s\n", g_input_file) : 0;
	g_opts[OPT_O] ? ft_printf("-o %s\n", g_output_file) : 0;
	g_opts[OPT_K] ? ft_printf("-k %s\n", g_key) : 0;
	g_opts[OPT_P] ? ft_printf("-p %s\n", g_passwd) : 0;
	g_opts[OPT_S] ? ft_printf("-s %s\n", g_salt) : 0;
	g_opts[OPT_V] ? ft_printf("-v %s\n", g_vector) : 0;
	ft_printf("input file: %s\n", g_input_file);
}

int		cipher(void)
{
	if (g_is_base64)
		return (read_base64());
	if (g_is_ecb || g_is_cbc)
		return (des());
	debug();
	return (EXIT_SUCCESS);
}
