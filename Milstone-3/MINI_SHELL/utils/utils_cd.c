/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:13:19 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/04 18:54:41 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*home_path(t_env *env)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (env->env_copy[i])
	{
		if (ft_strncmp(env->env_copy[i], "HOME=", 5) == 0)
		{
			str = ft_strdup(env -> env_copy[i] + 5);
			break ;
		}
		i++;
	}
	if (!str)
		return (NULL);
	return (str);
}
