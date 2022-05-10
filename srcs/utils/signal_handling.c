#include "../../includes/mini_shell.h"

extern t_env_var env;

//	move to a newline rl_on_new_line();

//	clear readline buffer rl_replace_line("", 0);

//	display prompt again	rl_redisplay();

static void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		env.stat_code = 130;
		printf("\n");	
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*
! why this funnction ? 
This function helps to handle signals such as CTRL + C and CONTRL + \
*/

void	handle_signals(void)
{
	signal(SIGQUIT,SIG_IGN);
	signal(SIGINT, handle_signal);
}
