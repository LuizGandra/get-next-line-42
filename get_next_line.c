/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:58:05 by lcosta-g          #+#    #+#             */
/*   Updated: 2024/11/11 17:10:16 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_reader	reader;
	char			buffer[BUFFER_SIZE];
	int				bytes;
	int				i;

	if (contains_newline(reader.line))
		return (create_string(&reader));
	reader.bytes_read = get_bytes_read(reader.line);
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes > 0)
	{
		if (bytes < BUFFER_SIZE)
			clean_buffer(buffer, bytes);
		save_buffer(&reader, buffer, bytes);
		i = 0;
		while (i < BUFFER_SIZE && buffer[i] != '\n')
			i++;
		if (i == BUFFER_SIZE)
		{
			reader.bytes_read += i;
			return (get_next_line(fd));
		}
		reader.bytes_read += (i + 1);
		return (create_string(&reader));
	}
	return (create_string(&reader));
}

int	contains_newline(t_line *line)
{
	while (line)
	{
		if (line->c == '\n')
			return (1);
		line = line->next;
	}
	return (0);
}

void	save_buffer(t_reader *reader, char buffer[BUFFER_SIZE], int bytes)
{
	t_line	*new;
	int		i;

	i = 0;
	while (i < bytes)
	{
		new = ft_linenew(&buffer[i++]);
		if (!new)
			free_line(reader);
		ft_lineadd_back(&reader->line, new);
	}
}

char	*create_string(t_reader *reader)
{
	t_line			*line;
	char			*str;
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

int	get_bytes_read(t_line *line)
{
	int	bytes_read;

	if (!line)
		return (0);
	bytes_read = 0;
	while (line && line->c != '\n')
	{
		bytes_read++;
		line = line->next;
	}
	return (bytes_read);
}

void	free_line(t_reader *reader)
{
	t_line				*temp;
	unsigned int		i;

	i = 0;
	while (reader->line && i < reader->bytes_read)
	{
		temp = reader->line->next;
		free(reader->line);
		reader->line = temp;
		i++;
	}
}

// int	main(void)
// {
// 	int		fd;

// 	fd = 0;
// 	printf("Output: |%s|\n", get_next_line(fd));
// 	printf("Output: |%s|\n", get_next_line(fd));
// 	printf("Output: |%s|\n", get_next_line(fd));
// 	close(fd);
// }

// int	main(void)
// {
// 	char	*line;
// 	int		fd;
// 	int		i;

// 	i = 0;
// 	fd = open("alternate_line_nl_no_nl", O_RDONLY);
// 	while (i < 4)
// 	{
// 		line = get_next_line(fd);
// 		printf("|%s", line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd);
// }