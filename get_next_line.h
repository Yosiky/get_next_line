/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:03:13 by eestelle          #+#    #+#             */
/*   Updated: 2021/10/23 16:07:59 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# ifdef __linux__
#  include <malloc.h>
# else
#  include <stdlib.h>
# endif

# include <stddef.h>
# include <unistd.h>

typedef	struct	s_buff
{
	char	*buff;
	size_t	begin;
	size_t	end; 
}	t_buff;

char    *get_next_line(int fd);
char	*ft_arrnew(char **arr, size_t size);
void	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int 	ft_check(char *buff, size_t start, size_t finish);
char	*ft_read(int fd, char *res, size_t len, size_t count, t_buff *rm);

#endif
