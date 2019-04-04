/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 08:19:40 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/10 17:53:55 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../libft.h"
# include <sys/types.h>
# include <sys/uio.h>

# define BUFF_SIZE	4242
# define MAX_FD		4865

int		get_next_line(const int fd, char **line);

#endif
