/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:05:40 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/22 16:44:49 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	md5_hash(char *input)
{
	int		i;
	uint8_t	*hash;

	md5_algo(input);
	i = 0;
	while (i < 4)
	{
		hash = (uint8_t*)&g_hash[i];
		ft_printf("%2.2x%2.2x%2.2x%2.2x", hash[0], hash[1], hash[2], hash[3]);
		i++;
	}
}
