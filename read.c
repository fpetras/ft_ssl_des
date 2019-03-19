/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 10:15:45 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/19 17:39:31 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char	*file_error(char *filename, int fd)
{
	ft_dprintf(2, "md5: %s: %s\n", filename, strerror(errno));
	close(fd);
	return (NULL);
}

char		*read_file(char *filename)
{
	int		fd;
	int		ret;
	char	buf[BUFF_SIZE];
	char	*file;
	char	*file1;

	g_input_len = 0;
	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		ft_dprintf(2, "ft_ssl: md5: %s: %s\n", filename, strerror(errno));
		return (NULL);
	}
	if ((file = ft_strnew(0)) == NULL)
		return (NULL);
	while ((ret = read(fd, &buf, BUFF_SIZE)) > 0)
	{
		file1 = file;
		file = ft_join(file1, buf, g_input_len, ret);
		g_input_len += ret;
		free(file1);
	}
	if (ret == -1)
		return (file_error(filename, fd));
	close(fd);
	return (file);
}

char		*read_stdin(void)
{
	int		ret;
	char	buf[BUFF_SIZE];
	char	*input;
	char	*input1;

	g_input_len = 0;
	if ((input = ft_strnew(0)) == NULL)
		return (NULL);
	while ((ret = read(STDIN_FILENO, &buf, BUFF_SIZE)) > 0)
	{
		input1 = input;
		input = ft_join(input1, buf, g_input_len, ret);
		g_input_len += ret;
		free(input1);
	}
	return (input);
}
