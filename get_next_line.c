/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:09:54 by lcosta-g          #+#    #+#             */
/*   Updated: 2024/11/10 12:49:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> // REMOVE

char	*get_next_line(int fd)
{
	static t_reader	reader;
	char	*str;
	int		bytes;
	int		i;

	reader.bytes_read = get_bytes_read(reader.line);
	printf("\nbytes: %zu\n", reader.bytes_read);
	str = (char *)ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!str)
		return (NULL);
	bytes = read(fd, str, BUFFER_SIZE);
	if (bytes > 0)
	{
		save_buffer(&reader, str);
		i = 0;
		while (i < BUFFER_SIZE && str[i - 1] != '\n')
			i++;
		reader.bytes_read += i;
		if (i == BUFFER_SIZE && str[BUFFER_SIZE - 1] != '\n')
			return (get_next_line(fd));
		return (create_string(&reader));
	}
	return (create_string(&reader));
}

void free_line(t_reader *reader)
{
	t_line				*temp;
	unsigned int	i;

	i = 0;
	while (reader->line && i < reader->bytes_read)
	{
		temp = reader->line->next;
		free(reader->line);
		reader->line = temp;
		i++;
	}
}

char	*create_string(t_reader *reader)
{
	t_line				*line;
	char					*str;
	unsigned int	i;

	if (!reader->line)
		return (NULL);
	line = reader->line;
	str = ft_calloc(1, reader->bytes_read + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (line && i < reader->bytes_read)
	{
		str[i++] = line->c;
		line = line->next;
	}
	free_line(reader);
	return (str);
}

void	save_buffer(t_reader *reader, char buffer[BUFFER_SIZE])
{
	t_line	*new;
	int	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		new = ft_linenew(&buffer[i++]);
		if (!new)
			free_line(reader);
		ft_lineadd_back(&reader->line, new);
	}
}

int	get_bytes_read(t_line *line)
{
	int	bytes_read;
	
	if (!line)
		return 0;
	bytes_read = 1;
	while (line && line->c != '\n')
	{
		bytes_read++;
		line = line->next;
	}

	return (bytes_read);
}

#include <fcntl.h> // REMOVE
int	main(void)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open("gnl_test.txt", O_RDONLY);
	while (i < 6)
	{
		line = get_next_line(fd);
		printf("%s", line);
		i++;
	}
	close(fd);
}
