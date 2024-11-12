/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:58:05 by lcosta-g          #+#    #+#             */
/*   Updated: 2024/11/12 19:37:06 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*find_next_line(int fd, char *temp);
static char	*get_line(char *temp, int *next_line_start);
static char	*get_rest(char *temp, int next_line_start);

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*line;
	int			start;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = find_next_line(fd, temp);
	if (!temp)
		return (NULL);
	start = 0;
	line = get_line(temp, &start);
	temp = get_rest(temp, start);
	return (line);
}

static char	*find_next_line(int fd, char *temp)
{
	char	*str;
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;

	if (!temp)
	{
		temp = ft_calloc(1, sizeof(char));
		if (!temp)
			return (NULL);
	}
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(temp, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(temp);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		str = ft_strjoin(temp, buffer);
		free(temp);
		temp = str;
	}
	return (temp);
}

static char	*get_line(char *temp, int *next_line_start)
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

static char	*get_rest(char *temp, int next_line_start)
{
	char	*rest;
	int		len;

	len = ft_strlen(temp) - next_line_start;
	if (len <= 0)
	{
		free(temp);
		return (NULL);
	}
	rest = ft_substr(temp, next_line_start, len);
	free(temp);
	return (rest);
}

// int	main(void)
// {
// 	char	*line;
// 	int		fd;
// 	int		i;

// 	i = 0;
// 	fd = open("test", O_RDONLY);
// 	while (i < 5)
// 	{
// 		line = get_next_line(fd);
// 		printf("|%s|\n", line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd);
// }