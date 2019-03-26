/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 14:22:49 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/26 14:37:00 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	leftrotate(uint32_t x, uint32_t n)
{
	return ((x << n) | (x >> (32 - n)));
}

uint32_t	rightrotate(uint32_t x, uint32_t n)
{
	return ((x >> n) | (x << (32 - n)));
}

uint64_t	rightrotate64(uint64_t x, uint64_t n)
{
	return ((x >> n) | (x << (64 - n)));
}
