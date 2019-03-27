/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 12:00:22 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/27 14:02:20 by fpetras          ###   ########.fr       */
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
# define E 4
# define F 5
# define G 6
# define I 7
# define TMP 4

char		*g_cmd;
int			g_opts[OPT_NUM];
int			g_is_224;
int			g_is_384;
size_t		g_input_len;
uint32_t	g_hash[8];
uint64_t	g_hash64[8];

void		print_usage(char **av);
int			parse_options(int ac, char **av);
int			hash(int ac, char **av);
char		*read_stdin(void);
char		*read_file(char *filename);
char		*join(char const *s1, char const *s2, size_t len1, size_t len2);
void		print(char *input);
void		md5(char *input);
void		md5_algo(char *input);
void		sha224_256(char *input);
void		sha224_256_algo(char *input);
void		sha384_512(char *input);
void		sha384_512_algo(char *input);
void		init_values(uint32_t *vars);
void		init_values64(uint64_t *vars);
void		add_values(uint32_t *vars);
void		add_values64(uint64_t *vars);
uint32_t	leftrotate(uint32_t x, uint32_t n);
uint32_t	rightrotate(uint32_t x, uint32_t n);
uint64_t	rightrotate64(uint64_t x, uint64_t n);
uint32_t	change_endianness(uint32_t value);
uint64_t	change_endianness64(uint64_t value);

#endif
