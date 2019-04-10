/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 13:14:39 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/10 13:15:21 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		invalid_character(char c)
{
	ft_dprintf(2, "ft_ssl: %s: Invalid%scharacter in input stream -- %c\n",
	g_cmd, c == '=' ? " padding " : " ", c);
	return (EXIT_FAILURE);
}
