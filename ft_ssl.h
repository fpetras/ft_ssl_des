/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 12:00:22 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/19 16:53:56 by fpetras          ###   ########.fr       */
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
# include <stdint.h>
# include <errno.h>
# include <limits.h>

# define OPT_STR "pqrs"
# define OPT_NUM 4
# define OPT_P 0
# define OPT_Q 1
# define OPT_R 2
# define OPT_S 3

# define A 0
# define B 1
# define C 2
# define D 3
# define F 4
# define G 5
# define E 6

int			g_opts[OPT_NUM];
int			g_len;
uint32_t	g_hash[4];

void	print_usage(char **av);
int		parse_options(int ac, char **av);
int		ft_md5(int ac, char **av);
int		ft_sha256(int ac, char **av);
char	*read_stdin(void);
char	*read_file(char *filename);
char	*ft_join(char const *s1, char const *s2, size_t len1, size_t len2);
void	print(char *input);
int		md5_hash(char *input);
void	md5_algo(uint8_t *input, size_t len);
int		sha256_hash(char *input);

#endif
