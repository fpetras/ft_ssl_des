/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:05:43 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/26 15:13:30 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** SHA-384 output omits hash value 6 and 7
*/

void	sha384(char *input)
{
	uint64_t *hash;

	sha384_algo(input);
	hash = g_hash64;
	ft_printf("%.16llx%.16llx%.16llx%.16llx%.16llx%.16llx",
	hash[0], hash[1], hash[2], hash[3], hash[4], hash[5]);
}
