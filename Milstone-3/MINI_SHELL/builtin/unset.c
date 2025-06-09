/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 22:13:53 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/08 19:11:58 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_len_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return (0);
	while (matrix[i])
		i++;
	return (i);
}

int	remove_var(t_env *env, int index)
{
	int		i;
	char	**temp;
	int		j;

	j = 0;
	if (!env || !env->env_copy)
		return (-1);
	if (index == -1)
		return (0);
	i = ft_len_matrix(env->env_copy);
	temp = ft_calloc((i) * sizeof(char *), 1);
	i = 0;
	while (env->env_copy[i])
	{
		if (i != index)
		{
			temp[j] = ft_strdup(env->env_copy[i]);
			j++;
		}
		i++;
	}
	ft_free_matrix(env->env_copy);
	env->env_copy = temp;
	return (0);
}

int	ft_unset(t_env *env, t_list_1 *list)
{
	char	**arg;
	int		index;
	int		i;

	i = 1;
	arg = list->arg;
	while (arg[i])
	{
		if (!arg[i])
			return (1);
		if (is_valid(arg[i]) == -1)
			return (1);
		index = find_var(env, arg[i]);
		if (index != -1)
			remove_var(env, index);
		i++;
	}
	return (0);
}
