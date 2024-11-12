/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:58:05 by lcosta-g          #+#    #+#             */
/*   Updated: 2024/11/12 15:25:31 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*find_next_line(int fd, char buffer[BUFFER_SIZE + 1], char *temp);
static char	*get_line(char *temp, int *next_line_start);
static char	*get_rest(char *temp, int next_line_start);
static void	clean_buffer(char buffer[BUFFER_SIZE]);

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	static char	*temp;
	int			start;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!temp)
		temp = ft_strdup("");
	clean_buffer(buffer);
	temp = find_next_line(fd, buffer, temp);
	if (!temp)
		return (NULL);
	line = get_line(temp, &start);
	if (!line)
		return (NULL);
	temp = get_rest(temp, start);
	return (line);
}

static char	*find_next_line(int fd, char buffer[BUFFER_SIZE + 1], char *temp)
{
	char	*new_str;
	int		read_bytes;

	while (ft_strchr(temp, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == 0 && !ft_strlen(temp))
		{
			free(temp);
			return (NULL);
		}
		if (read_bytes <= 0)
			return (temp);
		buffer[read_bytes] = '\0';
		new_str = ft_strjoin(temp, buffer);
		free(temp);
		temp = new_str;
	}
	return (temp);
}

static char	*get_line(char *temp, int *next_line_start)
{
	int		i;

	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] == '\n')
		*next_line_start = i + 1;
	else
	{
		*next_line_start = i;
		if (i == 0 && temp[i] == '\0')
			return (NULL);
	}
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

static void	clean_buffer(char buffer[BUFFER_SIZE])
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE)
		buffer[i++] = '\0';
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