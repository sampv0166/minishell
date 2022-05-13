#include "../includes/mini_shell.h"

t_env_var env;

static int get_input()
{
	char *input;
	while (1)
	{
		ft_putstr_fd("back here", 2);
		env.s_pid = 0;
		env.here_doc = 0;
		input = readline("\r[=========]");
		if (input == NULL)
		{
			free_env();
			ft_putstr_fd("exiting", 2);
			return (0);
		}
		if (ft_strlen(input) > 0)
			add_history(input);
		else
			continue;
		input_to_tokens(input);
		if (env.trigger)
		{
			free(input);
			exit(env.stat_code);
		}
	}
	
	return (0);
}

int main(int ac, char **argv, char **envp)
{
	(void)ac;
	(void)argv;
	handle_signals();
	if (init_env_vars(envp))
		free_env();
	return (get_input());
}