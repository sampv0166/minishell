#include "../../includes/mini_shell.h"

extern t_env_var env;

static void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		env.stat_code = 130;
		printf("\n");	
       	//move to a newline 
		rl_on_new_line();
		//clear readline buffer
		rl_replace_line("", 0);
		//display prompt again
		// rl_forced_update_display();
		rl_redisplay();
	}
}

static void	handle_signal1(int sig)
{
	if (sig == SIGQUIT)
	{
		env.stat_code = 131;
		// printf("\n");
       	//move to a newline 
		rl_on_new_line();
		//clear readline buffer
		// rl_replace_line("", 0);
		//display prompt again
		// rl_forced_update_display();
		rl_redisplay();
	}
}
/*
! why this funnction ? 
This function helps to handle signals such as CTRL + C and CONTRL + \
*/

void	handle_signals(void)
{
	signal(SIGQUIT,handle_signal1);
	signal(SIGINT, handle_signal);
}
