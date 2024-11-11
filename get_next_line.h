/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:58:16 by lcosta-g          #+#    #+#             */
/*   Updated: 2024/11/11 17:06:27 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>
#include <fcntl.h> // REMOVE
#include <stdio.h> // REMOVE

typedef struct s_line
{
	char					c;
	struct s_line			*next;
}	t_line;

typedef struct s_reader
{
	t_line	*line;
	size_t	bytes_read;
}	t_reader;

void	free_line(t_reader *reader);
char	*create_string(t_reader *reader);
void	save_buffer(t_reader *reader, char buffer[BUFFER_SIZE], int bytes);
int		get_bytes_read(t_line *line);
char	*get_next_line(int fd);

int	contains_newline(t_line *line); // REMOVE

void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
void	clean_buffer(char buffer[BUFFER_SIZE], int i);
t_line	*ft_linenew(void	*content);
void	ft_lineadd_back(t_line **line, t_line *new);

#endif