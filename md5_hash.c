/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:05:40 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/15 15:39:47 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		md5_hash(char *input)
{
	size_t	len;
	int		i;
	uint8_t	*hash;

	len = ft_strlen(input);
	md5_algo((uint8_t*)input, len);
	i = 0;
	while (i < 4)
	{
		hash = (uint8_t*)&g_hash[i];
		ft_printf("%2.2x%2.2x%2.2x%2.2x", hash[0], hash[1], hash[2], hash[3]);
		i++;
	}
	return (0);
}
