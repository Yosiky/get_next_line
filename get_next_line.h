#ifndef GET_NEXT_LINE_H

# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifdef __linux__
#  include <malloc.h>
# else
#  include <stdlib.h>
# endif

typedef struct s_buff
{
	char	buff[BUFFER_SIZE];
	size_t	begin;
	size_t	end;
}	t_buff;

typedef struct s_lst
{
	char			data[BUFFER_SIZE];
	size_t			len;
	struct s_lst	*next;
}	t_lst;

char	*get_next_line(int fd);

#endif
