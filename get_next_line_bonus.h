/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 08:46:14 by equentin          #+#    #+#             */
/*   Updated: 2025/11/26 08:48:25 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

# define MAX_FD 1024

char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, size_t len);
char	*allocate_new_buffer(char *old_buf);
size_t	ft_strlen(char *str);
char	*get_next_line(int fd);

#endif
