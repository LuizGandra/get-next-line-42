/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:58:10 by lcosta-g          #+#    #+#             */
/*   Updated: 2024/11/15 16:03:56 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (unsigned char)c)
		s++;
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*temp;
	size_t	i;
	size_t	j;

	temp = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!temp)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		temp[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		temp[i++] = s2[j++];
	temp[i] = '\0';
	return (temp);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	len_s;
	char			*substr;
	unsigned int	i;

	len_s = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start >= len_s)
		return ((char *)ft_calloc(1, sizeof(char)));
	if ((len_s - start) < len)
		len = len_s - start;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}
