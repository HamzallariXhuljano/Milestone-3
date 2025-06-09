/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:16:53 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/08 19:45:23 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_help_update_oldpwd(t_env *env, char *pwd)
{
	int		i;
	char	*oldpwd;

	i = 0;
	oldpwd = ft_strjoin("OLDPWD=", pwd);
	if (!oldpwd)
	{
		write(2, "MINISHELL: cd: memory allocation failed\n", 40);
		return ;
	}
	while (env->env_copy[i])
	{
		if (ft_strncmp(env->env_copy[i], "OLDPWD=", 7) == 0)
		{
			free(env->env_copy[i]);
			env->env_copy[i] = oldpwd;
			break ;
		}
		i++;
	}
	if (env->env_copy[i] == NULL)
	{
		add_name_var(&env, "OLDPWD", pwd);
		free(oldpwd);
	}
}

void	update_oldpwd(t_env *env)
{
	int		i;
	char	*pwd;

	i = 0;
	pwd = NULL;
	while (env->env_copy[i])
	{
		if (ft_strncmp(env->env_copy[i], "PWD=", 4) == 0)
		{
			pwd = env->env_copy[i] + 4;
			break ;
		}
		i++;
	}
	if (pwd)
		ft_help_update_oldpwd(env, pwd);
}

void	update_pwd(t_env *env)
{
	int		i;
	char	*newpwd;
	char	*join;

	i = 0;
	newpwd = getcwd(NULL, 0);
	join = ft_strjoin("PWD=", newpwd);
	while (env->env_copy[i])
	{
		if (ft_strncmp(env->env_copy[i], "PWD=", 4) == 0)
		{
			free(env->env_copy[i]);
			env->env_copy[i] = join;
			break ;
		}
		i++;
	}
	if (env->env_copy[i] == NULL)
	{
		add_name_var(&env, "PWD", newpwd);
		free(join);
	}
	free(newpwd);
}

static int	ft_help_cd(char **args, t_env *env, char *home)
{
	if (args[1] == NULL)
	{
		if (home)
		{
			update_oldpwd(env);
			if (chdir(home) != 0)
			{
				ft_printf("MINISHELL: cd: %s: %s\n", home);
				return (free(home), env->exit_code = 1, -1);
			}
			update_pwd(env);
		}
		else
			return (free(home), write(2, "MINISHELL: cd: HOME not set\n", 28),
				env -> exit_code = 1, -1);
	}
	return (free(home), 1);
}

int	ft_cd(char **args, t_env *env)
{
	int		cnt;

	cnt = 0;
	while (args[cnt] && *args[cnt])
		cnt++;
	if (cnt > 2)
		return (write(2, "MINISHELL: cd: too many arguments\n", 34), -1);
	if (args[1] == NULL)
	{
		if (ft_help_cd(args, env, home_path(env)))
			return (-1);
	}
	else if (args[1])
	{
		if (chdir(args[1]) != 0)
			return (write(2, "MINISHELL: cd: directory: not found!\n", 37),
				env->exit_code = 1, -1);
		update_oldpwd(env);
		update_pwd(env);
	}
	return (0);
}
