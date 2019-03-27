/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endianness.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 14:27:11 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/27 16:53:54 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	change_endianness(uint32_t value)
{
	uint32_t result;

	result = 0;
	result |= (value & 0x000000ff) << 24;
	result |= (value & 0x0000ff00) << 8;
	result |= (value & 0x00ff0000) >> 8;
	result |= (value & 0xff000000) >> 24;
	return (result);
}

uint64_t	change_endianness64(uint64_t value)
{
	uint64_t result;

	result = 0;
	result |= (value & 0xff00000000000000) >> 56;
	result |= (value & 0x00ff000000000000) >> 40;
	result |= (value & 0x0000ff0000000000) >> 24;
	result |= (value & 0x000000ff00000000) >> 8;
	result |= (value & 0x00000000ff000000) << 8;
	result |= (value & 0x0000000000ff0000) << 24;
	result |= (value & 0x000000000000ff00) << 40;
	result |= (value & 0x00000000000000ff) << 56;
	return (result);
}
