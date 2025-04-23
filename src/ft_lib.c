#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "ft_lib.h"

char ft_getchar(int fd)
{
	char c;
	read(fd, &c, 1);
	return(c);
}

void ft_get_terminal_size(int *row, int *col)
{
	struct winsize term_size;

	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &term_size) == -1)
	{
		//set default size
		*row = 24;
		*col = 80;
	}
	else
	{
		*row = term_size.ws_row;
		*col = term_size.ws_col;
	}
}
