/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_decode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 11:31:39 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/09 15:03:44 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char g_table[256] =
{
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
	-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
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

static int	parse_input(char *input)
{
	int i;

	i = -1;
	while (input[++i])
		if (input[i] == '-' || input[i] == '_')
			input[i] = (input[i] == '-') ? '+' : '/';
	i = 0;
	while (input[i])
	{
		if (!ft_strchr(ALNUM"+/", input[i]) && input[i] != '=' &&
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
			if (ft_strcmp("=", &input[i]) && ft_strcmp("==", &input[i]))
				return (invalid_character(input[i]));
	return (EXIT_SUCCESS);
}

/*
** Pads the encoded input if padding characters are missing
** Truncates the input if it cannot be padded
**				(i.e. if a single character is remaining at the end)
** Pads or truncates the input if it was improperly padded
**				(i.e. if it contains padding but is not a multiple of 4)
** e.g.
** "ABCDE[=[=]]" will be truncated to "ABCD"
** "ABCDEF[=]" will be padded to "ABCDEF=="
*/

static char	*pad_input(char *input, int *input_len)
{
	char *padded_input;

	padded_input = NULL;
	if ((*input_len) % 4 == 2 || (*input_len) % 4 == 3)
	{
		padded_input = ft_strjoin(input, (*input_len) % 4 == 2 ? "==" : "=");
		if (padded_input == NULL || g_is_base64url)
			return (padded_input);
		ft_dprintf(2, "Invalid input size. Your input has been padded");
		ft_dprintf(2, " by %s %s.\n", (*input_len) % 4 == 2 ? "two" : "one",
		(*input_len) % 4 == 2 ? "characters" : "character");
		(*input_len) += ((*input_len) % 4 == 2) ? 2 : 1;
	}
	return (padded_input);
}

static int	truncate_input(char *input, int *input_len)
{
	if ((*input_len) % 4 == 1)
	{
		input[(*input_len) - 1] = '\0';
		(*input_len) -= 1;
		ft_dprintf(2, "Invalid input size. Your input has been truncated");
		ft_dprintf(2, " by one character.\n");
	}
	else if (((*input_len) % 4 == 2 && ft_strchr(input, '=')) ||
		((*input_len) % 4 == 3 &&
		((ft_strchr(input, '=') && ft_strrchr(input, '=')) &&
		(ft_strchr(input, '=') != ft_strrchr(input, '=')))))
	{
		ft_strchr(input, '=')[-1] = '\0';
		ft_dprintf(2, "Invalid input size. Your input has been truncated");
		ft_dprintf(2, " by %s characters.\n",
		(*input_len) % 4 == 2 ? "two" : "three");
		(*input_len) -= (*input_len) % 4 == 2 ? 2 : 3;
	}
	else
		return (0);
	return (1);
}

static int	padding_decode(int fd, unsigned char *in, char *padded_input)
{
	if (in[3] == '=')
		ft_dprintf(fd, "%c", g_table[in[0]] << 2 | g_table[in[1]] >> 4);
	if (in[2] != '=' && in[3] == '=')
		ft_dprintf(fd, "%c", g_table[in[1]] << 4 | g_table[in[2]] >> 2);
	padded_input ? free(padded_input) : 0;
	return (EXIT_SUCCESS);
}

int			base64_decode(int fd, char *input)
{
	int				i;
	int				input_len;
	char			*padded_input;
	unsigned char	*in;

	if (parse_input(input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (((input_len = ft_strlen(input)) >= 0 && input_len <= 2) ||
		(input_len == 3 && input[1] == '=' && input[2] == '='))
		return (EXIT_SUCCESS);
	i = 0;
	padded_input = NULL;
	!truncate_input(input, &input_len) ?
	padded_input = pad_input(input, &input_len) : 0;
	in = padded_input ? (unsigned char*)padded_input : (unsigned char*)input;
	while (input_len >= 4 && in[i + 3] != '=')
	{
		ft_dprintf(fd, "%c", g_table[in[i]] << 2 | g_table[in[i + 1]] >> 4);
		ft_dprintf(fd, "%c", g_table[in[i + 1]] << 4 | g_table[in[i + 2]] >> 2);
		ft_dprintf(fd, "%c", g_table[in[i + 2]] << 6 | g_table[in[i + 3]]);
		i += 4;
		input_len -= 4;
	}
	return (padding_decode(fd, &in[i], padded_input));
}
