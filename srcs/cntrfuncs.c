#include <unistd.h>
#include <shell.h>
#include <cntrfuncs.h>
#include <stdio.h>
#include <termios.h>
#include <term.h>
#include <string.h>

void	print_n_char(t_cntr_info *info)
{
    char s[16];
    int	size = snprintf(s, 16, "%d", info->cur_x);
    write(1, s, size);
    info->cur_x += size;
}

void	cntr_eot(t_cntr_info *info)
{
    info->end_signals |= CNTR_EOT_SIGNAL;
}

void	cntr_nl(t_cntr_info *info)
{
    write(1, "\n", 1);
    info->cur_x = 0;
}

void	cntr_uparrow(t_cntr_info *info)
{
    write(1, BIN_STR("^"));
    info->cur_x++;
}

void	cntr_downarrow(t_cntr_info *info)
{
    write(1, BIN_STR("v"));
    info->cur_x++;
}

void	cntr_rightarrow(t_cntr_info *info)
{
    write(1, BIN_STR(">"));
    info->cur_x++;
}

void	cntr_leftarrow(t_cntr_info *info)
{
    write(1, BIN_STR("<"));
    info->cur_x++;
}

void	cntr_clear(t_cntr_info *info)
{
    //clear ctr + l
    (void)info;
}

void	cntr_del(t_cntr_info *info)
{
    // don't work
    // do move left
    // dont remove char
    // must be done in relative pos
    if (info->cur_x == 0)
	return;

    char    *cub = tigetstr("cub");

    tputs(tiparm(cub, 1), 1, put_c);

    info->cur_x--;
}
