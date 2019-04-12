/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   password.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 11:53:54 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/12 13:12:42 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

#define ENTER_ECB_PASS "Enter des-ecb encryption password:"
#define ENTER_CBC_PASS "Enter des-cbc encryption password:"
#define VERIFY_ECB_PASS "Verify des-ecb encryption password:"
#define VERIFY_CBC_PASS "Verify des-cbc encryption password:"

/*
** getpass() function leaves its result in an internal static object
** and returns a pointer to that object.
** Subsequent calls to getpass will modify the same object.
** That's the reason for the strcpy shenanigans.
*/

int		get_password(void)
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
	if (ft_strlen(g_passwd) > _PASSWORD_LEN)
	{
		ft_memset(g_passwd, 0, sizeof(g_passwd));
		ft_dprintf(2, "Error: password is too long (max: %d characters)\n",
		_PASSWORD_LEN);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
