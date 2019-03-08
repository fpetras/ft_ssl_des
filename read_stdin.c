/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 10:15:45 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/08 10:16:17 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*read_stdin(void)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*file1;
	char	*file2;

	file1 = ft_strnew(0);
	while ((ret = read(STDIN_FILENO, &buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		file2 = file1;
		file1 = ft_strjoin(file2, buf);
		free(file2);
	}
	return (file1);
}
