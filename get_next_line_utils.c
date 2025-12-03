/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:27:29 by equentin          #+#    #+#             */
/*   Updated: 2025/12/03 11:04:00 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

char	*ft_strchrnl(char *s)
{
	while (*s)
	{
		if (*s == '\n')
			return (s);
		s++;
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2, char *max)
{
	size_t	i;
	char	*join;
	char	*s1_ptr;

	s1_ptr = s1;
	if (max)
		join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + (max - s2 + 1)
					+ 1));
	else
		join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)
					+ 1));
	if (join == NULL)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	i = 0;
	while (s1_ptr && *s1_ptr)
		join[i++] = *s1_ptr++;
	while (*s2)
	{
		join[i++] = *s2;
		if (*s2 == '\n')
			break ;
		s2++;
	}
	if (s1)
		free(s1);
	join[i] = 0;
	return (join);
}
void	ft_strmove(char *str, char *nl)
{
	const size_t	delta = nl - str;
	size_t			i;
	size_t			len;

	len = ft_strlen(str);
	i = 0;
	while (str[i + delta])
	{
		str[i] = str[i + delta];
		i++;
	}
	while (i < len)
		str[i++] = 0;
}
