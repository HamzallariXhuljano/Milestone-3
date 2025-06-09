/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exc2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:55:02 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/06 17:21:00 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_forexc(t_env *start, char **env)
{
	if (start)
	{
		ft_free_env(start);
		ft_free_env2(env);
		free(start);
	}
}

int	exec(t_list_1 *cmd, char **env, t_env *start)
{
	char	*path;
	int		i;

	path = ft_get_path(cmd->arg[0], env, -1);
	i = ft_check_is_my_bultin(cmd, start);
	if (i != 0)
		return (ft_free_forexc(start, start->env_copy), free(path), 777);
	if (!path)
	{
		ft_putstr_fd("Minishell: command not found: ", 2);
		ft_putendl_fd(cmd->arg[0], 2);
		start->exit_code = 127;
		return (ft_free_forexc(start, env), 127);
	}
	if (execve(path, cmd->arg, env) == -1)
	{
		ft_putendl_fd(cmd->arg[0], 2);
		return (cleanup_heredoc_files(start->redirect),
			ft_free_forexc(start, env), free(path), 127);
	}
	return (0);
}

int	ft_exec_help(char *path, t_list_1 *cmd, char **env, t_env *start)
{
	if (cmd->arg[0][0] == '\0')
		return (free(path), 0);
	if (fork() == 0)
	{
		ft_close_saved_fds(start);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (execve(path, cmd->arg, env) == -1)
		{
			g_sigint = -1;
			return (ft_putendl_fd(cmd->arg[0], 2), free(path), 127);
		}
	}
	else
		return (wait(&start->exit_code), free(path),
			ft_check_exit_code(start), 0);
	return (-1);
}

int	ft_invalid_fd(t_env *start, t_redirect *redir)
{
	perror(redir->filename);
	rst_sdfd(start->saved_stdin,
		start-> saved_stdout, start-> saved_stderr);
	return (-1);
}

int	exec_2(t_list_1 *cmd, char **env, t_env *start)
{
	char	*path;

	if ((cmd->arg[0][0] == '\0' || cmd->arg[0][0] == '.'
		|| cmd->arg[0][0] == '/') && ft_strlen(cmd->arg[0]) == 1)
		return (0);
	else if (cmd->arg[0][0] == '.' && cmd->arg[0][0] == '/'
			&& ft_strlen(cmd->arg[0]) == 2)
		return (ft_putstr_fd("Minishell: command not found: ", 2),
			ft_putendl_fd(cmd->arg[0], 2), start->exit_code = 127, 127);
	else if (cmd->arg[0][0] == '/' && ft_strlen(cmd->arg[0]) == 1)
		return (ft_putstr_fd("Minishell: command not found: ", 2),
			ft_putendl_fd(cmd->arg[0], 2), start->exit_code = 127, 127);
	else if (cmd->arg[0][0] == '.' && cmd->arg[0][1] == '/'
			&& ft_strlen(cmd->arg[0]) == 2)
		return (ft_putstr_fd("Minishell: command not found: ", 2),
			ft_putendl_fd(cmd->arg[0], 2), start->exit_code = 127, 127);
	if (ft_check_is_my_bultin(cmd, start))
		return (777);
	cmd->arg[0] = ft_clean_word(cmd->arg[0]);
	path = ft_get_path(cmd->arg[0], env, -1);
	if (!path)
		return (ft_putstr_fd("Minishell: command not found: ", 2),
			ft_putendl_fd(cmd->arg[0], 2), start->exit_code = 127, 127);
	return (ft_exec_help(path, cmd, env, start));
}
