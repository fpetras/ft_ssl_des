/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:54:09 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/28 12:39:48 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		print_usage(char **av)
{
	ft_dprintf(2, "usage: %s <command> [options] [<arg>...]\n", av[0]);
	ft_dprintf(2, "\n%sCOMMANDS:%s\n", WHITE, TEXT_RESET);
	ft_dprintf(2, "     md5\n");
	ft_dprintf(2, "     sha224 sha256 sha384 sha512 sha512224 sha512256\n");
	ft_dprintf(2, "\n%sOPTIONS%s\n", WHITE, TEXT_RESET);
	ft_dprintf(2, "     -p            echo stdin to stdout and append ");
	ft_dprintf(2, "checksum to stdout\n");
	ft_dprintf(2, "     -q            quiet mode\n");
	ft_dprintf(2, "     -r            reverse the format of the output\n");
	ft_dprintf(2, "     -s string     print the sum of the given string\n");
}

static int	error(int ac, char **av)
{
	if (ac == 1)
	{
		print_usage(av);
		return (EXIT_FAILURE);
	}
	else if (ac >= 2 &&
			(ft_strcasecmp("md5", av[1]) && ft_strcasecmp("sha224", av[1]) &&
			ft_strcasecmp("sha256", av[1]) && ft_strcasecmp("sha384", av[1]) &&
			ft_strcasecmp("sha512", av[1]) &&
			ft_strcasecmp("sha512224", av[1]) &&
			ft_strcasecmp("sha512256", av[1])))
	{
		ft_dprintf(2, "ft_ssl:Error: '%s' is an invalid command.\n", av[1]);
		ft_dprintf(2, "\nStandard commands:\n");
		ft_dprintf(2, "\nMessage Digest commands:\n");
		ft_dprintf(2, "md5\nsha224\nsha256\nsha384\nsha512\n");
		ft_dprintf(2, "sha512224\nsha512256\n");
		ft_dprintf(2, "\nCipher commands:\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int			main(int ac, char **av)
{
	int i;

	if (error(ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	g_cmd = av[1];
	if ((i = parse_options(ac, av)) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!ft_strcasecmp("md5", av[1]) || !ft_strncasecmp("sha", av[1], 3))
		return (hash(ac - i, &av[i]));
	return (EXIT_SUCCESS);
}
