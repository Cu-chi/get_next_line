/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:27:37 by equentin          #+#    #+#             */
/*   Updated: 2025/12/04 10:32:32 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	*gnl_free(char *stash, char *buffer)
{
	if (stash)
		free(stash);
	if (buffer)
		free(buffer);
	return (NULL);
}

static char	*gnl_read(int fd, char *stash)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (gnl_free(stash, buffer));
	bytes_read = 1;
	while (!ft_strchrnl(stash) && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (gnl_free(stash, buffer));
		buffer[bytes_read] = '\0';
		if (bytes_read > 0)
		{
			stash = ft_strjoin(stash, buffer);
			if (!stash)
				return (gnl_free(stash, buffer));
		}
	}
	free(buffer);
	return (stash);
}

static char	*gnl_get_line(char *stash)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*gnl_new_stash(char *stash)
{
	char	*new_stash;
	size_t	i;
	size_t	j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!new_stash)
	{
		free(stash);
		return (NULL);
	}
	i++;
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= MAX_FD || MAX_FD < 0)
		return (NULL);
	stash[fd] = gnl_read(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = gnl_get_line(stash[fd]);
	if (!line)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = gnl_new_stash(stash[fd]);
	return (line);
}
