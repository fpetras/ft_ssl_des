/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:30 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/19 17:39:44 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	sha256_formatted_hash(char *filename, char *input)
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

static int	sha256_file(char *filename)
{
	char *input;

	if ((input = read_file(filename)) != NULL)
	{
		sha256_formatted_hash(filename, input);
		free(input);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}

static int	sha256_stdin(void)
{
	char *input;

	if ((input = read_stdin()) == NULL)
		return (EXIT_FAILURE);
	g_opts[OPT_P] ? print(input) : 0;
	sha256_hash(input);
	ft_printf("\n");
	free(input);
	return (EXIT_SUCCESS);
}

int			ft_sha256(int ac, char **av)
{
	int	i;
	int ret;

	i = 0;
	ret = EXIT_SUCCESS;
	if (ac == 0 || g_opts[OPT_P])
		if (sha256_stdin() == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (g_opts[OPT_S])
	{
		g_input_len = ft_strlen(av[i]);
		sha256_formatted_hash(NULL, av[i]);
		i++;
	}
	while (i < ac)
	{
		if (sha256_file(av[i]) == EXIT_FAILURE)
			ret = EXIT_FAILURE;
		i++;
	}
	return (ret);
}
