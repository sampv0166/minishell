/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_replace_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:30:35 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:30:36 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

void	replace_env(int g_env1, char *var)
{
	free(g_env.env_var[g_env1]);
	g_env.env_var[g_env1] = ft_strdup(var);
}
