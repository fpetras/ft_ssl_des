/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:38:48 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/15 16:39:55 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	md5_formatted_hash(char *filename, char *input)
{
	if (!g_opts[OPT_Q])
	{
		if (!g_opts[OPT_R])
		{
			if (filename)
				ft_printf("MD5 (%s) = ", filename);
			else
				ft_printf("MD5 (\"%s\") = ", input);
		}
	}
	md5_hash(input);
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

static int	md5_file(char *filename)
{
	char *input;

	if ((input = read_file(filename)) != NULL)
	{
		md5_formatted_hash(filename, input);
		free(input);
		return (0);
	}
	else
		return (-1);
}

static int	md5_stdin(void)
{
	char *input;

	if ((input = read_stdin()) == NULL)
		return (-1);
	g_opts[OPT_P] ? ft_printf("%s", input) : 0;
	md5_hash(input);
	ft_printf("\n");
	free(input);
	return (0);
}

int			ft_md5(int ac, char **av)
{
	int	i;
	int ret;

	i = 0;
	ret = 0;
	if (ac == 0 || g_opts[OPT_P])
		if (md5_stdin() == -1)
			return (-1);
	if (g_opts[OPT_S])
	{
		md5_formatted_hash(NULL, av[i]);
		i++;
	}
	while (i < ac)
	{
		if (md5_file(av[i]) == -1)
			ret = -1;
		i++;
	}
	return (ret);
}
