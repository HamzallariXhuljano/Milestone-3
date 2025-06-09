/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:59:55 by xhamzall          #+#    #+#             */
/*   Updated: 2025/05/29 15:31:13 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_var(t_env *env, char *name)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	if (!env || !name || !env -> env_copy)
		return (-1);
	while (name[len] && name[len] != '=')
		len++;
	while (env->env_copy[++i])
	{
		if (check_equal(name) == 0)
		{
			if (ft_strncmp(env->env_copy[i], name, len) == 0 && \
				env->env_copy[i][len] == '=')
				return (i);
		}
		else
		{
			if (ft_strncmp(env->env_copy[i], name, len) == 0 && \
				(env->env_copy[i][len] == '\0' || env->env_copy[i][len] == '='))
				return (i);
		}
	}
	return (-1);
}
