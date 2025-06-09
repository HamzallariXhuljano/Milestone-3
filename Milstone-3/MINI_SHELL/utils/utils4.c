/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:20:40 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/02 16:20:53 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix && matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

char	**dup_mtx(char **mtx)
{
	char	**tmp;
	int		i;

	if (!mtx)
		return (NULL);
	i = 0;
	while (mtx[i])
		i++;
	tmp = malloc((i + 1) * sizeof(char *));
	if (!tmp)
		return (NULL);
	i = 0;
	while (mtx[i])
	{
		tmp[i] = ft_strdup(mtx[i]);
		if (!tmp[i])
			return (ft_free_matrix(tmp), NULL);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

void	free_cmd_lst(t_list_1 *cmd)
{
	t_list_1	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		free(cmd->comand);
		free(cmd->str_after_comand);
		if (cmd->arg)
			ft_free_matrix(cmd->arg);
		free(cmd);
		cmd = tmp;
	}
}

void	close_fds(t_env *env)
{
	if (env->fd_to_read != STDIN_FILENO)
		close(env->fd_to_read);
	if (env->fd_to_write != STDOUT_FILENO)
		close(env->fd_to_write);
	if (env->pipe_fd[0] != -1)
		close(env->pipe_fd[0]);
	if (env->pipe_fd[1] != -1)
		close(env->pipe_fd[1]);
}
