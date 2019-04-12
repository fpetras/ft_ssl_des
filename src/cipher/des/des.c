/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 11:33:21 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/12 13:10:04 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		zero_padding(char *dst, char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dst[i] = ft_toupper(src[i]);
		i++;
	}
	while (i < 16)
	{
		dst[i] = '0';
		i++;
	}
	dst[i] = '\0';
	return (EXIT_SUCCESS);
}

int		des(void)
{
	int fd;

	if (invalid_arguments() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!g_input_file || !ft_strcmp(g_input_file, "-"))
		fd = STDIN_FILENO;
	else if ((fd = open(g_input_file, O_RDONLY)) == -1)
	{
			ft_dprintf(2, "ft_ssl: %s: %s: %s\n",
			g_cmd, g_input_file, strerror(errno));
			return (EXIT_FAILURE);
	}
	if (!g_k_ && !g_passwd && get_password() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	set_salt();
	get_key();
	ft_printf("salt=%s\n", g_salt);
	ft_printf("key=%s\n", g_key);
//	if (g_is_cbc && !g_vector)
//		get_iv();
//	read_input();
	return (EXIT_SUCCESS);
}
