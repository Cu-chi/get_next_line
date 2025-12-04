/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:27:41 by equentin          #+#    #+#             */
/*   Updated: 2025/12/04 10:29:03 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif
# ifndef MAX_FD
#  define MAX_FD 1024
# endif
/* utils */
size_t	ft_strlen(char *str);
char	*ft_strchrnl(char *s);
char	*ft_strjoin(char *s1, char *s2);
void	ft_strmove(char *str, char *nl);

char	*get_next_line(int fd);

#endif
