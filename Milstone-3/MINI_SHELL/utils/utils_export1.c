/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:50:24 by xhamzall          #+#    #+#             */
/*   Updated: 2025/05/29 14:53:09 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export(char **env_cpy, t_env *env)
{
	int		i;
	int		j;
	char	**tmp;

	tmp = dup_mtx(env_cpy);
	sort_export(tmp);
	i = -1;
	while (tmp[++i])
	{
		write(1, "declare -x ", 11);
		if (check_equal(tmp[i]) == 0)
		{
			j = 0;
			print_export_equal(tmp, &i, &j);
		}
		else
		{
			write(env -> fd_to_write, tmp[i], ft_strlen(tmp[i]));
			write(1, "\n", 1);
		}
	}
	ft_free_matrix(tmp);
}

void	print_export_equal(char **tmp, int *i, int *j)
{
	while (tmp[(*i)][(*j)] && tmp[(*i)][(*j)] != '=')
		write(1, &tmp[(*i)][(*j)++], 1);
	write(1, "=\"", 2);
	(*j)++;
	while (tmp[(*i)][(*j)])
		write(1, &tmp[(*i)][(*j)++], 1);
	write(1, "\"\n", 2);
}

char	*creat_name_val(char *name, char *val)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(name, "=");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, val);
	if (!result)
		return (free(tmp), NULL);
	free(tmp);
	return (result);
}

int	update_var(t_env *env, char *name, char *val)
{
	int		i;
	char	*val_name;

	if (!env || !name || !val || !env->env_copy)
		return (-1);
	i = find_var(env, name);
	if (i == -1)
		return (-1);
	val_name = creat_name_val(name, val);
	if (!val_name)
		return (-1);
	free(env -> env_copy[i]);
	env->env_copy[i] = val_name;
	return (0);
}

int	add_name(t_env **env, char *name)
{
	size_t	len;
	size_t	i;
	char	**tmp;
	char	*val_name;

	if (!env || !*env || !name)
		return (-1);
	len = 0;
	while ((*env)->env_copy && (*env)->env_copy[len])
		len++;
	tmp = malloc((len + 2) * sizeof(char *));
	if (!tmp)
		return (-1);
	i = -1;
	while (++i < len)
		tmp[i] = ft_strdup((*env)->env_copy[i]);
	val_name = ft_strdup(name);
	if (!val_name)
		return (ft_free_matrix(tmp), -1);
	tmp[len] = val_name;
	tmp[len + 1] = NULL;
	ft_free_env2((*env)->env_copy);
	(*env)->env_copy = dup_mtx(tmp);
	ft_free_matrix(tmp);
	return (0);
}
