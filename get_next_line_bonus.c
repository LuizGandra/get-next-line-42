/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:58:05 by lcosta-g          #+#    #+#             */
/*   Updated: 2024/11/13 18:35:30 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*find_next_line(int fd, char *temp);
char	*get_line(char *temp, int *next_line_start);
char	*get_rest(char *temp, int next_line_start);
void	*free_buffer(void *buffer);

char	*get_next_line(int fd)
{
	static t_reader	reader;
	char			*temp;
	char			*line;
	int				start;
	int				i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	i = 0;
	while (i < reader.file_count && reader.files[i] != fd)
		i++;
	if (i == reader.file_count)
	{
		reader.files[i] = fd;
		reader.file_count += 1;
	}
	temp = reader.temp;
	temp = find_next_line(fd, temp);
	if (!temp)
		return (NULL);
	start = 0;
	line = get_line(temp, &start);
	temp = get_rest(temp, start);
	return (line);
}

char	*find_next_line(int fd, char *temp)
{
	char	*str;
	char	*buffer;
	int		bytes_read;

	if (!temp)
		temp = (char *)ft_calloc(1, sizeof(char));
	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (free_buffer(buffer));
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(temp, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free_buffer(buffer);
			return (free_buffer(temp));
		}
		buffer[bytes_read] = '\0';
		str = ft_strjoin(temp, buffer);
		free_buffer(temp);
		temp = str;
	}
	free_buffer(buffer);
	return (temp);
}

char	*get_line(char *temp, int *next_line_start)
{
	int		i;

	i = 0;
	if (!temp[i])
		return (NULL);
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] == '\n')
		i++;
	*next_line_start = i;
	return (ft_substr(temp, 0, *next_line_start));
}

char	*get_rest(char *temp, int next_line_start)
{
	char	*rest;
	int		len;

	len = ft_strlen(temp) - next_line_start;
	if (len <= 0)
		return (free_buffer(temp));
	rest = ft_substr(temp, next_line_start, len);
	free_buffer(temp);
	return (rest);
}