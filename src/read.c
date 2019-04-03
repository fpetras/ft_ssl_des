/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 10:15:45 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/27 17:29:17 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char	*file_error(char *filename, int fd)
{
	ft_dprintf(2, "ft_ssl: %s: %s: %s\n", g_cmd, filename, strerror(errno));
	close(fd);
	return (NULL);
}

static int	malloc_error(char *to_free)
{
	if (to_free)
		free(to_free);
	ft_dprintf(2, "Memory allocation failure\n");
	return (EXIT_FAILURE);
}

char		*read_file(char *filename)
{
	int		fd;
	int		ret;
	char	buf[BUFF_SIZE];
	char	*file[2];

	g_input_len = 0;
	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		ft_dprintf(2, "ft_ssl: %s: %s: %s\n", g_cmd, filename, strerror(errno));
		return (NULL);
	}
	if ((file[0] = ft_strnew(0)) == NULL)
		exit(malloc_error(NULL));
	while ((ret = read(fd, &buf, BUFF_SIZE)) > 0)
	{
		file[1] = file[0];
		if ((file[0] = join(file[1], buf, g_input_len, ret)) == NULL)
			exit(malloc_error(g_input_len ? file[1] : NULL));
		g_input_len += ret;
		free(file[1]);
	}
	if (ret == -1)
		return (file_error(filename, fd));
	close(fd);
	return (file[0]);
}

char		*read_stdin(void)
{
	int		ret;
	char	buf[BUFF_SIZE];
	char	*input[2];

	g_input_len = 0;
	if ((input[0] = ft_strnew(0)) == NULL)
		exit(malloc_error(NULL));
	while ((ret = read(STDIN_FILENO, &buf, BUFF_SIZE)) > 0)
	{
		input[1] = input[0];
		if ((input[0] = join(input[1], buf, g_input_len, ret)) == NULL)
			exit(malloc_error(g_input_len ? input[1] : NULL));
		g_input_len += ret;
		free(input[1]);
	}
	return (input[0]);
}
