/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:27:37 by equentin          #+#    #+#             */
/*   Updated: 2025/12/03 12:47:53 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_loop(int fd, char *line, char *buffer)
{
	ssize_t	bytes_read;
	char	*nl;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = 0;
		nl = ft_strchrnl(buffer);
		line = ft_strjoin(line, buffer, nl);
		if (!line)
			return (NULL);
		if (nl)
		{
			ft_strmove(buffer, nl + 1);
			return (line);
		}
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	buffer[0] = 0;
	if (bytes_read == -1 || line[0] == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	char		*line;
	char		*nl;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= MAX_FD)
		return (NULL);
	nl = ft_strchrnl(buffer);
	line = ft_strjoin(NULL, buffer, nl);
	if (!line)
		return (NULL);
	if (nl)
	{
		ft_strmove(buffer, nl + 1);
		return (line);
	}
	return (ft_read_loop(fd, line, buffer));
}
