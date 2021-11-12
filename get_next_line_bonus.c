#include "get_next_line.h"

typedef unsigned long long	t_ull;


char	*ft_memcpy(char *dest, const char *src, size_t n)
{
	while (n--)
		*(dest++) = *(src++);
	return (dest);
}

t_lst	*ft_lstnew(char *src, size_t len)
{
	t_lst	*res;

	res = (t_lst *)malloc(sizeof(t_lst) * 1);
	if (res == NULL)
		return (NULL);
	ft_memcpy(res->data, src, len);
	res->len = len;
	res->next = NULL;
	return (res);
}

void	*ft_lstclear(t_lst *lst)
{
	t_lst *iter;

	while (lst != NULL)
	{
		iter = lst;
		lst = lst->next;
		free(iter);
	}
	return (NULL);
}

size_t	ft_strlen(t_lst *lst)
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
	size_t	count;
	char	*result;
	char	*iter;
	t_lst   *start;

	if (lst == NULL)
		return (NULL);
	start = lst;
	count = ft_strlen(lst);
	if (count == 0)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (count * BUFFER_SIZE + 1));
	if (result == NULL)
		return (NULL);
	iter = result;
	while (lst != NULL)
	{
		iter = ft_memcpy(iter, lst->data, lst->len);
		lst = lst->next;
	}
	*iter = '\0';
	ft_lstclear(start);
	return (result);
}

int ft_check(char *buff, size_t len, size_t *out) {
	size_t  i;
	char    flag;

	i = 0;
	flag = 0;
	if (len > 0) {
		while (i < len && buff[i] != '\n')
			i++;
		if (buff[i] == '\n') {
			i++;
			flag = 1;
		}
	}
	*out = i;
	return (flag);
}

int		ft_todo(t_lst ***iter, char *src, size_t *len, t_lst *begin)
{
	size_t	l;
	char	flag;

	flag = ft_check(src, *len, &l);
	if (flag)
		**iter = ft_lstnew(src, l);
	else
		**iter = ft_lstnew(src, *len);
	if (**iter == NULL)
	{
		ft_lstclear(begin);
		return (-1);
	}
	if (flag)
	{
		*len -= l;
		ft_memcpy(src, src + l, *len);
		return (1);
	}
	*iter = &(**iter)->next;
	return (0);
}

void	*ft_initial(char **buff, t_lst **begin, t_lst ***end, size_t *start)
{
	if (*buff == NULL)
		*buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 2));
	if (*buff == NULL)
		return (NULL);
	*begin = NULL;
	*end = begin;
	*start = 0;
	return (*buff);
}

char    *get_next_line(int fd)
{
	static char     *buff[1024] = {};
	static size_t   end[1024] = {};
	t_lst           *lst_begin;
	t_lst			**lst_end;

	if (fd < 0 || fd > 1024 || ft_initial(&buff[fd], &lst_begin, &lst_end, &end[fd]) == NULL)
		return (NULL);
	if (end[fd] != 0)
		if (ft_todo(&lst_end, buff[fd], &end[fd], NULL))
			return (ft_lsttoarr(lst_begin));
	while (1)
	{
		end[fd] = read(fd, buff[fd], BUFFER_SIZE);
		if (end[fd] == (size_t)-1)
			ft_lstclear(lst_begin);
		if (end[fd] == 0 || end[fd] == (size_t)-1)
		{
			free(buff[fd]);
			break;
		}
		if (ft_todo(&lst_end, buff[fd], &end[fd], lst_begin))
			break;
	}
	return (ft_lsttoarr(lst_begin));
}
