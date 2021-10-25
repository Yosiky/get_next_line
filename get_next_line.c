#include "get_next_line.h"

typedef unsigned long long	t_ull;

static	char    *ft_fast_completion(char *bdest, char *bsrc, size_t n)
{
	t_ull	*ptr_dest;
	t_ull	*ptr_src;
	size_t	len;

	ptr_dest = (t_ull *)bdest;
	ptr_src = (t_ull *)bsrc;
	len = n / 8;
	while (len--)
		*(ptr_dest++) = *(ptr_src++);
	bdest = (char *)ptr_dest;
	bsrc = (char *)ptr_src;
	len = n % 8;
	while (len--)
		*(bdest++) = *(bsrc++);
	return (bdest);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*bptr_dest;
	char	*bptr_src;

	if (dest == src || n == 0)
		return (dest);
	bptr_dest = (char *)dest;
	bptr_src = (char *)src;
	while ((size_t)bptr_dest % 8 && n)
	{
		*(bptr_dest++) = *(bptr_src++);
		n--;
	}
	if (n == 0)
		return (bptr_dest);
	return (ft_fast_completion(bptr_dest, bptr_src, n));
}


char	*ft_arrnew(char *src, size_t len)
{
	char	*dst;

	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (dst == NULL)
		return (NULL);
	ft_memcpy(dst, src, len);
	dst[len] = '\0';
	return (dst);
}

size_t	ft_check(char *arr, size_t start, size_t end)
{
	size_t	i;

	i = 0;
	while (i + start < end && arr[start + i] != '\n')
		i++;
	printf("i = %ld\n", i);
	if (arr[start + i] == '\n')
		return (i + 1);
	else
		return (-1);
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

char	*get_next_line(int fd)
{
	static	t_buff	st_buff = {};
	t_lst			*lst_begin;
	t_lst			**lst_end;
	char			buff[BUFFER_SIZE];
	size_t			len;
	int			buff_len;

	len = 0;
	lst_begin = NULL;
	lst_end = &lst_begin;
	if (st_buff.end != st_buff.begin && st_buff.end)
	{
		len = ft_check(st_buff.buff, st_buff.begin, st_buff.end);
		if (len != (size_t)-1)
		{
			lst_begin = ft_lstnew(st_buff.buff + st_buff.begin, len);
			st_buff.begin += len;
			if (st_buff.begin == st_buff.end)
				st_buff.end = 0;
			return (ft_lsttoarr(lst_begin));
		}
		len = st_buff.end - st_buff.begin;
		lst_begin = ft_lstnew(st_buff.buff + st_buff.begin, len);
		if (lst_begin != NULL)
			lst_end = &lst_begin->next;
		else
			return (NULL);
	}
	while (1)
	{
		buff_len = read(fd, buff, BUFFER_SIZE);
		if (buff_len <= 0)
			break;
		len = ft_check(buff, 0, buff_len);
		if (len == (size_t)-1)
		{
			*lst_end = ft_lstnew(buff, buff_len);
			if (*lst_end == NULL)
				return (ft_lstclear(lst_begin));
			else
				lst_end = &((*lst_end)->next);
		}
		else
		{
			*lst_end = ft_lstnew(buff, len);
			st_buff.begin = 0;
			st_buff.end = buff_len - len;
			ft_memcpy(st_buff.buff, buff + len, st_buff.end);
			break;
		}
	}
	return (ft_lsttoarr(lst_begin));
}
