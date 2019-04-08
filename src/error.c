/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:09:31 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/08 14:38:42 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		malloc_error(char *ptr)
{
	ptr ? free(ptr) : 0;
	ft_dprintf(2, "Memory allocation failure\n");
	return (EXIT_FAILURE);
}

int		invalid_character(char c)
{
	ft_dprintf(2, "ft_ssl: %s: Invalid%scharacter in input stream -- %c\n",
	g_cmd, c == '=' ? " padding " : " ", c);
	return (EXIT_FAILURE);
}
