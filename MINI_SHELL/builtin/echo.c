/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:40:41 by gnicolo           #+#    #+#             */
/*   Updated: 2025/06/01 17:23:14 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_help_echo(char **arg, int i)
{
	while (arg[i])
	{
		ft_putstr_fd(arg[i], 1);
		if (arg[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
}

void	ft_echo(char **arg)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (!arg[1])
		return (ft_putchar_fd('\n', 1));
	if (arg[i][0] == '-' && arg[i][1] == 'n')
	{
		n_flag = 2;
		while (arg[i][n_flag] == 'n')
			n_flag++;
		if (arg[i][n_flag] == '\0')
		{
			i++;
			n_flag = 1;
		}
		else
			n_flag = 0;
	}
	ft_help_echo(arg, i);
	if (!n_flag)
		ft_putchar_fd('\n', 1);
}
