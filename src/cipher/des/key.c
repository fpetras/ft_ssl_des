/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 11:55:08 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/12 12:41:08 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	generate_key(char *key, char *salt)
{
	(void)salt;
	for (int i = 0; i < 16; i++)
		key[i] = 'A';
	return (0);
}

int			get_key(void)
{
	if (g_k_)
		return (zero_padding(g_key, g_k_));
	else
		return (generate_key(g_key, g_salt));
}
