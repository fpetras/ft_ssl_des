/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:30 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/08 15:08:36 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void		sha256_formatted_hash(char *filename, char *input)
{
	if (!g_opts[OPT_Q])
	{
		if (!g_opts[OPT_R])
		{
			if (filename)
				ft_printf("SHA256 (%s) = ", filename);
			else
				ft_printf("SHA256 (\"%s\") = ", input);
		}
	}
	sha256_hash(input);
	if (!g_opts[OPT_Q] && g_opts[OPT_R])
	{
		if (filename)
			ft_printf(" %s\n", filename);
		else
			ft_printf(" \"%s\"\n", input);
	}
	else
		ft_printf("\n");
}

/*
static void		print_opts_and_args(int ac, char **av)
{
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
}
*/

int				ft_sha256(int ac, char **av)
{
	int		i;
	char	*input;

	i = 0;
	if (ac == 0 || g_opts[OPT_P])
	{
		if ((input = read_stdin()) == NULL)
			return (-1);
		g_opts[OPT_P] ? ft_printf("%s", input) : 0;
		sha256_hash(input);
		ft_printf("\n");
		free(input);
	}
//	print_opts_and_args(ac, av);
	if (g_opts[OPT_S])
	{
		sha256_formatted_hash(NULL, av[i]);
		i++;
	}
	while (i < ac)
	{
		if ((input = read_file(av[i])) != NULL)
		{
			sha256_formatted_hash(av[i], input);
			free(input);
		}
		i++;
	}
	return (0);
}
