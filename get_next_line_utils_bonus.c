/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 08:46:22 by equentin          #+#    #+#             */
/*   Updated: 2025/11/26 08:48:39 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	if (str == NULL)
		return (len);
	while (str[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_substr(char const *s, size_t len)
{
	size_t	count;
	size_t	i;
	char	*sub;

	count = 0;
	while (s[count] && count < len)
		count++;
	sub = (char *)malloc(sizeof(char) * (count + 1));
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (count--)
	{
		sub[i] = s[i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*allocate_new_buffer(char *old_buf)
{
	size_t	old_buf_size;
	char	*new_buf;

	old_buf_size = ft_strlen(old_buf);
	new_buf = (char *)malloc(sizeof(char) * (old_buf_size + BUFFER_SIZE + 1));
	if (new_buf == NULL)
	{
		if (old_buf)
			free(old_buf);
		old_buf = NULL;
		return (NULL);
	}
	old_buf_size = 0;
	while (old_buf && old_buf[old_buf_size])
	{
		new_buf[old_buf_size] = old_buf[old_buf_size];
		old_buf_size++;
	}
	new_buf[old_buf_size] = '\0';
	free(old_buf);
	return (new_buf);
}
