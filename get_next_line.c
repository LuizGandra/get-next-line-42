/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:09:54 by lcosta-g          #+#    #+#             */
/*   Updated: 2024/11/09 20:48:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> // REMOVE

int	read_next_buffer(int fd, t_reader *reader, t_line **new)
{
	char	*buffer;
	int		bytes;

	*new = (t_line *)ft_linenew();
	if (!*new)
		return (0);
	bytes = 0;
	buffer = (*new)->buffer;
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes > 0)
		ft_lineadd_back(&reader->line, *new);
	return (bytes);
}

unsigned int	find_line_start(char *str, unsigned int end_i)
{
	int	i;

	i = end_i - 1;
	while (i > 0 && str[i - 1] != '\n')
		i--;
	return (i);
}

int	free_buffers(t_line **line)
{
	t_line	*temp;

	while (*line)
	{
		if ((*line)->end_i == BUFFER_SIZE - 1)
		{
			temp = (*line)->next;
			free(*line);
			*line = temp;
		}
		else
			break;
	}
	if (!*line)
		return (1);
	return (0);
}

char	*join_buffers(t_reader *reader)
{
	char	*str;
	t_line	*line;
	char	*next_end;
	int		start;
	int		count;

	count = 0;
	line = reader->line;
	str = ft_calloc(1, reader->bytes_read + 1);
	while (line)
	{
		start = find_line_start(line->buffer, line->end_i);
		ft_strlcat(str, &line->buffer[start], BUFFER_SIZE * count + (line->end_i - start + 2));
		if (line->next)
		{
			line = line->next;
			count++;
		}
		else
			break;
	}
	if (!free_buffers(&reader->line))
	{
		next_end = ft_strnchr(&line->buffer[line->end_i + 1], '\n', BUFFER_SIZE - start - 1);
		reader->bytes_read = next_end - &line->buffer[line->end_i + 1];
		line->end_i = next_end - line->buffer;
	}
	else
		reader->bytes_read = 0;
	return (str);
}

char	*get_next_line(int fd)
{
	static t_reader	reader;
	t_line			*new;
	int				i;

	if (read_next_buffer(fd, &reader, &new) > 0)
	{
		i = 0;
		while (i < BUFFER_SIZE)
		{
			if (new->buffer[i++] == '\n' && i != BUFFER_SIZE - 1)
				break ;
		}
		reader.bytes_read += i;
		// printf("gnl rodou: %zu e buffer: %s\n", reader.bytes_read, new->buffer);
		new->end_i = (i - 1);
		if (reader.bytes_read == BUFFER_SIZE && new->buffer[new->end_i] != '\n')
			return (get_next_line(fd));
		return (join_buffers(&reader));
	}
	return (NULL);

}

#include <fcntl.h> // REMOVE

int	main(void)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open("gnl_test.txt", O_RDONLY);
	while (i < 2)
	{
		line = get_next_line(fd);
		printf("%s", line);
		i++;
	}
	close(fd);
}
