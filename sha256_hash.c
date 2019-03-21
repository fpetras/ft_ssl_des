/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:05:43 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/20 17:30:36 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		sha256_hash(char *input)
{
	uint32_t *hash;

	sha256_algo(input);
	hash = g_hash;
	ft_printf("%.8x%.8x%.8x%.8x%.8x%.8x%.8x%.8x",
	hash[0], hash[1], hash[2], hash[3], hash[4], hash[5], hash[6], hash[7]);
	return (0);
}
