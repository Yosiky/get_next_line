/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 17:00:03 by eestelle          #+#    #+#             */
/*   Updated: 2021/10/23 17:19:09 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *ft_realloc(char **dst, size_t *len)
{
	char    *res;

	res = (char *)malloc(sizeof(char) * (*len + BUFFER_SIZE + 1));
	ft_strlcpy(res, *dst, *len + 1);
	*len += BUFFER_SIZE;
	free(*dst);
	*dst = res;
	return (res);
}

char	*ft_read(int fd, char *res, size_t len, size_t count, t_buff *rm)
{
	char	buff[BUFFER_SIZE];
	int		l;
	int		check;

	while (1)
	{
		l = read(fd, buff, BUFFER_SIZE);
		if (l <= 0)
		{
			free(rm->buff);
			free(res);
			rm->buff = NULL;
			return (NULL);
		}
		else
		{
			check = ft_check(buff, 0, l);
			if (check >= 0)
			{
				if (l == 0 && count == 0)
				{
					free(rm->buff);
					free(res);
					rm->buff = NULL;
					return (NULL);
				}
				if (count + check >= len)
					if (ft_realloc(&res, &len) == NULL)
					{
						free(rm->buff);
						rm->buff = NULL;
						return (NULL);
					}
				ft_strlcpy(res + count, buff, check + 1);
				if (check < l)
				{
					ft_strlcpy(rm->buff, buff + check, l - check + 1);
					rm->begin = 0;
					rm->end = l - check;
				}
				else
				{
					free(rm->buff);
					rm->buff = NULL;
				}
				return (res);
			}
			else
			{
				if (count + l >= len)
					if (ft_realloc(&res, &len) == NULL)
					{
						free(rm->buff);
						rm->buff = NULL;
						return (NULL);
					}
				ft_strlcpy(res + count, buff, l + 1);
				count += l;
			}
			if (l == 0)
				break;
		}
	}
	if (rm->buff != NULL)
	{
		free(rm->buff);
		rm->buff = NULL;
	}
	return (res);
}