#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <term.h>
#include <termios.h>
#include <signal.h>
#include <shell.h>

extern char **environ;
int	    shell_fd = 0;

// whitespaces => blanks tabs
// control => & && ( ) ; ;; | || nl
// redirection => < > >| << >> <& >& <<- <>

int	put_c(int c)
{
    return write(1, &c, 1);
}

void	cleanup()
{
    readline_end();
    if (shell_fd != 0)
	close(shell_fd);
    else
    {
	tputs(tigetstr("sgr0"), 1, &put_c);
	reset_shell_attr();
    }
}

void	INT_handler(int sig)
{
    (void)sig;
    cleanup();
    write(2, BIN_STR("SIGINT received\n"));
    exit(0);
}

void	setup_sigcatch(void)
{
    struct sigaction	act;

    act.sa_handler = INT_handler;
    sigemptyset(&act.sa_mask);
    
    sigaction(SIGINT, &act, NULL);

}

int	main(int argc, char **argv)
{
    // init
	// set up env
    if (argc > 1)
    {
	int i = 1;
	// handles options + set i
	
	if (i < argc)
	{
	    if ((shell_fd = open(argv[i], O_RDONLY)) < 0)
	    {
		write(2, BIN_STR("Cannot open file: "));
		write(2, argv[i], strlen(argv[i]));
		write(2, "\n", 1);
		return -1;
	    }
	}
    }

    setup_sigcatch();

    if (shell_fd == 0)
    {
	if (stdin_handler() < 0)
	    return -1;
    }

    // TODO file handling
    /*
    char    *line;
    ssize_t s;
    while ((s = readline(fd, &line)) > 0)
    {
	write(fd, line, s);
    }
    */

    cleanup();
}
