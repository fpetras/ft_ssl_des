/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endianness.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 14:27:11 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/26 14:36:45 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	change_endianness(uint32_t value)
{
	uint32_t result;

	result = 0;
	result |= (value & 0x000000FF) << 24;
	result |= (value & 0x0000FF00) << 8;
	result |= (value & 0x00FF0000) >> 8;
	result |= (value & 0xFF000000) >> 24;
	return (result);
}

uint64_t	change_endianness64(uint64_t value)
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
