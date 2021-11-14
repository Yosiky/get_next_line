/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 15:52:28 by eestelle          #+#    #+#             */
/*   Updated: 2021/11/14 15:52:29 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_memcpy(char *s1, char *s2, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*(s1++) = *(s2++);
		i++;
	}
	return (s1);
}

t_lst	*ft_lstnew(char **buff, size_t len)
{
	t_lst	*elem;

	elem = (t_lst *)malloc(sizeof(t_lst));
	if (elem == NULL)
		return (NULL);
	elem->data = *buff;
	*buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (*buff == NULL)
	{
		free(elem->data);
		free(elem);
		return (NULL);
	}
	elem->len = len;
	elem->next = NULL;
	return (elem);
}

void	ft_lstclear(t_lst *lst)
{
	t_lst	*iter;

	while (lst != NULL)
	{
		free(lst->data);
		iter = lst;
		lst = lst->next;
		free(iter);
	}
}

static	size_t	ft_lstlen(t_lst *lst)
{
	size_t	len;

	len = 0;
	while (lst != NULL)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

char	*ft_lsttoarr(t_lst *lst)
{
	char	*res;
	char	*iter;
	size_t	count;
	t_lst	*start;

	res = NULL;
	start = lst;
	count = ft_lstlen(lst);
	if (count != 0)
	{
		res = (char *)malloc(sizeof(char) * (BUFFER_SIZE * count + 1));
		if (res != NULL)
		{
			iter = res;
			while (lst != NULL)
			{
				iter = ft_memcpy(iter, lst->data, lst->len);
				lst = lst->next;
			}
			*iter = '\0';
		}
	}
	ft_lstclear(start);
	return (res);
}
