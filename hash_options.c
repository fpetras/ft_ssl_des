/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 13:39:06 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/29 14:11:28 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	set_option(char opt)
{
	g_opts[OPT_P] = (opt == 'p') ? 1 : g_opts[OPT_P];
	g_opts[OPT_Q] = (opt == 'q') ? 1 : g_opts[OPT_Q];
	g_opts[OPT_R] = (opt == 'r') ? 1 : g_opts[OPT_R];
	g_opts[OPT_S] = (opt == 's') ? 1 : g_opts[OPT_S];
}

static int	parse_hash_options_2(char **av, int i, int j)
{
	if (!ft_strcmp("--", av[i]))
		return (i + 1);
	else if (ft_strchr(HASH_OPT_STR, av[i][j]))
		set_option(av[i][j]);
	else if (!ft_strchr(HASH_OPT_STR, av[i][j]))
		return (illegal_option(av[i][j], av));
	if (!ft_strcmp("-s", av[i]))
		return (i + 1);
	else if (!ft_strncmp("-s", av[i], 2) && ft_strlen(av[i]) >= 3)
	{
		av[i] = &av[i][2];
		return (i);
	}
	return (0);
}

int			parse_hash_options(int ac, char **av)
{
	int i;
	int j;
	int opt_end;

	i = 2;
	ft_bzero(g_opts, sizeof(int) * OPT_NUM);
	while (i < ac)
	{
		j = 1;
		while (av[i][j] && av[i][0] == '-')
		{
			if ((opt_end = parse_hash_options_2(av, i, j)) != 0)
				return (opt_end);
			j++;
		}
		if (av[i][0] != '-' || !ft_strcmp("-", av[i]))
			return (i);
		i++;
	}
	return (i);
}