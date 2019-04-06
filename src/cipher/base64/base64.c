/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 11:31:39 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/06 16:45:39 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char	radix[] =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static char table[256] =
{
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
	-1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
	-1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};

static int	invalid_character(char c)
{
	ft_dprintf(2, "ft_ssl: %s: Invalid%scharacter in input stream -- %c\n",
	g_cmd, c == '=' ? " padding " : " ", c);
	return (EXIT_FAILURE);
}

static int	parse_input(char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (!ft_strchr(radix, input[i]) && input[i] != '=' &&
			!ft_isspace(input[i]))
			return (invalid_character(input[i]));
		else if (ft_isspace(input[i]))
		{
			ft_memmove(&input[i], &input[i + 1], ft_strlen(input) - i);
			i--;
		}
		i++;
	}
	i = -1;
	while (input[++i])
		if (input[i] == '=')
			if (!ft_strequ("=", &input[i]) && !ft_strequ("==", &input[i]))
				return (invalid_character(input[i]));
	return (EXIT_SUCCESS);
}

/*
** Relies on input size being a multiple of four
*/

int			base64_decode(int fd, char *input)
{
	int i;
	int input_len;
	unsigned char *in;
//	int output_len;

	if (parse_input(input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!g_input_len)
		return (EXIT_SUCCESS);
	input_len = ft_strlen(input);
	if (input_len % 4)
	{
		ft_dprintf(2, "Invalid input size -- %d. Needs to be a multiple of 4\n",
		input_len);
		return (EXIT_FAILURE);
	}
//	output_len = input_len - (input_len / 4);
//	ft_printf("input_len: %d\noutput_len: %d\n", input_len, output_len);
	i = 0;
	in = (unsigned char*)input;
	while (input_len > 4)
	{
		ft_dprintf(fd, "%c", table[in[i]] << 2 | table[in[i + 1]] >> 4);
		ft_dprintf(fd, "%c", table[in[i + 1]] << 4 | table[in[i + 2]] >> 2);
		ft_dprintf(fd, "%c", table[in[i + 2]] << 6 | table[in[i + 3]]);
		i += 4;
		input_len -= 4;
	}
	if (in[i + 2] != '=' && in[i + 3] == '=')
	{
		ft_dprintf(fd, "%c", table[in[i]] << 2 | table[in[i + 1]] >> 4);
		ft_dprintf(fd, "%c", table[in[i + 1]] << 4 | table[in[i + 2]] >> 2);
		return (EXIT_SUCCESS);
	}
	else if (in[i + 3] == '=')
	{
		ft_dprintf(fd, "%c", table[in[i]] << 2 | table[in[i + 1]] >> 4);
		return (EXIT_SUCCESS);
	}
	if (input_len > 1)
		ft_dprintf(fd, "%c", table[in[i]] << 2 | table[in[i + 1]] >> 4);
	if (input_len > 2)
		ft_dprintf(fd, "%c", table[in[i + 1]] << 4 | table[in[i + 2]] >> 2);
	if (input_len > 3)
		ft_dprintf(fd, "%c", table[in[i + 2]] << 6 | table[in[i + 3]]);
	return (EXIT_SUCCESS);
}

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

static void	padding(char *input, char *output, size_t i, size_t *j)
{
	output[(*j)++] = radix[(input[i] >> 2) & 0x3f];
	if (i == g_input_len - 1)
	{
		output[(*j)++] = radix[(input[i] & 0x3) << 4];
		output[(*j)++] = '=';
	}
	else
	{
		output[(*j)++] = radix[(input[i] & 0x3) << 4 |
		(input[i + 1] & 0xf0) >> 4];
		output[(*j)++] = radix[(input[i + 1] & 0xf) << 2];
	}
	output[(*j)++] = '=';
}

int		base64_encode(int fd, char *input)
{
	size_t	i;
	size_t	j;
	int		pad;
	char	output[g_input_len + (g_input_len / 3) + 4];

	i = 0;
	j = 0;
	if (!g_input_len)
		return (EXIT_SUCCESS);
	(g_opts[OPT_N]) ? print_newline(fd, NULL) : 0;
	pad = (g_input_len >= 2) ? 2 : 1;
	while (i < g_input_len - pad)
	{
		output[j++] = radix[(input[i] >> 2) & 0x3f];
		output[j++] = radix[(input[i] & 0x3) << 4 | (input[i + 1] & 0xf0) >> 4];
		output[j++] = radix[(input[i + 1] & 0xf) << 2 |
		(input[i + 2] & 0xf0) >> 6];
		output[j++] = radix[input[i + 2] & 0x3f];
		i += 3;
	}
	if (i < g_input_len)
		padding(input, output, i, &j);
	output[j++] = '\0';
	(g_opts[OPT_N]) ? print_newline(fd, output) : ft_dprintf(fd, "%s", output);
	return (EXIT_SUCCESS);
}
