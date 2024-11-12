/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:58:05 by lcosta-g          #+#    #+#             */
/*   Updated: 2024/11/12 14:33:33 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	find_next_line(int fd, char buffer[BUFFER_SIZE + 1], char *temp);
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

static void	find_next_line(int fd, char buffer[BUFFER_SIZE + 1], char *temp)
{
	// * lê até achar um \n e atribui o valor lido no temp
	char	*new_str;
	int		read_bytes;

	// ! se tiver um \n no temp, ele não lê mais, o que resolve o problema
	// ! que eu tava tendo antes
	while (ft_strchr(temp, '\n')) // * lê enquanto não ler um \n no temp
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		// * se não ler nada e não tiver nada no temp, o arquivo acabou
		if (read_bytes == 0 && !ft_strlen(temp))
		{
			free(temp);
			return (NULL);
		}
		// * se não ler nada e tiver algo no temp, retorna temp
		if (read_bytes <= 0)
			return (temp);
		// * adiciona o \0 depois do que foi lido
		// * pra não ter que limpar o buffer a cada execução
		// * impedindo de dar problema se o read ler menos que buffer_size
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
	while (temp[i] && temp[i] != '\n');
		i++;
	// * se achar um \n, o next_line_start é o index seguinte
	// * funciona também pra múltiplos \n seguidos
	if (temp[i] == '\n')
		*next_line_start = i + 1;
	else // * se não achar um \n, leu o temp todo
	{
		*next_line_start = i; // * vai ser usado pra lógica de definir start = 0
		if (i == 0 && temp[i] == '\0')
			return (NULL);
	}
	// * a linha é uma substring do início de temp até o \n ou final do temp
	return (ft_substr(temp, 0, *next_line_start)) // TODO add ft_substr
}

static char	*get_rest(char *temp, int next_line_start)
{
	char	*rest;
	int		len;

	// * se não tiver sido encontrado um \n, start vai ter o comprimento do temp
	len = ft_strlen(temp) - next_line_start; // * e len será 0
	if (len <= 0) // * não sobrou nada pra guardar
	{
		free(temp);
		return (NULL);
	}
	// * cria a substr com o rest, que vai do index start até len caracteres
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