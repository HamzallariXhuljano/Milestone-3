/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:44:20 by gnicolo           #+#    #+#             */
/*   Updated: 2025/06/01 17:35:29 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_second_parse(t_env *start)
{
	t_list_1	*head;
	int			count;

	head = start->word;
	while (head)
	{
		count = ft_count_dollar_to_expand(head->comand, 0, 0, 0);
		while (count > 0)
		{
			head->comand = ft_expand_str(head->comand, start, 0, 0);
			count--;
		}
		if (head->str_after_comand != NULL)
			count = ft_count_dollar_to_expand(head->str_after_comand, 0, 0, 0);
		else
			count = 0;
		while (count > 0 && head->str_after_comand != NULL)
		{
			head->str_after_comand = ft_expand_str(head->str_after_comand,
					start, 0, 0);
			count--;
		}
		head = head->next;
	}
}
