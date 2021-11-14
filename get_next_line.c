/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 15:51:58 by eestelle          #+#    #+#             */
/*   Updated: 2021/11/14 15:52:00 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	int	ft_init(int fd, t_buff *buff, t_lst **lbegin, t_lst ***lend)
{
	if (fd < 0 || fd >= OPEN_MAX)
		return (1);
	if (BUFFER_SIZE <= 0)
		return (1);
	if (buff->data == NULL)
	{
		buff->data = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		buff->size = 0;
	}
	if (buff->data == NULL)
		return (1);
	*lbegin = NULL;
	*lend = lbegin;
	return (0);
}

static	void	ft_clear(t_buff *buff, t_lst *begin)
{
	if (buff->data != NULL)
	{
		free(buff->data);
		buff->data = NULL;
	}
	buff->size = 0;
	if (begin != NULL)
		ft_lstclear(begin);
}

static	int	ft_check(t_buff *buff, size_t *len)
{
	size_t	i;

	i = 0;
	while (i < buff->size)
	{
		if (buff->data[i] == '\n')
		{
			*len = i + 1;
			return (1);
		}
		i++;
	}
	return (0);
}

static	int	ft_todo(t_buff *buff, t_lst ***end, t_lst *begin)
{
	char	flag;
	size_t	len;

	flag = ft_check(buff, &len);
	if (flag)
		**end = ft_lstnew(&buff->data, len);
	else
		**end = ft_lstnew(&buff->data, buff->size);
	if (**end == NULL)
	{
		ft_lstclear(begin);
		return (-1);
	}
	if (flag)
	{
		buff->size -= len;
		ft_memcpy(buff->data, (**end)->data + len, buff->size);
		return (1);
	}
	*end = &(**end)->next;
	return (0);
}

char	*get_next_line(int fd)
{
	static t_buff	buff = {};
	t_lst			*lst_begin;
	t_lst			**lst_end;

	if (ft_init(fd, &buff, &lst_begin, &lst_end))
		return (NULL);
	if (buff.size != 0)
		if (ft_todo(&buff, &lst_end, lst_begin))
			return (ft_lsttoarr(lst_begin));
	while (1)
	{
		buff.size = read(fd, buff.data, BUFFER_SIZE);
		if (buff.size == (size_t)(-1))
			ft_clear(&buff, lst_begin);
		else if (buff.size == 0)
			ft_clear(&buff, NULL);
		if (buff.size <= 0 || buff.size == (size_t)(-1)
			|| ft_todo(&buff, &lst_end, lst_begin))
			break ;
	}
	return (ft_lsttoarr(lst_begin));
}
