/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 17:19:27 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/26 12:46:08 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint64_t g_k[] = {
	0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f,
	0xe9b5dba58189dbbc, 0x3956c25bf348b538, 0x59f111f1b605d019,
	0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242,
	0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
	0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
	0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65, 0x2de92c6f592b0275,
	0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
	0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f,
	0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
	0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc,
	0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
	0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6,
	0x92722c851482353b, 0xa2bfe8a14cf10364, 0xa81a664bbc423001,
	0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218,
	0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99,
	0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
	0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc,
	0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915,
	0xc67178f2e372532b, 0xca273eceea26619c, 0xd186b8c721c0c207,
	0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba,
	0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
	0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
	0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
	0x5fcb6fab3ad6faec, 0x6c44198c4a475817 };

static uint64_t	rightrotate(uint64_t x, uint64_t n)
{
	return ((x >> n) | (x << (64 - n)));
}

static uint64_t	change_endianness(uint64_t value)
{
	uint64_t result;

	result = 0;
	result |= (value & 0xFF00000000000000) >> 56;
	result |= (value & 0x00FF000000000000) >> 40;
	result |= (value & 0x0000FF0000000000) >> 24;
	result |= (value & 0x000000FF00000000) >> 8;
	result |= (value & 0x00000000FF000000) << 8;
	result |= (value & 0x0000000000FF0000) << 24;
	result |= (value & 0x000000000000FF00) << 40;
	result |= (value & 0x00000000000000FF) << 56;
	return (result);
}

/*
** Add compressed chunk to the current hash value
*/

static void		add(uint64_t *vars)
{
	g_hash64[0] += vars[A];
	g_hash64[1] += vars[B];
	g_hash64[2] += vars[C];
	g_hash64[3] += vars[D];
	g_hash64[4] += vars[E];
	g_hash64[5] += vars[F];
	g_hash64[6] += vars[G];
	g_hash64[7] += vars[I];
}

/*
** Initialize variables to the current hash value
*/

static void		init(uint64_t *vars)
{
	vars[A] = g_hash64[0];
	vars[B] = g_hash64[1];
	vars[C] = g_hash64[2];
	vars[D] = g_hash64[3];
	vars[E] = g_hash64[4];
	vars[F] = g_hash64[5];
	vars[G] = g_hash64[6];
	vars[I] = g_hash64[7];
}

/*
** SHA-2 operations
*/

static void		operations(uint64_t *vars, uint64_t *w, size_t i)
{
	uint64_t s[2];
	uint64_t ch;
	uint64_t tmp[2];
	uint64_t maj;

	s[1] = rightrotate(vars[E], 14) ^ rightrotate(vars[E], 18) ^
	rightrotate(vars[E], 41);
	ch = (vars[E] & vars[F]) ^ ((~vars[E]) & vars[G]);
	tmp[0] = vars[I] + s[1] + ch + g_k[i] + w[i];
	s[0] = rightrotate(vars[A], 28) ^ rightrotate(vars[A], 34) ^
	rightrotate(vars[A], 39);
	maj = (vars[A] & vars[B]) ^ (vars[A] & vars[C]) ^ (vars[B] & vars[C]);
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

static void		extend(uint64_t *w, size_t i)
{
	uint64_t s0;
	uint64_t s1;

	s0 = rightrotate(w[i - 15], 1) ^ rightrotate(w[i - 15], 8) ^
	(w[i - 15] >> 7);
	s1 = rightrotate(w[i - 2], 19) ^ rightrotate(w[i - 2], 61)
	^ (w[i - 2] >> 6);
	w[i] = w[i - 16] + s0 + w[i - 7] + s1;
}

/*
** Create 80-entry array of 64-bit words
** Copy chunk into first 16 words
** Extend the first 16 words into the remaining 80 words of the array
** Process the message in blocks of 1024-bit chunks
*/

static void		process(uint64_t *message, uint64_t vars[8], size_t i)
{
	uint64_t	*w;
	size_t		round;

	w = ft_calloc(80, 64);
	ft_memcpy(w, &message[i * 16], 1024);
	round = 16;
	while (round < 80)
	{
		extend(w, round);
		round++;
	}
	init(vars);
	round = 0;
	while (round < 80)
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

static uint64_t	*padding(char *input, size_t input_len, size_t *msg_len)
{
	uint64_t	*message;
	uint64_t	bits_len;
	size_t		i;

	message = NULL;
	bits_len = input_len * CHAR_BIT;
	(*msg_len) = ((bits_len + 128) / 1024) + 1;
	message = ft_calloc((*msg_len) * 16, 64);
	((uint8_t*)message)[input_len] = 0x80;
	ft_memcpy(message, input, input_len);
//	for (size_t j = 0; j < input_len; j++)
//		ft_printf("%02llx", message[j]);
//	ft_printf("\n");
	i = -1;
	while (++i < input_len + 1)
		message[i] = change_endianness(message[i]);
	message[((((*msg_len) * 1024) - 128) / 64) + 1] = bits_len;
//	for (size_t j = 0; j < input_len; j++)
//		ft_printf("%02llx", message[j]);
//	ft_printf("\n");
	return (message);
}

void			sha512_algo(char *input)
{
	uint64_t	*message;
	size_t		msg_len;
	uint64_t	vars[8];
	size_t		i;

//	for (size_t j = 0; j < g_input_len; j++)
//		ft_printf("%02x", (unsigned int)input[j]);
//	ft_printf("\n");

	message = padding(input, g_input_len, &msg_len);
	g_hash64[0] = 0x6a09e667f3bcc908;
	g_hash64[1] = 0xbb67ae8584caa73b;
	g_hash64[2] = 0x3c6ef372fe94f82b;
	g_hash64[3] = 0xa54ff53a5f1d36f1;
	g_hash64[4] = 0x510e527fade682d1;
	g_hash64[5] = 0x9b05688c2b3e6c1f;
	g_hash64[6] = 0x1f83d9abfb41bd6b;
	g_hash64[7] = 0x5be0cd19137e2179;
	i = 0;
	while (i < msg_len)
	{
		process(message, vars, i);
		i++;
	}
	free(message);
}
