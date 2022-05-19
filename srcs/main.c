#include "../includes/mini_shell.h"

t_env_var		g_env;

static void	exit_program(char *input)
{
	free(input);
	free_env();
	ft_putendl_fd("exiting", 2);
	exit(g_env.stat_code);
}

static int	get_input(void)
{
	char	*input;

	input = NULL;
	while (1)
	{
		g_env.s_pid = 0;
		g_env.here_doc = 0;
		input = readline("\001\033[1m\x1B[31m\002MS SHELL======> \001\033[0m\x1B[37m\002");
		if (input == NULL)
		{
			free_env();
			ft_putendl_fd("exiting", 2);
			exit (g_env.stat_code);
		}
		if (ft_strlen(input) > 0)
			add_history(input);
		else
			continue ;
		input_to_tokens(input);
		if (g_env.trigger)
			exit_program(input);
	}	
	return (g_env.stat_code);
}

int	main(int ac, char **argv, char **envp)
{
	(void)ac;
	(void)argv;
	handle_signals();
	if (init_env_vars(envp))
		free_env();
	return (get_input());
}
