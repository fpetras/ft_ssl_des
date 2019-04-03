/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 12:04:59 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/01 17:34:51 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		print_usage(char **av)
{
	ft_dprintf(2, "usage: %s <command> [<options>] [<arg>...]\n", av[0]);
	ft_dprintf(2, "\n%sMESSAGE DIGEST COMMANDS%s\n", WHITE, TEXT_RESET);
	ft_dprintf(2, "     md5\n");
	ft_dprintf(2, "     sha224 sha256 sha384 sha512 sha512224 sha512256\n");
	ft_dprintf(2, "\n%sCIPHER COMMANDS%s\n", WHITE, TEXT_RESET);
	ft_dprintf(2, "     base64\n");
	ft_dprintf(2, "     des des-ecb des-cbc\n");
	return (EXIT_FAILURE);
}

int		print_hash_usage(char **av)
{
	ft_dprintf(2, "usage: %s %s [-pqr] [-s <string>] [<file>...]\n",
	av[0], av[1]);
	ft_dprintf(2, "\n%sOPTIONS%s\n", WHITE, TEXT_RESET);
	ft_dprintf(2, "     -p            echo stdin to stdout and append ");
	ft_dprintf(2, "checksum to stdout\n");
	ft_dprintf(2, "     -q            quiet mode\n");
	ft_dprintf(2, "     -r            reverse the format of the output\n");
	ft_dprintf(2, "     -s <string>   print the sum of the given string\n");
	return (EXIT_FAILURE);
}
