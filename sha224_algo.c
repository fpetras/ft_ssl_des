/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 17:19:27 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/26 14:27:40 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint32_t g_k[] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2 };

/*
** Add compressed chunk to the current hash value
*/

static void		add(uint32_t *vars)
{
	g_hash[0] += vars[A];
	g_hash[1] += vars[B];
	g_hash[2] += vars[C];
	g_hash[3] += vars[D];
	g_hash[4] += vars[E];
	g_hash[5] += vars[F];
	g_hash[6] += vars[G];
	g_hash[7] += vars[I];
}

/*
** Initialize variables to the current hash value
*/

static void		init(uint32_t *vars)
{
	vars[A] = g_hash[0];
	vars[B] = g_hash[1];
	vars[C] = g_hash[2];
	vars[D] = g_hash[3];
	vars[E] = g_hash[4];
	vars[F] = g_hash[5];
	vars[G] = g_hash[6];
	vars[I] = g_hash[7];
}

/*
** SHA-2 operations
*/

static void		operations(uint32_t *vars, uint32_t *w, size_t i)
{
	uint32_t ch;
	uint32_t maj;
	uint32_t s[2];
	uint32_t tmp[2];

	ch = (vars[E] & vars[F]) ^ ((~vars[E]) & vars[G]);
	maj = (vars[A] & vars[B]) ^ (vars[A] & vars[C]) ^ (vars[B] & vars[C]);
	s[0] = rightrotate(vars[A], 2) ^ rightrotate(vars[A], 13) ^
	rightrotate(vars[A], 22);
	s[1] = rightrotate(vars[E], 6) ^ rightrotate(vars[E], 11) ^
	rightrotate(vars[E], 25);
	tmp[0] = vars[I] + s[1] + ch + g_k[i] + w[i];
	tmp[1] = s[0] + maj;
	vars[I] = vars[G];
	vars[G] = vars[F];
	vars[F] = vars[E];
	vars[E] = vars[D] + tmp[0];
	vars[D] = vars[C];
	vars[C] = vars[B];
	vars[B] = vars[A];
	vars[A] = tmp[0] + tmp[1];
}

static void		extend(uint32_t *w, size_t i)
{
	uint32_t s0;
	uint32_t s1;

	s0 = rightrotate(w[i - 15], 7) ^ rightrotate(w[i - 15], 18) ^
	(w[i - 15] >> 3);
	s1 = rightrotate(w[i - 2], 17) ^ rightrotate(w[i - 2], 19)
	^ (w[i - 2] >> 10);
	w[i] = w[i - 16] + s0 + w[i - 7] + s1;
}

/*
** Create 64-entry array of 32-bit words
** Copy chunk into first 16 words
** Extend the first 16 words into the remaining 48 words of the array
** Process the message in blocks of 512-bit chunks
*/

static void		process(uint32_t *message, uint32_t vars[8], size_t i)
{
	uint32_t	*w;
	size_t		round;

	w = ft_calloc(64, 32);
	ft_memcpy(w, &message[i * 16], 512);
	round = 16;
	while (round < 64)
	{
		extend(w, round);
		round++;
	}
	init(vars);
	round = 0;
	while (round < 64)
	{
		operations(vars, w, round);
		round++;
	}
	add(vars);
	free(w);
}

/*
** Pre-processing (padding)
*/

static uint32_t	*padding(char *input, size_t input_len, size_t *msg_len)
{
	uint32_t	*message;
	uint32_t	bits_len;
	size_t		i;

	message = NULL;
	bits_len = input_len * CHAR_BIT;
	(*msg_len) = ((bits_len + 16 + 64) / 512) + 1;
	message = ft_calloc((*msg_len) * 16, 32);
	((uint8_t*)message)[input_len] = 0x80;
	ft_memcpy(message, input, input_len);
	i = -1;
	while (++i < ((*msg_len) * 16) - 1)
		message[i] = change_endianness(message[i]);
	message[((((*msg_len) * 512) - 64) / 32) + 1] = bits_len;
	return (message);
}

/*
** SHA-224 initial hash values differ from SHA-256
*/

void			sha224_algo(char *input)
{
	uint32_t	*message;
	size_t		msg_len;
	uint32_t	vars[8];
	size_t		i;

	message = padding(input, g_input_len, &msg_len);
	g_hash[0] = 0xc1059ed8;
	g_hash[1] = 0x367cd507;
	g_hash[2] = 0x3070dd17;
	g_hash[3] = 0xf70e5939;
	g_hash[4] = 0xffc00b31;
	g_hash[5] = 0x68581511;
	g_hash[6] = 0x64f98fa7;
	g_hash[7] = 0xbefa4fa4;
	i = 0;
	while (i < msg_len)
	{
		process(message, vars, i);
		i++;
	}
	free(message);
}
