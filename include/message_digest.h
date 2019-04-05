/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_digest.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:25:54 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/05 09:02:57 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_DIGEST_H
# define MESSAGE_DIGEST_H

# define HASH_OPT_STR "pqrs"

enum	e_vars
{
	A, B, C, D, E, F, G, I, TMP = 4
};

int			g_is_hash;
int			g_is_cipher;
int			g_md;
int			g_sha;
uint32_t	g_hash[8];
uint64_t	g_hash64[8];

int			command_is_hash(char **av);
int			parse_hash_options(int ac, char **av);
int			print_hash_usage(char **av);

int			hash(int ac, char **av);

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
