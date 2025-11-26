/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 08:46:19 by equentin          #+#    #+#             */
/*   Updated: 2025/11/26 09:39:38 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*remove_line_from_buffer(char **buffer, size_t line_len)
{
	char			*new_buf;
	const size_t	old_buf_len = ft_strlen(*buffer);
	size_t			i;

	new_buf = (char *)malloc(sizeof(char) * (old_buf_len - line_len + 1));
	if (new_buf == NULL)
	{
		free(*buffer);
		*buffer = NULL;
		return (NULL);
	}
	i = 0;
	while (i < old_buf_len - line_len)
	{
		new_buf[i] = (*buffer)[line_len + i + 1];
		i++;
	}
	new_buf[i] = '\0';
	free(*buffer);
	return (new_buf);
}

static char	*get_end_line_no_nl(char **buffer)
{
	char	*line;
	size_t	buf_len;

	buf_len = ft_strlen(*buffer);
	if (buf_len == 0)
		return (NULL);
	line = ft_substr(*buffer, buf_len);
	free(*buffer);
	*buffer = NULL;
	return (line);
}

static char	*get_line_in_buffer(char **buffer, int fd_end)
{
	char	*line;
	char	*nl;

	nl = ft_strchr(*buffer, '\n');
	if (fd_end && !nl)
		return (get_end_line_no_nl(buffer));
	if (!nl)
		return (NULL);
	line = ft_substr(*buffer, nl - *buffer + 1);
	if (line == NULL)
		return (NULL);
	*buffer = remove_line_from_buffer(buffer, nl - *buffer);
	if (*buffer == NULL)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static char	*last_line(ssize_t bytes_read, char **buffer)
{
	char	*line;

	if (bytes_read == 0)
	{
		line = get_line_in_buffer(&(*buffer), 1);
		if (line)
			return (line);
	}
	free(*buffer);
	*buffer = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD] = {0};
	char		*line;
	ssize_t		bytes_read;
	size_t		i_buffer;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = allocate_new_buffer(buffer[fd]);
	if (buffer[fd] == NULL)
		return (NULL);
	i_buffer = ft_strlen(buffer[fd]);
	bytes_read = read(fd, &buffer[fd][i_buffer], BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[fd][i_buffer + bytes_read] = '\0';
		line = get_line_in_buffer(&buffer[fd], 0);
		if (line)
			return (line);
		buffer[fd] = allocate_new_buffer(buffer[fd]);
		if (buffer[fd] == NULL)
			return (NULL);
		i_buffer = ft_strlen(buffer[fd]);
		bytes_read = read(fd, &buffer[fd][i_buffer], BUFFER_SIZE);
	}
	return (last_line(bytes_read, &buffer[fd]));
}

// #include <fcntl.h>
// #include <stdio.h>
// int	main(int ac, char **av)
// {
// 	int		fda;
// 	int		fdb;
// 	char	*l;

// 	(void)ac;
// 	(void)av;
// 	fda = open("a", O_RDONLY);
// 	fdb = open("b", O_RDONLY);
// 	l = get_next_line(fda);
// 	printf("'%s'", l);
// 	l = get_next_line(fdb);
// 	printf("'%s'", l);
// 	l = get_next_line(fda);
// 	printf("'%s'", l);
// 	l = get_next_line(fda);
// 	printf("'%s'", l);
// 	l = get_next_line(fdb);
// 	printf("'%s'", l);
// 	l = get_next_line(fdb);
// 	printf("'%s'", l);
// 	l = get_next_line(fdb);
// 	printf("NULL ? -> '%s'", l);
// 	l = get_next_line(fda);
// 	printf("'%s'", l);
// 	l = get_next_line(fda);
// 	printf("NULL ? -> '%s'", l);
// 	return (0);
// }
