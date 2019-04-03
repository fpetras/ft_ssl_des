/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 17:06:24 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/27 13:59:08 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** Initialize variables to the current hash value
*/

void	init_values(uint32_t *vars)
{
	vars[A] = g_hash[0];
	vars[B] = g_hash[1];
	vars[C] = g_hash[2];
	vars[D] = g_hash[3];
	vars[E] = g_hash[4];
	vars[F] = g_hash[5];
	vars[G] = g_hash[6];
	vars[I] = g_hash[7];
}

void	init_values64(uint64_t *vars)
{
	vars[A] = g_hash64[0];
	vars[B] = g_hash64[1];
	vars[C] = g_hash64[2];
	vars[D] = g_hash64[3];
	vars[E] = g_hash64[4];
	vars[F] = g_hash64[5];
	vars[G] = g_hash64[6];
	vars[I] = g_hash64[7];
}

/*
** Add compressed chunk to the current hash value
*/

void	add_values(uint32_t *vars)
{
	g_hash[0] += vars[A];
	g_hash[1] += vars[B];
	g_hash[2] += vars[C];
	g_hash[3] += vars[D];
	g_hash[4] += vars[E];
	g_hash[5] += vars[F];
	g_hash[6] += vars[G];
	g_hash[7] += vars[I];
}

void	add_values64(uint64_t *vars)
{
	g_hash64[0] += vars[A];
	g_hash64[1] += vars[B];
	g_hash64[2] += vars[C];
	g_hash64[3] += vars[D];
	g_hash64[4] += vars[E];
	g_hash64[5] += vars[F];
	g_hash64[6] += vars[G];
	g_hash64[7] += vars[I];
}
