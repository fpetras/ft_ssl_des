/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:51:45 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/15 12:36:47 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	illegal_option(char opt, char **av)
{
	ft_dprintf(2, "%s: illegal option -- %c\n", av[0], opt);
	print_usage(av);
	return (-1);
}

static void	set_option(char opt)
{
	g_opts[OPT_P] = (opt == 'p') ? 1 : g_opts[OPT_P];
	g_opts[OPT_Q] = (opt == 'q') ? 1 : g_opts[OPT_Q];
	g_opts[OPT_R] = (opt == 'r') ? 1 : g_opts[OPT_R];
	g_opts[OPT_S] = (opt == 's') ? 1 : g_opts[OPT_S];
}

static int	parse_options_2(char **av, int i, int j)
{
	if (!ft_strcmp("--", av[i]))
		return (i + 1);
	else if (ft_strchr(OPT_STR, av[i][j]))
		set_option(av[i][j]);
	else if (!ft_strchr(OPT_STR, av[i][j]))
		return (illegal_option(av[i][j], av));
	if (!ft_strcmp("-s", av[i]))
		return (i + 1);
	else if (!ft_strncmp("-s", av[i], 2) && ft_strlen(av[i]) >= 3)
	{
		av[i] = &av[i][2]; //in order to make -s"string" work
		return (i);
	}
	return (0);
}

int			parse_options(int ac, char **av)
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
			if ((opt_end = parse_options_2(av, i, j)) != 0)
				return (opt_end);
			j++;
		}
		if (av[i][0] != '-' || !ft_strcmp("-", av[i]))
			return (i);
		i++;
	}
	return (i);
}
