/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 15:29:33 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/06 15:53:05 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char	*concatenate(char *s1, const char *s2, int len1, int len2)
{
	int i;
	int j;

	i = len1;
	j = 0;
	while (j < len2)
	{
		s1[i] = s2[j];
		i++;
		j++;
	}
	s1[i] = '\0';
	return (s1);
}

static char	*copy(char *dst, const char *src, int len1)
{
	int i;

	i = 0;
	while (i < len1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char		*join(char const *s1, char const *s2, size_t len1, size_t len2)
{
	size_t	len;
	char	*s;

	if (!s1 || !s2)
		return (NULL);
	len = len1 + len2;
	s = (char*)malloc(sizeof(char) * (len + 1));
	if (s == NULL)
		return (NULL);
	copy(s, (char*)s1, len1);
	concatenate(s, (char*)s2, len1, len2);
	return (s);
}
