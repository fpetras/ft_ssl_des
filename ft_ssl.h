/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 12:00:22 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/08 13:45:26 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft/libft.h"
# include "libft/get_next_line/get_next_line.h"
# include "libft/ft_printf/ft_printf.h"

# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <errno.h>

# define OPT_STR "pqrs"
# define OPT_NUM 4
# define OPT_P 0
# define OPT_Q 1
# define OPT_R 2
# define OPT_S 3

int		g_opts[OPT_NUM];

void	print_usage(char **av);
int		parse_options(int ac, char **av);
int		ft_md5(int ac, char **av);
int		ft_sha256(int ac, char **av);
char	*read_stdin(void);
char	*read_file(char *filename);

#endif
