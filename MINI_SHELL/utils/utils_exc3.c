/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exc3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnicolo <gnicolo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:56:23 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/08 17:01:48 by gnicolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_last_heredoc(t_env *start, t_redirect *redir,
		int fd, char *last_heredoc_tmp)
{
	signal(SIGINT, sigint_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
	if (last_heredoc_tmp)
	{
		fd = open(last_heredoc_tmp, O_RDONLY);
		if (fd < 0)
			return (free(last_heredoc_tmp), ft_invalid_fd(start, redir));
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

void	ft_set_saved_fds(t_env *start)
{
	start->saved_stdin = dup(STDIN_FILENO);
	start->saved_stdout = dup(STDOUT_FILENO);
	start->saved_stderr = dup(STDERR_FILENO);
}

void	ft_close_saved_fs(t_env *start, t_redirect *redir,
		int fd, char *last_heredoc_tmp)
{
	if (fd >= 0)
		close (fd);
	free(last_heredoc_tmp);
	perror(redir->filename);
	ft_close_saved_fds(start);
	ft_free_forexc(start, start->env_copy);
	exit(1);
}

int	ft_check_sec_lis(t_redirect *redir, t_env *start,
		int old_fd, char *last_heredoc_tmp)
{
	int	tmp_fd;

	if (!ft_strcmp(redir->operator, "<"))
	{
		tmp_fd = open(redir->filename, O_RDONLY);
		if (tmp_fd < 0)
			ft_close_saved_fs(start, redir, old_fd, last_heredoc_tmp);
		dup2(tmp_fd, 0);
		close(tmp_fd);
		return (1);
	}
	else
		return (0);
}

int	ft_check_list_red_mul(int old_fd, t_redirect *redir,
		t_env *start, char *last_heredoc_tmp)
{
	int	tmp_fd;

	if (!ft_strcmp(redir->operator, ">"))
	{
		tmp_fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (tmp_fd < 0)
			ft_close_saved_fs(start, redir, old_fd, last_heredoc_tmp);
		dup2(tmp_fd, 1);
		close(tmp_fd);
		return (1);
	}
	else if (!ft_strcmp(redir->operator, ">>"))
	{
		tmp_fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (tmp_fd < 0)
			ft_close_saved_fs(start, redir, old_fd, last_heredoc_tmp);
		dup2(tmp_fd, 1);
		close(tmp_fd);
		return (1);
	}
	else
		return (ft_check_sec_lis(redir, start, old_fd, last_heredoc_tmp));
}
