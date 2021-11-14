#include "get_next_line_bonus.h"

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

int	ft_init(int fd, t_buff *buff, t_lst **lbegin, t_lst ***lend)
{
	if (fd < 0 || fd > OPEN_MAX)
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

size_t	ft_lstlen(t_lst *lst)
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

void	ft_clear(t_buff *buff, t_lst *begin)
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

int	ft_check(t_buff *buff, size_t *len)
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

int	ft_todo(t_buff *buff, t_lst ***end, t_lst *begin)
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
	static	t_buff	buff[OPEN_MAX] = {};
	t_lst			*lst_begin;
	t_lst			**lst_end;

	if (ft_init(fd, &buff[fd], &lst_begin, &lst_end))
		return (NULL);
	if (buff[fd].size != 0)
		if (ft_todo(&buff[fd], &lst_end, lst_begin))
			return (ft_lsttoarr(lst_begin));
	while (1)
	{
		buff[fd].size = read(fd, buff[fd].data, BUFFER_SIZE);
		if (buff[fd].size == (size_t)-1)
			ft_clear(&buff[fd], lst_begin);
		else if (buff[fd].size == 0)
			ft_clear(&buff[fd], NULL);
		if (buff[fd].size <= 0 || buff[fd].size == (size_t)-1
			|| ft_todo(&buff[fd], &lst_end, lst_begin))
			break;
	}
	return (ft_lsttoarr(lst_begin));
}
