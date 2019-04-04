/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_base64.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 11:16:09 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/04 15:13:15 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		file_error(char *filename, int fd)
{
	ft_dprintf(2, "ft_ssl: %s: %s: %s\n", g_cmd, filename, strerror(errno));
	close(fd);
	return (EXIT_FAILURE);
}

int		read_base64(void)
{
	int		fd;
	int		ret;
	char	buf[4242];

	if (!g_input_file || !ft_strcmp("-", g_input_file))
		fd = STDIN_FILENO;
	else
		if ((fd = open(g_input_file, O_RDONLY)) == -1)
		{
			ft_dprintf(2, "ft_ssl: %s: %s: %s\n",
			g_cmd, g_input_file, strerror(errno));
			return (EXIT_FAILURE);
		}
	while ((ret = read(fd, &buf, 4242)) > 0)
	{
		g_input_len = ret;
		if (!g_opts[OPT_D])
			base64_encode(buf);
//		else
//			base64_decode();
	}
	if (ret == -1)
		return (file_error(g_input_file, fd));
	ft_printf("\n");
	return (EXIT_SUCCESS);
}
