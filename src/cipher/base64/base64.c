/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 11:31:39 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/04 15:13:07 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char	radix[] =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

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

void		base64_encode(char *input)
{
	size_t	i;
	size_t	j;
	int		pad;
	char	output[g_input_len + (g_input_len / 3) + 4];

	i = 0;
	j = 0;
	if (!g_input_len)
		return ;
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
	ft_printf("%s", output); // base64 output
//	j = -1;
//	while (output[++j]) // openssl base64 output (with \n every 64 chars)
//		j && !(j % 64) ?
//		ft_printf("\n%c", output[j]) : ft_printf("%c", output[j]);
}

//int		base64(void)
//{
//	char *input;

//	if ((input = (!g_input_file || !ft_strcmp("-", g_input_file)) ?
//		read_stdin() : read_file(g_input_file)) == NULL)
//		return (EXIT_FAILURE);
//	if (!g_opts[OPT_D])
//		base64_encode(input);
//	else
//		base64_decode(input);
//	return (EXIT_SUCCESS);
//}

//int	main()
//{
//	char str[] = "All our Base64 are belong to you";
//	base64_encode(str2, strlen(str2));
//	return (0);
//}
