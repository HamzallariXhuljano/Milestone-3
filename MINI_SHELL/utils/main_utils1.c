/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnicolo <gnicolo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:38:06 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/04 16:46:23 by gnicolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_redirect(t_redirect **redirect)
{
	int	i;

	if (!redirect)
		return ;
	i = 0;
	while (redirect[i])
	{
		ft_clean_red2(redirect[i]);
		i++;
	}
	free(redirect);
}

void	ft_free_word(t_list_1 *word)
{
	t_list_1	*temp;

	while (word)
	{
		temp = word;
		word = word->next;
		ft_free_matrix(temp->arg);
		free(temp->comand);
		if (temp->str_after_comand)
			free(temp->str_after_comand);
		free(temp);
	}
}

void	ft_free_env2(char **env_copy)
{
	int	i;

	i = 0;
	while (env_copy[i])
	{
		free(env_copy[i]);
		i++;
	}
	free(env_copy);
}

void	ft_free_env(t_env *start)
{
	ft_free_redirect(start->redirect);
	ft_free_word(start->word);
	free(start->input);
}
