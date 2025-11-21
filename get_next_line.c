/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 08:46:19 by equentin          #+#    #+#             */
/*   Updated: 2025/11/21 16:43:18 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;
	ssize_t		bytes_read;
	size_t		i_buffer;
	size_t		len;
	size_t		i;

	buffer = allocate_new_buffer(buffer);
	if (buffer == NULL)
	{
		free(buffer);
		return (NULL);
	}
	i_buffer = ft_strlen(buffer);
	bytes_read = read(fd, &buffer[i_buffer], BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[i_buffer + bytes_read] = '\0';
		line = get_line_in_buffer(&buffer);
		if (line)
			return (line);
		buffer = allocate_new_buffer(buffer);
		i_buffer = ft_strlen(buffer);
		bytes_read = read(fd, &buffer[i_buffer], BUFFER_SIZE);
	}
	line = get_line_in_buffer(&buffer);
	if (line)
		return (line);
	if (bytes_read >= 0 && buffer && i_buffer > 0)
	{
		len = ft_strlen(buffer);
		line = malloc(len + 1);
		if (!line)
			return (NULL);
		i = 0;
		while (i < len)
		{
			line[i] = buffer[i];
			i++;
		}
		line[i] = '\0';
		free(buffer);
		buffer = NULL;
		return (line);
	}
	free(buffer);
	buffer = NULL;
	return (NULL);
}

// int	main(int ac, char **av)
// {
// 	int		fd;
// 	char	*l;

// 	(void)ac;
// 	(void)av;
// 	l = get_next_line(1);
// 	if (l)
// 	{
// 		printf("'%s'", l);
// 		free(l);
// 	}
// 	else
// 		printf("NONO\n");
// 	return (0);
// }
