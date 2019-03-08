/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:38:48 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/08 11:08:05 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int			ft_md5(int ac, char **av)
{
	char *input;

	(void)av;
	if (ac == 0 || g_opts[OPT_P])
	{
		input = read_stdin();
		g_opts[OPT_P] ? ft_printf("%s\n", input) : 0;
		free(input);
	}
	//print options
	ft_printf("options:\n");
	g_opts[OPT_P] ? ft_printf("-p\n") : 0;
	g_opts[OPT_Q] ? ft_printf("-q\n") : 0;
	g_opts[OPT_R] ? ft_printf("-r\n") : 0;
	g_opts[OPT_S] ? ft_printf("-s\n") : 0;
	//print remaining args
	ft_printf("args:\n");
	for (int i = 0; i < ac; i++)
		ft_printf("%s\n", av[i]);
	return (0);
}
