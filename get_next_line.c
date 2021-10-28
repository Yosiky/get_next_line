#include "get_next_line.h"

typedef unsigned long long	t_ull;


char	*ft_memcpy(char *dest, const char *src, size_t n)
{
	while (n--)
		*(dest++) = *(src++);
	return (dest);
}

/*
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
*/
/*
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
*/
/*
size_t	ft_check(char *arr, size_t start, size_t end)
{
	size_t	i;

	i = 0;
	while (i + start < end && arr[start + i] != '\n')
		i++;
	if (arr[start + i] == '\n')
		return (i + 1);
	else
		return (-1);
}
*/
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

/*
char	*get_next_line(int fd)
{
	static t_buff   st_buff;
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
		st_buff.end = 0;
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
*/



/*
size_t	ft_check_buff(t_lst **lend, char *buff, size_t *len, size_t *ret)
{
	size_t	i;
	char	flag;

	flag = 0;
	i = 0;
	while (i < *len && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
	{
		i++;
		flag = 1;
	}
	if (i > 0)
	{
		*lend = ft_lstnew(buff, i);
		if (*lend == NULL)
			return (-1);
		lend = &(*lend)->next;
		ft_memcpy(buff, buff + i, *len - i);
		*len -= i;
		*ret = i;
	}
	return (0);
}
*/

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

size_t  ft_read(int fd, t_lst **lend, char *buff, size_t *end)
{
	size_t  len;

	while (1)
	{
		*end = read(fd, buff, BUFFER_SIZE);
		if (*end == 0)
			return (0);
		else if (*end == (size_t)-1)
			return (1);
		ft_check(buff, *end, &len);
		*lend = ft_lstnew(buff, len);
		if (*lend == NULL)
			return (1);
		if (len != *end)
		{
			*end -= len;
			ft_memcpy(buff, buff + len, *end);
			break;
		}
	}
	return (0);
}
/*
char	*get_next_line(int fd) {
	static char buff[BUFFER_SIZE + 1] = {};
	static size_t end = 0;
	t_lst *lst_begin;
	t_lst **lst_end;
	size_t len;

	lst_begin = NULL;
	lst_end = &lst_begin;
	ft_check(buff, end, &len);
	if (len)
	{
		lst_begin = ft_lstnew(buff, len);
		if (lst_begin == NULL)
			return (NULL);
		lst_end = &lst_begin->next;
	}
	end -= len;
	ft_memcpy(buff, buff + len, end);
	if (lst_begin == NULL || lst_begin->data[lst_begin->len] != '\n')
		if (ft_read(fd, lst_end, buff, &end))
			ft_lstclear(lst_begin);
	return (ft_lsttoarr(lst_begin));

//
	if (ft_check_buff(lst_end, buff, &end, &len) == (size_t)-1) {
		return (NULL);
	} else if (!len)
	{
		while (1)
		{
			end = read(fd, buff, BUFFER_SIZE);
			if (ft_check_buff(lst_end, buff, &end, &len) == (size_t)-1)
			{
				ft_lstclear(lst_begin);
				return (NULL);
			}
			else if (!len)
				break;
		}
	}
	return (ft_lsttoarr(lst_begin));
 //
}
*/
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

char    *get_next_line(int fd)
{
	static char     buff[BUFFER_SIZE + 1] = {};
	static size_t   end = 0;
	t_lst           *lst_begin;
	t_lst			**lst_end;

	lst_begin = NULL;
	lst_end = &lst_begin;
	if (end != 0)
		if (ft_todo(&lst_end, buff, &end, NULL))
			return (ft_lsttoarr(lst_begin));
	while (1)
	{
		end = read(fd, buff, BUFFER_SIZE);
		if (end == (size_t)-1)
			ft_lstclear(lst_begin);
		if (end <= 0)
			break;
		if (ft_todo(&lst_end, buff, &end, lst_begin))
			break;
	}
	return (ft_lsttoarr(lst_begin));
}
