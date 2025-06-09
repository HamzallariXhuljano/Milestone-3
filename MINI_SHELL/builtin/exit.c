/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 20:47:05 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/08 18:53:44 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_exit(char *str)
{
	int		i;
	long	num;

	if (!str)
		return (-1);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (-1);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		i++;
	}
	num = ft_atoi(str);
	if (num < INT_MIN || num > INT_MAX)
		return (-1);
	return (0);
}

static void	ft_freee(t_env *env)
{
	ft_close_saved_fds(env);
	ft_free_env2(env->env_copy);
	ft_free_env(env);
	free(env);
	close(0);
	close(1);
	close(2);
}

void	exit_with_error(int error_code, t_env *env)
{
	if (error_code == 2)
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		error_code = 2;
	}
	else if (error_code == 1)
	{
		env -> exit_code = 1;
		return (ft_putstr_fd("*****minishell: exit: too many arguments\n", 2));
	}
	else if (error_code > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		error_code = 1;
	}
	ft_freee(env);
	if (error_code == 0)
		exit(EXIT_SUCCESS);
	else if (error_code == 1)
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	else
		exit(error_code);
}

void	ft_exit(t_list_1 *cmd, t_env *env)
{
	int	cnt_arg;
	int	is_valid;
	int	i;

	cnt_arg = matrix_len(cmd -> arg);
	if (cnt_arg >= 2)
	{
		is_valid = valid_exit(cmd->arg[1]);
		if (is_valid == -1)
			exit_with_error(2, env);
	}
	if (cnt_arg > 2)
		return (exit_with_error(1, env));
	if (cnt_arg == 2)
		env->exit_code = ft_atoi(cmd->arg[1]) % 256;
	else
		env->exit_code = 0;
	i = env->exit_code;
	ft_freee(env);
	exit(i);
}
