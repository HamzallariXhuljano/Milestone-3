/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:51:09 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/08 19:14:04 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_close_saved_fds(t_env *start)
{
	close(start->saved_stdin);
	close(start->saved_stdout);
	close(start->saved_stderr);
	close(6);
}

void	ft_close_all(int i)
{
	i = 3;
	while (i < 4097)
		close(i++);
}

void	sigint_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_sigint = 130;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		rl_done = 1;
	}
	if (sig == SIGQUIT)
	{
		g_sigint = 131;
		write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		rl_done = 1;
	}
}

int	ft_check_is_my_bultin(t_list_1 *cmd, t_env *start)
{
	if (!ft_strcmp(cmd->arg[0], "echo"))
		return (ft_echo(cmd->arg), start->exit_code = 0, 1);
	else if (!ft_strcmp(cmd->arg[0], "cd"))
		return (ft_cd(cmd->arg, start), 2);
	else if (!ft_strcmp(cmd->arg[0], "pwd"))
		return (ft_pwd(), start->exit_code = 0, 4);
	else if (!ft_strcmp(cmd->arg[0], "export"))
		return (ft_export(start, cmd), 3);
	else if (!ft_strcmp(cmd->arg[0], "unset"))
		return (ft_unset(start, cmd), start->exit_code = 0, 6);
	else if (!ft_strcmp(cmd->arg[0], "env"))
		return (ft_env(start->env_copy, 1), start->exit_code = 0, 5);
	else if (!ft_strcmp(cmd->arg[0], "exit"))
		return (ft_exit(cmd, start), 7);
	return (0);
}

void	rst_sdfd(int saved_stdin, int saved_stdout, int saved_stderr)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stderr, STDERR_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	close(saved_stderr);
}
