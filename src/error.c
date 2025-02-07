/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:09:31 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/10 13:15:29 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		malloc_error(char *ptr)
{
	ptr ? free(ptr) : 0;
	ft_dprintf(2, "Memory allocation failure\n");
	return (EXIT_FAILURE);
}
