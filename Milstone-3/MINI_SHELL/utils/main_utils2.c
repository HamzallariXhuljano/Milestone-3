/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:39:12 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/01 20:00:13 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_help_count_argv(char *str, char quote, int i)
{
	while (str[i] && (ft_is_space(str[i]) == 0))
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == quote)
			{
				i++;
				quote = 0;
			}
		}
		else
			i++;
	}
	return (i);
}

int	ft_count_argv(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!str)
		return (-1);
	while (i < (int)ft_strlen(str))
	{
		count++;
		i = ft_help_count_argv(str, 0, i);
		if (str[i] == '\0')
			return (count);
		i = ft_find_next_space(str, i);
		if (str[i] == '\0')
			return (count);
	}
	return (count);
}

void	ft_fill_argv(char **argv, char *str, char *comand)
{
	int	i;
	int	j;

	argv[0] = ft_strdup(comand);
	j = 1;
	i = ft_find_next_space(str, 0);
	if (!str)
		return ;
	while (j < (ft_count_argv(str) + 1))
	{
		argv[j] = ft_first_word(str, i);
		i = ft_next_word(str, i);
		j++;
	}
}

void	ft_clean_to_quote_argv(char **argv)
{
	int	i;

	i = 0;
	if (!argv || !argv[0])
		return ;
	while (argv[i])
	{
		argv[i] = ft_clean_word(argv[i]);
		i++;
	}
}

void	ft_set_argv(t_list_1 *word)
{
	t_list_1	*temp;
	int			count;

	temp = word;
	while (temp)
	{
		count = ft_count_argv(temp->str_after_comand);
		if (count == -1)
		{
			temp->arg = ft_calloc(sizeof(char *), 2);
			temp->arg[0] = ft_strdup(temp->comand);
			temp->arg[1] = NULL;
		}
		else
		{
			temp->arg = ft_calloc(sizeof(char *), (count + 2));
			ft_fill_argv(temp->arg, temp->str_after_comand, temp->comand);
			ft_clean_to_quote_argv(temp->arg);
		}
		temp = temp->next;
	}
}
