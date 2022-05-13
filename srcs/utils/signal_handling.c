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
       	//move to a newline 
		rl_on_new_line();
		//clear readline buffer
		rl_replace_line("", 0);
		//display prompt again
		//rl_forced_update_display();
		//printf("\b\b");
		rl_redisplay();
	}
}

// static void	handle_signal1(int sig)
// {
// 	if (sig == SIGQUIT)
// 	{
// 		env.stat_code = 131;
// 		// printf("\n");
//        	//move to a newline 
// 		rl_on_new_line();
// 		//clear readline buffer
// 		// rl_replace_line("", 0);
// 		//display prompt again
// 		// rl_forced_update_display();
// 		rl_redisplay();
// 	}
// }

void	signal_handler(int signum, siginfo_t *siginfo, void *context)
{
	int			trig;

	trig = 0;
	(void)context;
	if (signum == SIGINT)
	{
		if (env.s_pid)
		{
			printf("\b\b\n");
			env.stat_code = 130;
		}
		else
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			env.stat_code = 1;
		}
	}
	else if (signum == SIGQUIT)
	{
		if (env.s_pid)
		{
			ft_putendl_fd("\b\bQuit", STDOUT_FILENO);
			env.stat_code = 131;
		}
		else
		{
			rl_on_new_line();
			rl_redisplay();
			write(1, "  \b\b", 4);
		}
	}
}

/*
! why this funnction ? 
This function helps to handle signals such as CTRL + C and CONTRL + \
*/

// void	handle_signals(void)
// {
// 	signal(SIGQUIT,handle_signal);
// 	signal(SIGINT, handle_signal);
// }

void	handle_signals(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &signal_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}