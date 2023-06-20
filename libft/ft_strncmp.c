/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com:>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:02:50 by fsalazar          #+#    #+#             */
/*   Updated: 2023/03/10 16:19:30 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strcmp(const char *s1, const char *s2)
{
	unsigned char *ss1;
	unsigned char *ss2;
	size_t a;

	if (!s1 || !s2)
		return (-1);
	ss1 = (unsigned char *) s1;
	ss2 = (unsigned char *) s2;
	a = 0;
	while (ss1[a] != '\0' || ss2[a] != '\0')
	{
		if (ss1[a] != ss2[a])
			return (ss1[a] - ss2[a]);
		a++;
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			a;
	unsigned char	*ss1;
	unsigned char	*ss2;

	a = 0;
	if (!s1 || !s2)
		return (-1);
	ss1 = (unsigned char *) s1;
	ss2 = (unsigned char *) s2;
	while (a < n)
	{
		if (ss1[a] != ss2[a])
			return (ss1[a] - ss2[a]);
		else if (ss1[a] == '\0' || ss2[a] == '\0')
			return (ss1[a] - ss2[a]);
		a++;
	}
	return (0);
}
