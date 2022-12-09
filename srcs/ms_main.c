#include "../includes/minishell.h"

void    display_prompt()
{
	static int	first_time = 1;
	const char	*CLEAR_SCREEN_ANSI;

	CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
	if (first_time)
		write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
	first_time = 0;
}

int main(void)
{
	while (1)
	{
		display_prompt();
	}
}