#ifndef SHELL_H
# define SHELL_H

# define BIN_STR(s) s, sizeof(s) - 1

#include <unistd.h>

extern char **environ;

extern int  shell_fd;

ssize_t	    readuntilc(int fd, char c, char **line);
ssize_t	    readline(int fd, char **line);
void	    readline_end();	// free remainder of readline static

ssize_t	    readcmd(char **input);
int	    put_c(int c);

int	    stdin_handler();
void	    reset_shell_attr();

#endif
