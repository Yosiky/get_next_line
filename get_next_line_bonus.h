/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:03:13 by eestelle          #+#    #+#             */
/*   Updated: 2021/11/14 15:52:46 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# ifdef __linux__
#  include <malloc.h>
# else
#  include <stdlib.h>
# endif

# include <limits.h>
# include <stddef.h>
# include <unistd.h>

typedef struct s_buff
{
	char	*data;
	size_t	size;
}	t_buff;

typedef struct s_lst
{
	char			*data;
	size_t			len;
	struct s_lst	*next;
}	t_lst;

char	*get_next_line(int fd);
char	*ft_memcpy(char *s1, char *s2, size_t len);
t_lst	*ft_lstnew(char **buff, size_t len);
void	ft_lstclear(t_lst *lst);
char	*ft_lsttoarr(t_lst *lst);

#endif
