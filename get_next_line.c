/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 15:58:01 by eestelle          #+#    #+#             */
/*   Updated: 2021/10/23 17:28:24 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_check(char *buff, size_t start, size_t finish)
{
	size_t	len;

	len = 0;
	while (start + len < finish && buff[start + len] != '\n')
		len++;
	if (buff[start + len] == '\n')
		return (len + 1);
	else
		return (-1);
}

void	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i < dstsize - 1 && dstsize > 0)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > 0)
		dst[i] = '\0';
}

char	*ft_arrnew(char **arr, size_t size)
{
	*arr = (char *)malloc(sizeof(char) * (size + 1));
	return (*arr);
}

char	*get_next_line(int fd)
{
	static	t_buff	abuff[1024] = {};
	char			*result;
	int				len;
	size_t			alen;
	size_t          count;

	if (fd < 0 || fd > 1024)
		return (NULL);
	alen = BUFFER_SIZE;
	count = 0;
	if (ft_arrnew(&result, alen) == NULL)
		return (NULL);
	if (abuff[fd].buff == NULL)
	{
		if (ft_arrnew(&abuff[fd].buff, BUFFER_SIZE - 1) == NULL)
		{
			free(result);
			return (NULL);
		}
	}
	else
	{
		len = ft_check(abuff[fd].buff, abuff[fd].begin, abuff[fd].end);
		if (len >= 0)
		{
			ft_strlcpy(result, abuff[fd].buff + abuff[fd].begin, len + 1);
			if (abuff[fd].begin + len == abuff[fd].end)
			{
				abuff[fd].begin = 0;
				abuff[fd].end = 0;
				free(abuff[fd].buff);
				abuff[fd].buff = NULL;
			}
			else
				abuff[fd].begin += len;
			return (result);
		}
		else
		{
			ft_strlcpy(result, abuff[fd].buff + abuff[fd].begin, abuff[fd].end + 1);
			count = abuff[fd].end - abuff[fd].begin;
			abuff[fd].begin = 0;
			abuff[fd].end = 0;
		}
	}
	return (ft_read(fd, result, alen, count, &abuff[fd]));
}