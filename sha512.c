/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:05:43 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/25 17:34:41 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	sha512(char *input)
{
	uint64_t *hash;

	sha512_algo(input);
	hash = g_hash64;
	ft_printf("%.16llx%.16llx%.16llx%.16llx%.16llx%.16llx%.16llx%.16llx",
	hash[0], hash[1], hash[2], hash[3], hash[4], hash[5], hash[6], hash[7]);
}
