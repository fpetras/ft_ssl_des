/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 13:21:18 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/10 17:12:55 by fpetras          ###   ########.fr       */
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

static int	print_error(int len, char *type, char *str)
{
	if ((ft_strcmp(type, "Key") && len > 16) ||
		(!ft_strcmp(type, "Key") && len > 32))
		ft_dprintf(2, "Error: ft_ssl: %s: %s is too large.\n", g_cmd, type);
	else
	{
		ft_dprintf(2, "%s contains non-hexadecimal digit: \n", type);
		highlight_invalid(str);
	}
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
	int len;
	int ret;

	ret = EXIT_SUCCESS;
	if (g_salt && ((len = ft_strlen(g_salt) > 16) || !is_hex(g_salt)))
		ret = print_error(len, "Salt", g_salt);
	if (g_key && ((len = ft_strlen(g_key) > 32) || !is_hex(g_key)))
		ret = print_error(len, "Key", g_key);
	if (g_is_cbc && g_vector && ((len = ft_strlen(g_vector) > 16) ||
		!is_hex(g_vector)))
		ret = print_error(len, "Initialization vector", g_vector);
	return (ret);
}
