/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:38:48 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/07 16:58:03 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char	*read_stdin(void)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*file1;
	char	*file2;

	file1 = ft_strnew(0);
	while ((ret = read(0, &buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		file2 = file1;
		file1 = ft_strjoin(file2, buf);
		free(file2);
	}
	return (file1);
}

int			ft_md5(int ac, char **av)
{
//	int i;
//
//	i = 0;
//	ft_printf("%d\n", ac);
//	while (i < ac)
//	{
//		ft_printf("%s\n", av[i]);
//		i++;
//	}
	char *input;

	(void)av;
	if (ac == 0 || g_opts[OPT_P])
	{
		input = read_stdin();
		g_opts[OPT_P] ? ft_printf("%s\n", input) : 0;
		free(input);
	}
	return (0);
}
