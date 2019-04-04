/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cipher.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:26:10 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/04 12:16:04 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CIPHER_H
# define CIPHER_H

# include <pwd.h>

# define BASE64_OPT_STR "deio"
# define DES_OPT_STR "adeiokpsv"

char	*g_input_file;
char	*g_output_file;
char	*g_key;
char	*g_passwd;
char	*g_salt;
char	*g_vector;
int		g_is_base64;
int		g_is_ecb;
int		g_is_cbc;

int		command_is_cipher(char **av);
int		parse_cipher_options(int ac, char **av);
int		print_base64_usage(char **av);
int		print_des_usage(char **av);

int		cipher(void);
int		read_base64(void);
void	base64_encode(char *input);

#endif
