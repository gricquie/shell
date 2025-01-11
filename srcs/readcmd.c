#include <string.h>
#include <stdlib.h>
#include <unistd.h>

size_t	    readcmd(char **input)
{
    char    buffer[256];
    char    *res = NULL;
    ssize_t b_size;
    size_t  res_size = 0;
    int	    cont = 1;
    char    quotes[256];
    int	    q_count = 0;

    char    accept[] = "\'\"()"; // add backslash

    *input = NULL;
    while (cont && (b_size = read(0, buffer, sizeof(buffer))))
    {
	if (b_size < 0)
	{
	    free(*input);
	    return -1;
	}

	res_size += b_size;
	res = realloc(res, res_size + 1);
	if (res == NULL)
	    return -1;
	res = strncat(res, buffer, b_size);

	char	*tmp = res + res_size - b_size - 1;
	while ((tmp = strpbrk(tmp + 1, accept)))
	{
	    if ((q_count > 0 && quotes[q_count - 1] == *tmp && *tmp != '(')
		    || (*tmp == ')' && quotes[q_count - 1] == '('))
		q_count--;
	    else
	    {
		quotes[q_count] = *tmp;
		q_count++;
	    }
	}

	if (buffer[b_size - 1] == '\n')
	{
	    if (b_size >= 2 && buffer[b_size - 2] == '\\')
	    {
		res[res_size - 2] = '\0';
		res_size -= 2;
		cont = 1;
	    }
	    else if (q_count == 0)
	    {
		res[res_size - 1] = '\0';
		res_size--;
	        cont = 0;
	    }
	}

	if (q_count > 0)
	    cont = 1;
    }

    *input = res;
    return res_size;
}
