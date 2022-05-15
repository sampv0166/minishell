#include "../../includes/mini_shell.h"

extern t_env_var	g_env;

int	input_to_tokens(char *input)
{
	t_pars_tokens	*pa_tkns;
	char			**tokens;
	// TOKEN SPLIT
	tokens = tokens_split(input);
	if (!tokens)
		return (EXIT_FAILURE);
	// PARCER
	pa_tkns = parser(tokens);
	ft_free_str_array(&tokens);
	// EXPANDER
	expander(pa_tkns);
	//EXECUTOR
	// print_strcut(pa_tkns);
	executor(pa_tkns);
	free_everything(pa_tkns);
	return (g_env.stat_code);
}
