/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384_512.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:05:43 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/27 15:18:27 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** SHA-384 initial hash values differ from SHA-512
*/

static void	initialize(char *command)
{
	if (!ft_strcasecmp("sha384", command))
	{
		g_is_384 = 1;
		g_hash64[0] = 0xcbbb9d5dc1059ed8;
		g_hash64[1] = 0x629a292a367cd507;
		g_hash64[2] = 0x9159015a3070dd17;
		g_hash64[3] = 0x152fecd8f70e5939;
		g_hash64[4] = 0x67332667ffc00b31;
		g_hash64[5] = 0x8eb44a8768581511;
		g_hash64[6] = 0xdb0c2e0d64f98fa7;
		g_hash64[7] = 0x47b5481dbefa4fa4;
	}
	else if (!ft_strcasecmp("sha512", command))
	{
		g_is_512 = 1;
		g_hash64[0] = 0x6a09e667f3bcc908;
		g_hash64[1] = 0xbb67ae8584caa73b;
		g_hash64[2] = 0x3c6ef372fe94f82b;
		g_hash64[3] = 0xa54ff53a5f1d36f1;
		g_hash64[4] = 0x510e527fade682d1;
		g_hash64[5] = 0x9b05688c2b3e6c1f;
		g_hash64[6] = 0x1f83d9abfb41bd6b;
		g_hash64[7] = 0x5be0cd19137e2179;
	}
	else if (!ft_strcasecmp("sha512224", command))
	{
		g_is_512224 = 1;
		g_hash64[0] = 0x8c3d37c819544da2;
		g_hash64[1] = 0x73e1996689dcd4d6;
		g_hash64[2] = 0x1dfab7ae32ff9c82;
		g_hash64[3] = 0x679dd514582f9fcf;
		g_hash64[4] = 0x0f6d2b697bd44da8;
		g_hash64[5] = 0x77e36f7304c48942;
		g_hash64[6] = 0x3f9d85a86a1d36c8;
		g_hash64[7] = 0x1112e6ad91d692a1;
	}
	else
	{
		g_is_512256 = 1;
		g_hash64[0] = 0x22312194fc2bf72c;
		g_hash64[1] = 0x9f555fa3c84c64c2;
		g_hash64[2] = 0x2393b86b6f53b151;
		g_hash64[3] = 0x963877195940eabd;
		g_hash64[4] = 0x96283ee2a88effe3;
		g_hash64[5] = 0xbe5e1e2553863992;
		g_hash64[6] = 0x2b0199fc2c85b8aa;
		g_hash64[7] = 0x0eb72ddc81c52ca2;
	}
}

/*
** SHA-384 output omits hash value 6 and 7
*/

void		sha384_512(char *input)
{
	uint64_t *hash;

	initialize(g_cmd);
	sha384_512_algo(input);
	hash = g_hash64;
	if (g_is_384)
		ft_printf("%.16llx%.16llx%.16llx%.16llx%.16llx%.16llx",
		hash[0], hash[1], hash[2], hash[3], hash[4], hash[5]);
	else if (g_is_512)
		ft_printf("%.16llx%.16llx%.16llx%.16llx%.16llx%.16llx%.16llx%.16llx",
		hash[0], hash[1], hash[2], hash[3], hash[4], hash[5], hash[6], hash[7]);
	else if (g_is_512224)
		ft_printf("%.16llx%.16llx%.16llx%.8llx",
		hash[0], hash[1], hash[2], hash[3] / 0x100000000);
	else if (g_is_512256)
		ft_printf("%.16llx%.16llx%.16llx%.16llx",
		hash[0], hash[1], hash[2], hash[3]);
}
