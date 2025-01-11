#ifndef STDIN_HELPER_H
# define STDIN_HELPER_H

typedef struct	cmd_line
{
    char    *line;
    size_t  max_l;
    size_t  length;
    char    *header;
    size_t  header_length;

    struct cmd_line *prev;
    struct cmd_line *next;
}   t_cmd_line;

t_cmd_line  *new_cmd_line(char *header, size_t term_l);
int cmd_line_insert(t_cmd_line *cmd, char c, size_t pos);
int cmd_line_remove(t_cmd_line *cmd, size_t pos);

#endif
