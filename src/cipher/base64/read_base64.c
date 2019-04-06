/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_base64.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 11:16:09 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/06 15:59:14 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	file_error(char *filename, int fd)
{
	ft_dprintf(2, "ft_ssl: %s: %s: %s\n", g_cmd, filename, strerror(errno));
	close(fd);
	return (EXIT_FAILURE);
}

static int	malloc_error(char *to_free)
{
	to_free ? free(to_free) : 0;
	ft_dprintf(2, "Memory allocation failure\n");
	return (EXIT_FAILURE);
}

static int	finish_base64(int ifd, int ofd, int ret, char *input)
{
	if (ret == -1)
		return (file_error(g_input_file, ifd));
	ret = (ret == -2) ? EXIT_FAILURE : EXIT_SUCCESS;
	if (g_input_len != BUFF_SIZE)
		ret = !g_opts[OPT_D] ?
		base64_encode(ofd, input) : base64_decode(ofd, input);
	input ? free(input) : 0;
	!g_opts[OPT_D] ? ft_dprintf(ofd, "\n") : 0;
	ifd != STDIN_FILENO ? close(ifd) : 0;
	ofd != STDOUT_FILENO ? close(ofd) : 0;
	return (ret);
}


static char	*join_input(int ret, char *buf, char *input)
{
	char *tmp;

	tmp = input;
	g_input_len = g_input_len == BUFF_SIZE ? 0 : g_input_len;
	if ((input = join(input, buf, g_input_len, ret)) == NULL)
		exit(malloc_error(g_input_len > 0 && g_input_len < BUFF_SIZE ?
		tmp : NULL));
	g_input_len += ret;
	free(tmp);
	return (input);
}

static int	output_file_descriptor(char *output_file)
{
	int fd;

	if (!output_file || !ft_strcmp("-", output_file))
		return (STDOUT_FILENO);
	fd = open(output_file, O_RDWR | O_CREAT | O_TRUNC,
	S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (fd == -1)
	{
		ft_dprintf(2, "ft_ssl: %s: %s: %s\n",
		g_cmd, output_file, strerror(errno));
		return (-1);
	}
	return (fd);
}

static int	input_file_descriptor(char *input_file)
{
	int fd;

	if (!input_file || !ft_strcmp("-", input_file))
		return (STDIN_FILENO);
	if ((fd = open(input_file, O_RDONLY)) == -1)
	{
		ft_dprintf(2, "ft_ssl: %s: %s: %s\n",
		g_cmd, input_file, strerror(errno));
		return (-1);
	}
	return (fd);
}

/*
** BUFF_SIZE needs to be a multiple of three
** (otherwise, we get padding after every read() iteration)
*/


int			read_base64(void)
{
	int		ifd;
	int		ofd;
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*input;

	if ((ifd = input_file_descriptor(g_input_file)) == -1)
		return (EXIT_FAILURE);
	if ((ofd = output_file_descriptor(g_output_file)) == -1)
		return (EXIT_FAILURE);
	if ((input = ft_strnew(0)) == NULL)
		exit(malloc_error(NULL));
	g_input_len = 0;
	while ((ret = read(ifd, &buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (ret < BUFF_SIZE)
			input = join_input(ret, buf, input);
		else
		{
			g_input_len = ret;
			if ((!g_opts[OPT_D]) ?
			base64_encode(ofd, buf) : base64_decode(ofd, buf) == EXIT_FAILURE)
				return (finish_base64(ifd, ofd, -2, input));
		}
	}
	return (finish_base64(ifd, ofd, ret, input));
}
