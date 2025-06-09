/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnicolo <gnicolo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:06:19 by xhamzall          #+#    #+#             */
/*   Updated: 2025/05/28 20:27:22 by gnicolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path_evnp(char **evnp)
{
	int	i;

	i = 0;
	while (evnp[i])
	{
		if (ft_strncmp(evnp[i], "PATH=", 5) == 0)
		{
			return ((evnp[i] + 5));
		}
		i++;
	}
	return (NULL);
}

char	*make_path(char *dir, char *cmd )
{
	char	*path;

	path = malloc(ft_strlen(dir) + ft_strlen(cmd) + 2);
	if (!path)
	{
		perror("Path allocation faild");
		return (free (path), NULL);
	}
	ft_strlcpy(path, dir, ft_strlen(dir));
	ft_strlcat(path, "/", 1);
	ft_strlcat(path, cmd, ft_strlen(cmd));
	return (path);
}

char	**get_path(char **evnp)
{
	char	*evnp_path;
	char	**path;

	evnp_path = path_evnp(evnp);
	if (!evnp_path)
	{
		perror("PATH not found");
		free(evnp_path);
		return (NULL);
	}
	path = ft_split(evnp_path, ':');
	if (!path)
	{
		perror("Split don't work as expect");
		ft_free_matrix(path);
		return (NULL);
	}
	return (path);
}

char	*get_comand_path(char *cmd, char **path)
{
	char	*full_path;
	int		i;

	i = 0;
	while (path && path[i])
	{
		full_path = make_path(path[i], cmd);
		if (!full_path)
		{
			free (full_path);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			ft_free_matrix(path);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_matrix(path);
	return (perror("Command not found"), NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**path;
	char	*full_path;

	path = get_path(envp);
	if (!path)
	{
		ft_free_matrix(path);
		return (NULL);
	}
	full_path = get_comand_path(cmd, path);
	if (!full_path)
	{
		free (full_path);
		return (NULL);
	}
	return (full_path);
}
