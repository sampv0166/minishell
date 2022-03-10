#include "../../includes/mini_shell.h"

static void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
       	// move to a newline 
		//rl_on_new_line();
		// clear readline buffer
		//rl_replace_line("", 0);
		// display prompt again
		//rl_redisplay();
	}
	exit (1);
}

void	handle_signals(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT,handle_signal);
}
