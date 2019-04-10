/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 13:21:18 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/10 17:44:08 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	highlight_invalid(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isxdigit(str[i]))
			ft_dprintf(2, "%c", str[i]);
		else
			ft_dprintf(2, "%s%c%s", RED, str[i], TEXT_RESET);
		i++;
	}
	ft_dprintf(2, "\n");
}

static int	print_error(char *type, char *str)
{
	ft_dprintf(2, "%s contains non-hexadecimal character: \n", type);
	highlight_invalid(str);
	return (EXIT_FAILURE);
}

static int	is_hex(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isxdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int			invalid_arguments(void)
{
	int ret;

	ret = EXIT_SUCCESS;
	(g_salt && ft_strlen(g_salt) > 16) ? g_salt[16] = '\0' : 0;
	(g_key && ft_strlen(g_key) > 16) ? g_key[16] = '\0' : 0;
	(g_vector && ft_strlen(g_vector) > 16) ? g_vector[16] = '\0' : 0;
	if (g_salt && !is_hex(g_salt))
		ret = print_error("Salt", g_salt);
	if (g_key && !is_hex(g_key))
		ret = print_error("Key", g_key);
	if (g_is_cbc && g_vector && !is_hex(g_vector))
		ret = print_error("Initialization vector", g_vector);
	return (ret);
}
