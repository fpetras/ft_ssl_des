/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 13:21:18 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/11 10:26:47 by fpetras          ###   ########.fr       */
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
	(g_s_ && ft_strlen(g_s_) > 16) ? g_s_[16] = '\0' : 0;
	(g_k_ && ft_strlen(g_k_) > 16) ? g_k_[16] = '\0' : 0;
	(g_v_ && ft_strlen(g_v_) > 16) ? g_v_[16] = '\0' : 0;
	if (g_s_ && !is_hex(g_s_))
		ret = print_error("Salt", g_s_);
	if (g_k_ && !is_hex(g_k_))
		ret = print_error("Key", g_k_);
	if (g_is_cbc && g_v_ && !is_hex(g_v_))
		ret = print_error("Initialization vector", g_v_);
	return (ret);
}
