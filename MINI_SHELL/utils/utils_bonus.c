/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:09:59 by gnicolo           #+#    #+#             */
/*   Updated: 2025/06/01 20:36:52 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_file(char *file, int in_or_out)
{
	int	ret;

	if (in_or_out == 0)
		ret = open(file, O_RDONLY, 0777);
	if (in_or_out == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (in_or_out == 2)
		ret = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (ret == -1)
		exit(0);
	return (ret);
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*ft_get_path(char *cmd_name, char **env, int i)
{
	char	*exec;
	char	**allpath;
	char	*path_part;

	if (!cmd_name)
		return (NULL);
	if (ft_strchr(cmd_name, '/'))
		return (ft_check_direct_path(cmd_name));
	allpath = ft_split(my_getenv("PATH", env), ':');
	if (!allpath || !allpath[0] || !allpath[0][0])
		return (free(allpath), NULL);
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, cmd_name);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
			return (ft_free_tab(allpath), exec);
		free(exec);
	}
	return (ft_free_tab(allpath), NULL);
}

char	*ft_check_direct_path(char *cmd_name)
{
	if (access(cmd_name, F_OK | X_OK) == 0)
		return (ft_strdup(cmd_name));
	return (NULL);
}
