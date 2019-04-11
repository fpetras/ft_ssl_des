/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 12:04:59 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/11 17:53:36 by fpetras          ###   ########.fr       */
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
	ft_dprintf(2, "     base64 base64url\n");
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

int		print_base64_usage(char **av)
{
	ft_dprintf(2, "usage: %s %s [-d | -e] [-i <file>] [-o <file>]\n",
	av[0], av[1]);
	ft_dprintf(2, "\n%sOPTIONS%s\n", WHITE, TEXT_RESET);
	ft_dprintf(2, "     -d            decode mode\n");
	ft_dprintf(2, "     -e            encode mode (default)\n");
	ft_dprintf(2, "     -i <file>     input file\n");
	ft_dprintf(2, "     -o <file>     output file\n");
	ft_dprintf(2, "     -n            print a newline every 64 characters\n");
	return (EXIT_FAILURE);
}

int		print_des_usage(char **av)
{
	ft_dprintf(2, "usage: %s %s [-a] [-d | -e] [-i <file>] [-o <file>]\n",
	av[0], av[1]);
	ft_dprintf(2, "%7c[[-k <key>] | [-p <password>] [-s <salt>]]", ' ');
	ft_dprintf(2, "%s", g_is_cbc ? " [-v <vector]\n" : "\n");
	ft_dprintf(2, "\n%sOPTIONS%s\n", WHITE, TEXT_RESET);
	ft_dprintf(2, "     -a%12cdecode/encode the input/output in Base64\n", ' ');
	ft_dprintf(2, "     -d            decrypt mode\n");
	ft_dprintf(2, "     -e            encrypt mode\n");
	ft_dprintf(2, "     -i <file>     input file\n");
	ft_dprintf(2, "     -o <file>     output file\n");
	ft_dprintf(2, "     -p <password> password (in ASCII)\n");
	ft_dprintf(2, "     -s <salt>     salt (in hexadecimal)\n");
	ft_dprintf(2, "     -v <vector>%3cinitialization vector (in hexadecimal)\n",
	' ');
	return (EXIT_FAILURE);
}
