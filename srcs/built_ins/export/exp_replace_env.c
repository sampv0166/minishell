#include "../../../includes/mini_shell.h"

void	replace_env(int g_env1, char *var)
{
	free(g_env.env_var[g_env1]);
	g_env.env_var[g_env1] = ft_strdup(var);
}
