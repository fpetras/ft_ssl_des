/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_encode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 11:31:39 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/15 15:31:46 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char	g_radix[65] = ALNUM;

static void	print_newline(int fd, char *output)
{
	static int	first_line = 1;
	int			j;

	if (!output)
		return ;
	j = -1;
	!first_line ? ft_dprintf(fd, "\n") : 0;
	while (output[++j])
		j && !(j % 64) ?
		ft_dprintf(fd, "\n%c", output[j]) : ft_printf("%c", output[j]);
	first_line = 0;
}

static void	padding_encode(char *input, char *output, size_t i, size_t j)
{
	if (i < g_input_len)
	{
		output[j++] = g_radix[(input[i] >> 2) & 0x3f];
		if (i == g_input_len - 1)
		{
			output[j++] = g_radix[(input[i] & 0x3) << 4];
			output[j++] = (g_is_base64url) ? '\0' : '=';
		}
		else
		{
			output[j++] = g_radix[(input[i] & 0x3) << 4 |
			(input[i + 1] & 0xf0) >> 4];
			output[j++] = g_radix[(input[i + 1] & 0xf) << 2];
		}
		output[j++] = (g_is_base64url) ? '\0' : '=';
	}
	output[j++] = '\0';
}

/*
** Base64URL uses '-' and '_' instead of '+' and '/' and omits padding
*/

int			base64_encode(int fd, char *in)
{
	size_t	i;
	size_t	j;
	int		pad;
	char	out[g_input_len + (g_input_len / 3) + 4];

	if (!g_input_len)
		return (EXIT_SUCCESS);
	g_opts[OPT_N] ? print_newline(fd, NULL) : 0;
	i = 0;
	j = 0;
	pad = (g_input_len >= 2) ? 2 : 1;
	if (!g_radix[62])
		g_is_base64url ? ft_strcat(g_radix, "-_") : ft_strcat(g_radix, "+/");
	while (i < g_input_len - pad)
	{
		out[j++] = g_radix[(in[i] >> 2) & 0x3f];
		out[j++] = g_radix[(in[i] & 0x3) << 4 | (in[i + 1] & 0xf0) >> 4];
		out[j++] = g_radix[(in[i + 1] & 0xf) << 2 | (in[i + 2] & 0xf0) >> 6];
		out[j++] = g_radix[in[i + 2] & 0x3f];
		i += 3;
	}
	padding_encode(in, out, i, j);
	g_opts[OPT_N] ? print_newline(fd, out) : ft_dprintf(fd, "%s", out);
	return (EXIT_SUCCESS);
}
