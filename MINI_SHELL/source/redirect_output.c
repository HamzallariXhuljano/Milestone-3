/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:24:02 by gnicolo           #+#    #+#             */
/*   Updated: 2025/06/01 19:54:22 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_redirect(char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open() error");
		return (-1);
	}
	return (fd);
}

int	ft_redirect_append(char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open() error");
		return (-1);
	}
	return (fd);
}
