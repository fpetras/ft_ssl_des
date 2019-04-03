/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_cipher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 13:39:06 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/02 17:12:16 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

# define BRK 2
# define SKIP 3

static int	check_argument(char **av, int i, int j, char opt)
{
	if (opt == 'i' && g_input_file == NULL)
		return (argument_missing(opt, av));
	else if (opt == 'o' && g_output_file == NULL)
		return (argument_missing(opt, av));
	else if (opt == 'k' && g_key == NULL)
		return (argument_missing(opt, av));
	else if (opt == 'p' && g_passwd == NULL)
		return (argument_missing(opt, av));
	else if (opt == 's' && g_salt == NULL)
		return (argument_missing(opt, av));
	else if (opt == 'v' && g_vector == NULL)
		return (argument_missing(opt, av));
	else if (!av[i][j + 1])
		return (SKIP);
	else
		return (BRK);
}

static void	set_option(char opt)
{
	g_opts[OPT_D] = (opt == 'd') ? 1 : g_opts[OPT_D];
	g_opts[OPT_E] = (opt == 'e') ? 1 : g_opts[OPT_E];
	g_opts[OPT_I] = (opt == 'i') ? 1 : g_opts[OPT_I];
	g_opts[OPT_O] = (opt == 'o') ? 1 : g_opts[OPT_O];
	g_opts[OPT_A] = (opt == 'a') ? 1 : g_opts[OPT_A];
	g_opts[OPT_K] = (opt == 'k') ? 1 : g_opts[OPT_K];
	g_opts[OPT_P] = (opt == 'p') ? 1 : g_opts[OPT_P];
	g_opts[OPT_S] = (opt == 's') ? 1 : g_opts[OPT_S];
	g_opts[OPT_V] = (opt == 'v') ? 1 : g_opts[OPT_V];
}

static int	parse_cipher_options_3(char **av, int i, int j)
{
	if (av[i][j] == 'k')
	{
		g_key = av[i][j + 1] ? &av[i][j + 1] : NULL;
		g_key = !g_key && av[i + 1] ? av[i + 1] : g_key;
		return (check_argument(av, i, j, av[i][j]));
	}
	if (av[i][j] == 'p')
	{
		g_passwd = av[i][j + 1] ? &av[i][j + 1] : NULL;
		g_passwd = !g_passwd && av[i + 1] ? av[i + 1] : g_passwd;
		return (check_argument(av, i, j, av[i][j]));
	}
	if (av[i][j] == 's')
	{
		g_salt = av[i][j + 1] ? &av[i][j + 1] : NULL;
		g_salt = !g_salt && av[i + 1] ? av[i + 1] : g_salt;
		return (check_argument(av, i, j, av[i][j]));
	}
	if (av[i][j] == 'v')
	{
		g_vector = av[i][j + 1] ? &av[i][j + 1] : NULL;
		g_vector = !g_vector && av[i + 1] ? av[i + 1] : g_vector;
		return (check_argument(av, i, j, av[i][j]));
	}
	return (0);
}

static int	parse_cipher_options_2(char **av, int i, int j)
{
	if (ft_strchr(g_is_base64 ? BASE64_OPT_STR : DES_OPT_STR, av[i][j]))
		set_option(av[i][j]);
	else
		return (illegal_option(av[i][j], av));
	if (av[i][j] == 'i')
	{
		g_input_file = av[i][j + 1] ? &av[i][j + 1] : NULL;
		g_input_file = !g_input_file && av[i + 1] ? av[i + 1] : g_input_file;
		return (check_argument(av, i, j, av[i][j]));//to support -i"file" syntax
	}
	if (av[i][j] == 'o')
	{
		g_output_file = av[i][j + 1] ? &av[i][j + 1] : NULL;
		g_output_file = !g_output_file && av[i + 1] ? av[i + 1] : g_output_file;
		return (check_argument(av, i, j, av[i][j]));//to support -o"file" syntax
	}
	if (g_is_ecb || g_is_cbc)
		return (parse_cipher_options_3(av, i, j));
	return (0);
}

/*
** Supports:
** -- to signify end of options
** concatenation, i.e. -ad
** -i file syntax
** -o"file" syntax
** Both, i.e. -adk"Key"
** Example usage: ./ft_ssl des -ao file -k"Key" -s Salt -- -
*/

int			parse_cipher_options(int ac, char **av)
{
	int i;
	int j;
	int ret;
	int opt_end;

	i = 2;
	opt_end = 0;
	while (i < ac)
	{
		j = 1;
		ret = 0;
		if (av[i] && (opt_end || av[i][0] != '-'))
			g_input_file = av[i];
		while (av[i][j] && av[i][0] == '-' && !opt_end)
		{
			if ((opt_end = !ft_strcmp("--", av[i])))
				break ;
			if ((ret = parse_cipher_options_2(av, i, j)) == BRK || ret == SKIP)
				break ;              // break if -i"file" syntax is used
			if (ret == EXIT_FAILURE)
				return (ret);
			j++;
		}
		(ret == SKIP) ? i += 2 : i++;
	}
	return (EXIT_SUCCESS);
}
