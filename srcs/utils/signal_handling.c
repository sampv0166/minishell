#include "../../includes/mini_shell.h"

extern t_env_var	env;

//	move to a newline rl_on_new_line();

//	clear readline buffer rl_replace_line("", 0);

//	display prompt again	rl_redisplay();

static void	control_c(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	env.stat_code = 1;
}

static void	print_nothing(void)
{
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \b\b", 4);
}

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
			control_c();
	}
	else if (signum == SIGQUIT)
	{
		if (env.s_pid)
		{
			ft_putendl_fd("\b\bQuit", STDOUT_FILENO);
			env.stat_code = 1;
		}
		else
			print_nothing();
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
