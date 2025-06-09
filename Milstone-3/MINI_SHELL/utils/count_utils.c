/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:31:35 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/01 18:31:48 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_comand_len(char *comand, int i)
{
	int		len_new_comand;
	char	quote_char;

	quote_char = 0;
	len_new_comand = 0;
	while (comand[i])
	{
		if (comand[i] == '\'' || comand[i] == '\"')
		{
			if (quote_char == 0)
			{
				quote_char = comand[i];
				len_new_comand++;
			}
			else if (comand[i] == quote_char)
			{
				quote_char = 0;
				len_new_comand++;
			}
		}
		i++;
	}
	return (len_new_comand);
}
