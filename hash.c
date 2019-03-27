/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:38:48 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/27 16:51:21 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	hash_formatted(char *filename, char *input)
{
	if (!g_opts[OPT_Q])
	{
		if (!g_opts[OPT_R])
		{
			if (filename)
				ft_printf("%s (%s) = ", ft_strupr(g_cmd), filename);
			else
				ft_printf("%s (\"%s\") = ", ft_strupr(g_cmd), input);
			ft_strlwr(g_cmd);
		}
	}
	g_is_md5 ? md5(input) : 0;
	g_is_224 || g_is_256 ? sha224_256(input) : 0;
	g_is_384 || g_is_512 || g_is_512224 || g_is_512256 ? sha384_512(input) : 0;
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

static int	hash_file(char *filename)
{
	char *input;

	if ((input = read_file(filename)) != NULL)
	{
		hash_formatted(filename, input);
		free(input);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}

static int	hash_stdin(void)
{
	char *input;

	if ((input = read_stdin()) == NULL)
		return (EXIT_FAILURE);
	g_opts[OPT_P] ? print(input) : 0;
	g_is_md5 ? md5(input) : 0;
	g_is_224 || g_is_256 ? sha224_256(input) : 0;
	g_is_384 || g_is_512 || g_is_512224 || g_is_512256 ? sha384_512(input) : 0;
	ft_printf("\n");
	free(input);
	return (EXIT_SUCCESS);
}

static void	which_sha_function(int sha)
{
	if (sha == 224)
		g_is_224 = 1;
	else if (sha == 256)
		g_is_256 = 1;
	else if (sha == 384)
		g_is_384 = 1;
	else if (sha == 512)
		g_is_512 = 1;
	else if (sha == 512224)
		g_is_512224 = 1;
	else if (sha == 512256)
		g_is_512256 = 1;
}

int			hash(int ac, char **av)
{
	int	i;
	int ret;

	i = 0;
	ret = EXIT_SUCCESS;
	if (!ft_strncasecmp("sha", g_cmd, 3))
		which_sha_function(ft_atoi(&g_cmd[3]));
	else
		g_is_md5 = 1;
	if (ac == 0 || g_opts[OPT_P])
		if (hash_stdin() == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (g_opts[OPT_S])
	{
		g_input_len = ft_strlen(av[i]);
		hash_formatted(NULL, av[i]);
		i++;
	}
	while (i < ac)
	{
		if (hash_file(av[i]) == EXIT_FAILURE)
			ret = EXIT_FAILURE;
		i++;
	}
	return (ret);
}
