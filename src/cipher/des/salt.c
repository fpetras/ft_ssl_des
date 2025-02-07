/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   salt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 09:45:46 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/12 11:50:36 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void to_hex(char *urandom, char *salt, int i)
{
	salt[i] = (urandom[i] >= -128 && urandom[i] <= -113) ? '0' : salt[i];
	salt[i] = (urandom[i] >= -112 && urandom[i] <= -97) ? '1' : salt[i];
	salt[i] = (urandom[i] >= -96 && urandom[i] <= -81) ? '2' : salt[i];
	salt[i] = (urandom[i] >= -80 && urandom[i] <= -65) ? '3' : salt[i];
	salt[i] = (urandom[i] >= -64 && urandom[i] <= -49) ? '4' : salt[i];
	salt[i] = (urandom[i] >= -48 && urandom[i] <= -33) ? '5' : salt[i];
	salt[i] = (urandom[i] >= -32 && urandom[i] <= -17) ? '6' : salt[i];
	salt[i] = (urandom[i] >= -16 && urandom[i] <= -1) ? '7' : salt[i];
	salt[i] = (urandom[i] >= 0 && urandom[i] <= 15) ? '8' : salt[i];
	salt[i] = (urandom[i] >= 16 && urandom[i] <= 31) ? '9' : salt[i];
	salt[i] = (urandom[i] >= 32 && urandom[i] <= 47) ? 'A' : salt[i];
	salt[i] = (urandom[i] >= 48 && urandom[i] <= 63) ? 'B' : salt[i];
	salt[i] = (urandom[i] >= 64 && urandom[i] <= 79) ? 'C' : salt[i];
	salt[i] = (urandom[i] >= 80 && urandom[i] <= 95) ? 'D' : salt[i];
	salt[i] = (urandom[i] >= 96 && urandom[i] <= 111) ? 'E' : salt[i];
	salt[i] = (urandom[i] >= 112 && urandom[i] <= 127) ? 'F' : salt[i];
}

static int	generate_salt(char *salt)
{
	int		fd;
	int		ret;
	int		i;
	char	urandom[16];

	if ((fd = open("/dev/urandom", O_RDONLY)) == -1)
	{
		ft_dprintf(2, "%s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	if ((ret = read(fd, urandom, 16)) < 0)
	{
		ft_dprintf(2, "%s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < 16)
	{
		to_hex(urandom, salt, i);
		i++;
	}
	salt[i] = '\0';
	return (EXIT_SUCCESS);
}

int			set_salt(void)
{
	if (g_s_)
		return (zero_padding(g_salt, g_s_));
	else
		return (generate_salt(g_salt));
}
