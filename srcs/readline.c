#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>
#include <shell.h>

#define	BUFF_SIZE 8

typedef struct	s_buffer
{
    struct s_buffer *next;
    char	    buffer[BUFF_SIZE];
    ssize_t	    size;
    ssize_t	    taken;
    int		    fd;
} t_buffer;

static t_buffer	*buff = NULL;

t_buffer    *get_fd_buffer(int fd)
{
    t_buffer	*cur = buff;

    while (cur && cur->fd != fd)
	cur = cur->next;
    
    if (cur)
	return cur;

    if (!(cur = malloc(sizeof(t_buffer))))
	return NULL;
    cur->next = buff;
    cur->fd = fd;
    cur->size = 0;
    cur->taken = 0;
    buff = cur;
    return cur;
}

void	    readline_end()
{
    t_buffer	*cur = buff;

    while (cur)
    {
	buff = buff->next;
	free(cur);
	cur = buff;
    }
}

ssize_t		readuntilc(int fd, char c, char **line)
{
    char	*res = NULL;
    size_t	res_size = 0;
    t_buffer	*cur = NULL;

    if (!(cur = get_fd_buffer(fd)))
	return -1;

    while (1)
    {
	if (cur->taken >= cur->size)
	{
	    cur->size = read(fd, cur->buffer, sizeof(cur->buffer));
	    if (cur->size < 0)
		return -1;
	    cur->taken = 0;
	}

	if (cur->size == 0)
	{
	    *line = NULL;
	    return 0;
	}

	int c_i = cur->taken;

	while (c_i < cur->size && cur->buffer[c_i] != c)
	    c_i++;
	if (c_i < cur->size)
	    c_i++;

	if (!(res = realloc(res, res_size + c_i - cur->taken + 1)))
	    return -1;
	memcpy(res + res_size, cur->buffer + cur->taken, c_i - cur->taken);
	res_size = res_size + c_i - cur->taken;
	cur->taken = c_i;

	if (cur->buffer[c_i - 1] != c)
	    continue;
	res[res_size] = '\0';
	*line = res;
	return res_size;
    }
}

ssize_t		readline(int fd, char **line)
{
    return readuntilc(fd, '\n', line);
}
