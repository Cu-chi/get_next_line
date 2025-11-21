/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 08:46:22 by equentin          #+#    #+#             */
/*   Updated: 2025/11/21 12:13:31 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*allocate_new_buffer(char *old_buf)
{
	size_t	old_buf_size;
	char	*new_buf;

	old_buf_size = ft_strlen(old_buf);
	new_buf = (char *)malloc(sizeof(char) * (old_buf_size + BUFFER_SIZE + 1));
	if (new_buf == NULL)
		return (NULL);
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

static char	*remove_line_from_buffer(char **buffer, size_t line_len)
{
	char			*new_buf;
	const size_t	old_buf_len = ft_strlen(*buffer);
	size_t	i;

	new_buf = (char *)malloc(sizeof(char) * (old_buf_len - line_len + 1));
	if (new_buf == NULL)
		return (NULL);
	i = 0;
	while (i < old_buf_len - line_len)
	{
		new_buf[i] = (*buffer)[line_len + i + 1];
		i++;
	}
	//new_buf[i] = '\0';
	free(*buffer);
	return (new_buf);
}

char	*get_line_in_buffer(char **buffer)
{
	size_t	i;
	size_t	j;
	char	*line;

	i = 0;
	while ((*buffer)[i])
	{
		if ((*buffer)[i] == '\n')
		{
			line = (char *)malloc(sizeof(char) * (i + 2));
			if (line == NULL)
				return (NULL);
			j = 0;
			while (j <= i)
			{
				line[j] = (*buffer)[j];
				j++;
			}
			line[j] = '\0';
			*buffer = remove_line_from_buffer(buffer, i);
			if (*buffer == NULL)
				return (NULL);
			else
				return (line);
		}
		i++;
	}
	return (0);
}
