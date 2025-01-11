#include <fcntl.h>
#include <term.h>
#include <termios.h>
#include <unistd.h>
#include <shell.h>
#include <ctype.h>
#include <string.h>
#include <cntrfuncs.h>
#include <stdlib.h>
#include <stdio.h>

struct termios base_shell_attr;

void	reset_shell_attr()
{
    tcsetattr(0, TCSANOW, &base_shell_attr);
}

t_cntrcharfunc cntrfuncs[] =
{
    {"\e", print_n_char},
    {"\e[A", cntr_uparrow},
    {"\e[B", cntr_downarrow},
    {"\e[C", cntr_rightarrow},
    {"\e[D", cntr_leftarrow},
    {"\n", cntr_nl},
    {"\x7F", cntr_del},
    {"\4", cntr_eot},
    {"\12", cntr_clear},
    {NULL, NULL}
};

void	handle_cntrchar(char *c, size_t l, t_cntr_info *info)
{
    int	i = 0;

    while (cntrfuncs[i].seq != NULL &&
	    memcmp(cntrfuncs[i].seq, c, (size_t)l))
	i++;

    if (cntrfuncs[i].func != NULL)
	cntrfuncs[i].func(info);
    else if (cntrfuncs[i].seq == NULL)
    {
	// should be removed in final product
	// all control sequences should be handled

	char	s[16];
	int	size;

	size = snprintf(s, 16, "%d", c[0]);
	memcpy(s + size, " - ", 3);
	memcpy(s + size + 3, c+1, l - 1);
	memcpy(s + size + l + 2, "\n", 1);
	write(1, s, size + l + 3);
    }
}

int	stdin_handler()
{
    if (setupterm(NULL, 0, NULL))
    {
	write(2, BIN_STR("Error setting up termios\n"));
	return -1;
    }

    t_cntr_info	info;
    memset(&info, 0, sizeof(info));

    struct termios attr;
    tcgetattr(0, &attr);
    base_shell_attr = attr;
    attr.c_lflag &= ~ICANON & ~ECHO;
    attr.c_cc[VMIN] = 1;
    attr.c_cc[VTIME] = 1;
    tcsetattr(0, TCSANOW, &attr);

    info.l_term = tigetnum("cols");
    info.h_term = tigetnum("lines");

    printf("%d - %d\n", info.l_term, info.h_term);

    char    c[8];
    ssize_t l;

    char    *ps1 = "$> ";
    char    *ps2 = "> ";

    (void)ps2;

    info.cur_y = 0;
    
    info.n_line = 1;
    if (!(info.cmd_lines = new_cmd_line(ps1, info.l_term)))
	return (-1);

    write(1, info.cmd_lines->header, info.cmd_lines->header_length);
    // set cur as cursor pos OR input index ?

    t_cmd_line	*cur = info.cmd_lines;
    while (!info.end_signals && (l = read(0, &c, 8)) > 0)
    {
	if (iscntrl(c[0]))
	    handle_cntrchar(c, l, &info);
	else
	{
	    int	nl;

	    if ((nl = cmd_line_insert(cur, *c,
			info.cur_x)) > 0)
	    {
		//reprint next lines (nl)
	    }

	    info.cur_x++;
	}
    }

    return 0;
}
