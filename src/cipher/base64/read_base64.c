/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_base64.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 11:16:09 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/08 23:13:23 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	finish_base64(int i_fd, int o_fd, int ret, char *input)
{
	if (ret == -1)
	{
		ft_dprintf(2, "ft_ssl: %s: %s: %s\n",
		g_cmd, g_input_file, strerror(errno));
		i_fd != STDIN_FILENO ? close(i_fd) : 0;
		o_fd != STDOUT_FILENO ? close(o_fd) : 0;
		return (EXIT_FAILURE);
	}
	ret = (ret == -2) ? EXIT_FAILURE : EXIT_SUCCESS;
	if (g_input_len != BUFF_SIZE)
		ret = !g_opts[OPT_D] ?
		base64_encode(o_fd, input) : base64_decode(o_fd, input);
	input ? free(input) : 0;
	!g_opts[OPT_D] ? ft_dprintf(o_fd, "\n") : 0;
	i_fd != STDIN_FILENO ? close(i_fd) : 0;
	o_fd != STDOUT_FILENO ? close(o_fd) : 0;
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
	int		fd[2];
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*input;

	if ((fd[0] = input_file_descriptor(g_input_file)) == -1)
		return (EXIT_FAILURE);
	if ((fd[1] = output_file_descriptor(g_output_file)) == -1)
		return (EXIT_FAILURE);
	if ((input = ft_strnew(0)) == NULL)
		exit(malloc_error(NULL));
	while ((ret = read(fd[0], &buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (ret < BUFF_SIZE)
			input = join_input(ret, buf, input);
		else
		{
			g_input_len = ret;
			if ((!g_opts[OPT_D]) ? base64_encode(fd[1], buf) :
				base64_decode(fd[1], buf) == EXIT_FAILURE)
				return (finish_base64(fd[0], fd[1], -2, input));
		}
	}
	return (finish_base64(fd[0], fd[1], ret, input));
}
