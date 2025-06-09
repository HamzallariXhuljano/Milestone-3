/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:24:46 by gnicolo           #+#    #+#             */
/*   Updated: 2025/06/08 19:45:13 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_name_var(t_env **env, char *name, char *val)
{
	size_t	len;
	size_t	i;
	char	**tmp;
	char	*val_name;

	if (!env || !*env || !name)
		return (-1);
	len = matrix_len((*env)->env_copy);
	tmp = malloc((len + 2) * sizeof(char *));
	if (!tmp)
		return (-1);
	i = -1;
	while (++i < len)
		tmp[i] = ft_strdup((*env)->env_copy[i]);
	if (val)
		val_name = creat_name_val(name, val);
	else
		val_name = ft_strdup(name);
	if (!val_name)
		return (ft_free_matrix(tmp), -1);
	tmp[len] = val_name;
	tmp[len + 1] = NULL;
	ft_free_env2((*env)->env_copy);
	(*env)->env_copy = dup_mtx(tmp);
	return (ft_free_matrix(tmp), 0);
}

int	ft_export(t_env *env, t_list_1 *list)
{
	char	**arg;
	int		i;

	if (!env || !list || !list->arg)
		return (print_export(env-> env_copy, env), 0);
	if (list->arg[1] == NULL)
		return (print_export(env-> env_copy, env), 0);
	arg = list ->arg;
	i = 1;
	while (arg[i])
	{
		if (is_valid(arg[i]) == -1)
		{
			env->exit_code = 1;
			export_print_errors(arg, &i);
			continue ;
		}
		helper_export(arg, env, i);
		i++ ;
	}
	return (0);
}

void	export_print_errors(char **arg, int *i)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(arg[(*i)], 2);
	ft_putstr_fd("' not a valid identifier\n", 2);
	(*i)++;
}

void	helper_export(char **arg, t_env *env, int i)
{
	char	*name;
	char	*value;
	int		index;

	if (check_equal(arg[i]) == 0)
	{
		name = get_name(arg[i]);
		value = get_value(arg[i]);
		index = find_var(env, name);
		if (index != -1)
			update_var(env, name, value);
		else
			add_name_var(&env, name, value);
		free(name);
		free(value);
	}
	else
	{
		index = find_var(env, arg[i]);
		if (index == -1)
			add_name(&env, arg[i]);
	}
}

int	matrix_len(char **mtx)
{
	int	len;

	len = 0;
	while (mtx && mtx[len])
		len++;
	return (len);
}
