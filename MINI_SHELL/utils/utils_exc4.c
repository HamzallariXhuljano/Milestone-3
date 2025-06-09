/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exc4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:58:28 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/06 17:21:53 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_invalid_fd__her(t_env *start, t_redirect *redir)
{
	perror(redir->heredoc_tmpfile);
	rst_sdfd(start->saved_stdin, start-> saved_stdout,
		start->saved_stderr);
	return ;
}

int	handle_redirections(t_redirect *redir, t_env *start, char *last_heredoc_tmp)
{
	int	fd;

	fd = -1;
	while (redir)
	{
		if (ft_check_list_red_mul(fd, redir, start, last_heredoc_tmp) == 1)
			;
		else if (!ft_strcmp(redir->operator, "<<"))
		{
			if (handle_redirections_h(redir, start,
					&last_heredoc_tmp, &fd) == -1)
				return (-1);
		}
		redir = redir->next;
	}
	if (start->word->arg[0][0] == '\0')
		rst_sdfd(start->saved_stdin, start->saved_stdout, start->saved_stderr);
	if (last_heredoc_tmp)
		ft_last_heredoc(start, redir, fd, last_heredoc_tmp);
	return (ft_close_saved_fds(start), 0);
}

int	ft_handler_pa_check_list2(t_env *start, int fd, t_redirect *redir)
{
	if (!ft_strcmp(redir->operator, ">"))
	{
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (ft_invalid_fd(start, redir));
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (!ft_strcmp(redir->operator, ">>"))
	{
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (ft_invalid_fd(start, redir));
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

int	ft_handler_pa_check_list(t_env *start, int fd, t_redirect *redir)
{
	if (!ft_strcmp(redir->operator, "<"))
	{
		fd = open(redir->filename, O_RDONLY);
		if (fd < 0)
			return (ft_invalid_fd(start, redir));
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (ft_handler_pa_check_list2(start, fd, redir));
}

int	ft_hree(t_env *start, int fd, t_redirect *redir, char *last_heredoc_tmp)
{
	char	*tmp;

	tmp = here_doc_file(redir->filename, start);
	if (!tmp || g_sigint)
	{
		start->exit_code = 130;
		rst_sdfd(start->saved_stdin, start->saved_stdout, start->saved_stderr);
		if (tmp)
			free(tmp);
		return (-1);
	}
	if (last_heredoc_tmp)
		free(last_heredoc_tmp);
	last_heredoc_tmp = tmp;
	if (last_heredoc_tmp)
	{
		fd = open(last_heredoc_tmp, O_RDONLY);
		if (fd < 0)
			return (ft_invalid_fd(start, redir));
		dup2(fd, STDIN_FILENO);
		close(fd);
		free(last_heredoc_tmp);
	}
	return (0);
}
