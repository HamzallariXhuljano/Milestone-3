/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exc5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:59:40 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/08 19:46:58 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_redirections_father(t_redirect *redir, t_env *start, int fd)
{
	char	*last_heredoc_tmp;

	last_heredoc_tmp = NULL;
	while (redir)
	{
		if (!ft_strcmp(redir->operator, "<<"))
			last_heredoc_tmp = redir->heredoc_tmpfile;
		if (ft_handler_pa_check_list(start, fd, redir) == -1)
			return (-1);
		redir = redir->next;
	}
	if (start->word->arg[0][0] == '\0')
		rst_sdfd(start->saved_stdin, start->saved_stdout, start->saved_stderr);
	if (last_heredoc_tmp)
		return (ft_last_heredoc(start, redir, fd, last_heredoc_tmp));
	return (0);
}

int	ft_is_my(char *str)
{
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "pwd")
		|| !ft_strcmp(str, "export") || !ft_strcmp(str, "unset")
		|| !ft_strcmp(str, "env") || !ft_strcmp(str, "exit"))
		return (1);
	return (0);
}

int	ft_is_single_cmd(t_env *start)
{
	if (preprocess_all_heredocs(start->redirect, start, 0) == -1)
		return (ft_check_exit_code(start),
			cleanup_heredoc_files(start->redirect), -1);
	ft_set_saved_fds(start);
	if (handle_redirections_father(start->redirect[0], start, 0))
		return (ft_check_exit_code(start), rst_sdfd(start->saved_stdin,
				start->saved_stdout, start->saved_stderr), -1);
	ft_check_exit_code(start);
	exec_2(start->word, start->env_copy, start);
	return (rst_sdfd(start->saved_stdin, start->saved_stdout,
			start->saved_stderr), ft_check_exit_code(start), 0);
}

void	ft_check_exit_code(t_env *start)
{
	if (g_sigint == 1)
	{
		start->exit_code = 1;
		g_sigint = 0;
	}
	else if (g_sigint == 129 && start->exit_code != 1)
	{
		start->exit_code = 0;
		g_sigint = 0;
	}
	if (start->exit_code == 127 || start->exit_code == 256)
		return ;
	if (start->exit_code != 127 && g_sigint != 0)
	{
		start->exit_code = g_sigint;
		g_sigint = 0;
	}
}
