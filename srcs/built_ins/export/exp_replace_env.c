#include "../../../includes/mini_shell.h"

extern t_env_var	env;

void	replace_env(int g_env, char *var)
{
	free(env.env_var[g_env]);
	env.env_var[g_env] = ft_strdup(var);
}
