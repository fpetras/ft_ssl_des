/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:54:09 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/07 14:52:54 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		print_usage(char **av)
{
	ft_dprintf(2, "usage: %s [md5 | sha256] [options] [arg1 ...]\n", av[0]);
	ft_dprintf(2, "\n\033[1;37mOPTIONS\033[0;0m\n");
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
		return (-1);
	}
	else if (ac >= 2 && (ft_strcmp("md5", av[1]) && ft_strcmp("sha256", av[1])))
	{
		ft_dprintf(2, "%s:Error: '%s' is an invalid command.\n", av[0], av[1]);
		ft_dprintf(2, "\nStandard commands:\n");
		ft_dprintf(2, "\nMessage Digest commands:\nmd5\nsha256\n");
		ft_dprintf(2, "\nCipher commands:\n");
		return (-1);
	}
	return (0);
}

int			main(int ac, char **av)
{
	int i;

	if (error(ac, av) == -1)
		return (-1);
	if ((i = parse_options(ac, av)) == -1)
		return (-1);
	if (!ft_strcmp("md5", av[1]))
		ft_md5(ac - i, &av[i]);
	else if (!ft_strcmp("sha256", av[1]))
		ft_sha256(ac - i, &av[i]);
	return (0);
}
