/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:05:43 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/23 00:07:16 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** SHA-224 output omits hash value 7
*/

void	sha224(char *input)
{
	uint32_t *hash;

	sha224_algo(input);
	hash = g_hash;
	ft_printf("%.8x%.8x%.8x%.8x%.8x%.8x%.8x",
	hash[0], hash[1], hash[2], hash[3], hash[4], hash[5], hash[6]);
}
