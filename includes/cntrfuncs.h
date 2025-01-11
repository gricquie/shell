#ifndef CNTRFUNCS_H
# define CNTRFUNC_H

# include <stdin_helper.h>

# define CNTR_ETX_SIGNAL 0x1
# define CNTR_EOT_SIGNAL 0x2
# define CNTR_ETB_SIGNAL 0x4
# define CNTR_EM_SIGNAL  0x8

typedef struct	cntr_info
{
    unsigned int    l_term;
    unsigned int    h_term;

    unsigned int    cur_x;
    unsigned int    cur_y; // 0 is starting line

    t_cmd_line	    *cmd_lines;
    size_t	    n_line;

    unsigned char   end_signals;
}   t_cntr_info;

typedef struct	cntrcharfunc
{
    char    *seq;
    void    (*func)(t_cntr_info *);
}   t_cntrcharfunc;

void	print_n_char(t_cntr_info *info);

void	cntr_nl(t_cntr_info *info);
void	cntr_uparrow(t_cntr_info *info);
void	cntr_downarrow(t_cntr_info *info);
void	cntr_rightarrow(t_cntr_info *info);
void	cntr_leftarrow(t_cntr_info *info);
void	cntr_del(t_cntr_info* info);
void	cntr_eot(t_cntr_info* info);
void	cntr_clear(t_cntr_info *info);

#endif
