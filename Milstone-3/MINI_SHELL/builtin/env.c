/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:32:40 by gnicolo           #+#    #+#             */
/*   Updated: 2025/06/01 17:26:12 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(char **envp, int fd_to_write)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (check_equal(envp[i]) == -1)
			i++;
		else if (envp[i] == NULL)
			break ;
		else
		{
			ft_putendl_fd(envp[i], fd_to_write);
			i++;
		}
	}
}
