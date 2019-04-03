/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 12:00:22 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/03 14:04:40 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <stdint.h>
# include <errno.h>
# include <limits.h>

# include "libft.h"
# include "message_digest.h"
# include "cipher.h"

# define WHITE "\033[37;1m"
# define TEXT_RESET "\033[0;0m"

char	*g_cmd;
int		g_opts[OPT_NUM];
size_t	g_input_len;

int		print_usage(char **av);
int		parse_options(int ac, char **av);
int		illegal_option(char opt, char **av);
int		argument_missing(char opt, char **av);

char	*read_stdin(void);
char	*read_file(char *filename);
char	*join(char const *s1, char const *s2, size_t len1, size_t len2);
void	print(char *input);

#endif
