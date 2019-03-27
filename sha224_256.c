/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_256.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:05:43 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/27 13:57:37 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** SHA-224 initial hash values differ from SHA-256
*/

static void	initialize(char *command)
{
	if (!ft_strcmp("sha224", command))
	{
		g_is_224 = 1;
		g_hash[0] = 0xc1059ed8;
		g_hash[1] = 0x367cd507;
		g_hash[2] = 0x3070dd17;
		g_hash[3] = 0xf70e5939;
		g_hash[4] = 0xffc00b31;
		g_hash[5] = 0x68581511;
		g_hash[6] = 0x64f98fa7;
		g_hash[7] = 0xbefa4fa4;
	}
	else
	{
		g_is_224 = 0;
		g_hash[0] = 0x6a09e667;
		g_hash[1] = 0xbb67ae85;
		g_hash[2] = 0x3c6ef372;
		g_hash[3] = 0xa54ff53a;
		g_hash[4] = 0x510e527f;
		g_hash[5] = 0x9b05688c;
		g_hash[6] = 0x1f83d9ab;
		g_hash[7] = 0x5be0cd19;
	}
}

/*
** SHA-224 output omits hash value 7
*/

void		sha224_256(char *input)
{
	uint32_t *hash;

	initialize(g_cmd);
	sha224_256_algo(input);
	hash = g_hash;
	if (g_is_224)
		ft_printf("%.8x%.8x%.8x%.8x%.8x%.8x%.8x",
		hash[0], hash[1], hash[2], hash[3], hash[4], hash[5], hash[6]);
	else
		ft_printf("%.8x%.8x%.8x%.8x%.8x%.8x%.8x%.8x",
		hash[0], hash[1], hash[2], hash[3], hash[4], hash[5], hash[6], hash[7]);
}
