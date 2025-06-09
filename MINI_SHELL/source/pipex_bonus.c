/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:09:15 by gnicolo           #+#    #+#             */
/*   Updated: 2025/06/08 19:44:54 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_sigint;

void	ft_help_mulp_cmd(int p_fd[2], int prev_fd, t_list_1 *cmd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, 0);
		close(prev_fd);
	}
	if (cmd->next)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		close(p_fd[1]);
	}
}

void	ft_help_mulp_cmd2(t_env *start, int index, t_list_1 *cmd)
{
	ft_set_saved_fds(start);
	handle_redirections(start->redirect[index], start, NULL);
	cleanup_heredoc_files(start->redirect);
	exec(cmd, start->env_copy, start);
	close(1);
	exit(1);
}

void	ft_help_mulp_cmd3(int (*p_fd)[2], int flags, int *prev_fd)
{
	if (flags == 0)
	{
		if (pipe(*p_fd) == -1)
		{
			perror("pipe");
			exit(1);
		}
	}
	else
	{
		close((*p_fd)[1]);
		(*prev_fd) = (*p_fd[0]);
	}
}

void	ft_is_multiple_cmd(t_env *start, int index, int prev_fd)
{
	t_list_1	*cmd;
	pid_t		pid;
	int			p_fd[2];

	cmd = start->word;
	while (cmd)
	{
		if (cmd->next)
			ft_help_mulp_cmd3(&p_fd, 0, &prev_fd);
		pid = fork();
		if (pid == -1)
			exit(1);
		else if (pid == 0)
		{
			ft_help_mulp_cmd(p_fd, prev_fd, cmd);
			ft_help_mulp_cmd2(start, index, cmd);
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
			ft_help_mulp_cmd3(&p_fd, 1, &prev_fd);
		cmd = cmd->next;
		index++;
	}
}

int	ft_exec_all(t_env *start)
{
	if (!start->word->arg[0])
		return (0);
	if (!start->word->next)
		return (ft_is_single_cmd(start));
	if (preprocess_all_heredocs(start->redirect, start, 0) == -1)
		return (ft_check_exit_code(start),
			cleanup_heredoc_files(start->redirect), -1);
	ft_is_multiple_cmd(start, 0, -1);
	while (waitpid(0, &start->exit_code, 0) > 0)
		;
	cleanup_heredoc_files(start->redirect);
	return (0);
}
