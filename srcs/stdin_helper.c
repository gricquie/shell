#include <shell.h>
#include <stdin_helper.h>
#include <cntrfuncs.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void	llist_cmd_line_insert_after(t_cmd_line *cur,
				    t_cmd_line *new)
{
    new->next = cur->next;
    new->prev = cur;
    cur->next->prev = cur;
    cur->next = new;
}

t_cmd_line    *new_cmd_line(char *header, size_t term_l)
{
    t_cmd_line	*new;

    new = malloc(sizeof(t_cmd_line));
    if (!new)
	return NULL;
    if (header)
    {
        new->header = strdup(header);
	new->header_length = strlen(header);
    }
    else
    {
	new->header = NULL;
	new->length = 0;
    }
    new->max_l = term_l - new->header_length;
    new->line = malloc(new->max_l *sizeof(char));
    new->length = 0;

    new->prev = NULL;
    new->next = NULL;

    return (new);
}

// return nb lines moved
int cmd_line_insert(t_cmd_line *cmd, char c, size_t pos)
{
    char pop = 0;

    if (cmd == NULL)
	return (-1);
    if (pos > cmd->max_l - 1)
	return (-1);

    if (pos > cmd->length)
	pos = cmd->length;
    if (cmd->length == cmd->max_l)
	pop = cmd->line[cmd->length - 1];

    memmove(cmd->line + pos + 1, cmd->line + pos + 1,
	    cmd->length - pos - (pop != 0));
    cmd->line[pos] = c;
    cmd->length += (pop != 0);

    if (!pop)
       return (0);
    if (!cmd->next || cmd->next->header != NULL)
    {
	t_cmd_line  *new = new_cmd_line(NULL,
		cmd->max_l + cmd->header_length);
	llist_cmd_line_insert_after(cmd, new);
    }

    return (1 + cmd_line_insert(cmd->next, pop, 0));
}

int cmd_line_remove(t_cmd_line *cmd, size_t pos)
{
    if (!cmd)
	return (-1);
    if (pos > cmd->length)
	pos = cmd->length;
    
    memmove(cmd->line + pos, cmd->line + pos + 1,
	    cmd->length - pos);
    cmd->length--;

    return 1;
}
