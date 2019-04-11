/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 11:33:21 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/11 10:28:57 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

#define ENTER_ECB_PASS "Enter des-ecb encryption password:"
#define ENTER_CBC_PASS "Enter des-cbc encryption password:"
#define VERIFY_ECB_PASS "Enter des-ecb encryption password:"
#define VERIFY_CBC_PASS "Enter des-cbc encryption password:"

/*
** getpass() function leaves its result in an internal static object
** and returns a pointer to that object.
** Subsequent calls to getpass will modify the same object.
** That's the reason for the strcpy shenanigans.
*/

static int	get_password(void)
{
	char passwd1[_PASSWORD_LEN + 1];
	char passwd2[_PASSWORD_LEN + 1];

	g_passwd = getpass(g_is_ecb ? ENTER_ECB_PASS : ENTER_CBC_PASS);
	ft_strcpy(passwd1, g_passwd);
	g_passwd = getpass(g_is_ecb ? VERIFY_ECB_PASS : VERIFY_CBC_PASS);
	ft_strcpy(passwd2, g_passwd);
	if (ft_strcmp(passwd1, passwd2))
	{
		ft_dprintf(2, "Error: passwords are not identical\n");
		ft_memset(passwd1, 0, sizeof(passwd1));
		ft_memset(passwd2, 0, sizeof(passwd2));
		ft_memset(g_passwd, 0, ft_strlen(g_passwd));
		return (EXIT_FAILURE);
	}
	ft_memset(passwd1, 0, sizeof(passwd1));
	ft_memset(passwd2, 0, sizeof(passwd2));
	return (EXIT_SUCCESS);
}

int			des(void)
{
	int		fd;

	if (invalid_arguments() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!g_input_file || !ft_strcmp(g_input_file, "-"))
		fd = STDIN_FILENO;
	else if ((fd = open(g_input_file, O_RDONLY)) == -1)
	{
			ft_dprintf(2, "ft_ssl: %s: %s: %s\n",
			g_cmd, g_input_file, strerror(errno));
			return (EXIT_FAILURE);
	}
	if (!g_k_ && !g_passwd && get_password() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_strlen(g_passwd) > _PASSWORD_LEN)
	{
		ft_dprintf(2, "Error: password is too long (max: %d characters)\n",
		_PASSWORD_LEN);
		return (EXIT_FAILURE);
	}
	set_salt();
	ft_printf("salt=%s\n", g_salt);
	ft_printf("key=%s\n", g_k_ ? g_k_ : g_key);
//	if (!g_k_)
//		get_key();
//	if (g_is_cbc && !g_vector)
//		get_iv();
//	read_input();
	return (EXIT_SUCCESS);
}
