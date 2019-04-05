/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 17:47:39 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/05 01:33:12 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	print_input(char *input, size_t input_len)
{
	size_t i;

	i = 0;
	while (i < input_len)
	{
		ft_printf("%c", input[i]);
		i++;
	}
}
