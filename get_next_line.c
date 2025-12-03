/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:27:37 by equentin          #+#    #+#             */
/*   Updated: 2025/12/03 11:14:37 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	char		*line;
	char		*nl;
	ssize_t		bytes_read;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= MAX_FD)
		return (NULL);
	nl = ft_strchrnl(buffer);
	if (nl)
	{
		line = ft_strjoin(NULL, buffer, nl);
		ft_strmove(buffer, nl + 1);
		return (line);
	}
	line = ft_strjoin(NULL, buffer, 0);
	if (!line)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = 0;
			nl = ft_strchrnl(buffer);
			if (nl)
			{
				line = ft_strjoin(line, buffer, nl);
				ft_strmove(buffer, nl + 1);
				return (line);
			}
			line = ft_strjoin(line, buffer, 0);
			if (!line)
				return (NULL);
		}
		if (bytes_read == -1)
		{
			buffer[0] = 0;
			if (line)
				free(line);
			return (NULL);
		}
	}
	buffer[0] = 0;
	if (line[0] == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

#include <fcntl.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	int	fd;
	(void)ac;
	(void)av;
	fd = open("a", O_RDONLY);
	char *l = get_next_line(fd);
	printf("%s", l);
	free(l);
	return (0);
}
