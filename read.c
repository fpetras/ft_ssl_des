/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 10:15:45 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/08 13:54:42 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*read_file(char *filename)
{
	int		fd;
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*file;
	char	*file1;

	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		ft_dprintf(2, "md5: %s: %s\n", filename, strerror(errno));
		return (NULL);
	}
	if ((file = ft_strnew(0)) == NULL)
		return (NULL);
	while ((ret = read(fd, &buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		file1 = file;
		file = ft_strjoin(file1, buf);
		free(file1);
	}
	if (ret == -1)
	{
		ft_dprintf(2, "md5: %s: %s\n", filename, strerror(errno));
		close(fd);
		return (NULL);
	}
	close(fd);
	return (file);
}

char	*read_stdin(void)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*input;
	char	*input1;

	if ((input = ft_strnew(0)) == NULL)
		return (NULL);
	while ((ret = read(STDIN_FILENO, &buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		input1 = input;
		input = ft_strjoin(input1, buf);
		free(input1);
	}
	return (input);
}
