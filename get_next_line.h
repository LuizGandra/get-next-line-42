/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:49:57 by marvin            #+#    #+#             */
/*   Updated: 2024/11/09 20:28:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

#include <unistd.h>
#include <stdlib.h>

typedef struct s_line {
	char			buffer[BUFFER_SIZE];
	int				end_i;
	struct s_line	*next;
}	t_line;

typedef struct s_reader {
	t_line	*line;
	size_t	bytes_read;
}	t_reader;

char	*get_next_line(int fd);

char		*ft_strnchr(const char *s, int c, int n);
void		*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

t_line	*ft_linenew(void);
void		ft_lineadd_back(t_line **line, t_line *new);

#endif