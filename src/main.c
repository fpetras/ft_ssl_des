/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:54:09 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/04 11:12:38 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	error_message(char **av)
{
	ft_dprintf(2, "ft_ssl: Error: '%s' is an invalid command.\n", av[1]);
	ft_dprintf(2, "\n%sStandard commands%s\n", WHITE, TEXT_RESET);
	ft_dprintf(2, "\n%sMessage Digest commands%s\n", WHITE, TEXT_RESET);
	ft_dprintf(2, "md5\nsha224\nsha256\nsha384\nsha512\n");
	ft_dprintf(2, "sha512224\nsha512256\n");
	ft_dprintf(2, "\n%sCipher commands%s\n", WHITE, TEXT_RESET);
	ft_dprintf(2, "base64\ndes\ndes-ecb\ndes-cbc\n");
	return (EXIT_FAILURE);
}

static int	error(int ac, char **av)
{
	if (ac == 1)
		return (print_usage(av));
	else if (command_is_hash(av))
		g_is_hash = 1;
	else if (command_is_cipher(av))
		g_is_cipher = 1;
	else
		return (error_message(av));
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
	if (g_is_hash)
		return (hash(ac - i, &av[i]));
	else if (g_is_cipher)
		return (cipher());
	return (EXIT_SUCCESS);
}
