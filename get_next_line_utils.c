/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 10:41:02 by marvin            #+#    #+#             */
/*   Updated: 2024/11/10 12:40:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	m_size;
	size_t	i;
	void	*temp;

	if (!nmemb || !size)
		return (malloc(0));
	m_size = nmemb * size;
	if (m_size / size != nmemb)
		return (NULL);
	temp = malloc(m_size);
	if (!temp)
		return (NULL);
	i = 0;
	while (i < m_size)
		((unsigned char *)temp)[i++] = 0;
	return (temp);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = 0;
	while (dst[dst_len])
		dst_len++;
	src_len = 0;
	while (src[src_len])
		src_len++;
	if (size <= dst_len)
		return (size + src_len);
	i = 0;
	while (src[i] && i < (size - dst_len - 1))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

t_line	*ft_linenew(void	*content)
{
	t_line	*line;

	line = (t_line *)ft_calloc(1, sizeof(t_line));
	if (!line)
		return (NULL);
	line->c = *(char *)content;
	line->next = NULL;
	return (line);
}

void	ft_lineadd_back(t_line **line, t_line *new)
{
	t_line	*temp;

	if (!line || !new)
		return ;
	if (!*line)
		*line = new;
	else
	{
		temp = *line;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}
