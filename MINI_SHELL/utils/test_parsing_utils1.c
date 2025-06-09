/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:12:44 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/01 20:01:50 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_node(t_env *start, char *comand, char *str_after_comand)
{
	t_list_1	*new_node;
	t_list_1	*temp;

	new_node = malloc(sizeof(t_list_1));
	if (!new_node)
		return ;
	new_node->comand = comand;
	new_node->str_after_comand = str_after_comand;
	new_node->next = NULL;
	if (start->word == NULL)
		start->word = new_node;
	else
	{
		temp = start->word;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
}

int	ft_next_word(char *str, int start)
{
	int		i;
	char	quote_char;

	if (!str)
		return (-1);
	i = start;
	quote_char = 0;
	while (str[i] && ft_is_space(str[i]))
		i++;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (quote_char == 0)
				quote_char = str[i];
			else if (str[i] == quote_char)
				quote_char = 0;
		}
		if (quote_char == 0 && ft_is_space(str[i]))
			break ;
		i++;
	}
	while (str[i] && ft_is_space(str[i]))
		i++;
	return (i);
}

void	ft_set_first_node(char *input, int i, t_env *start)
{
	start->word = malloc(sizeof(t_list_1));
	start->word->comand = ft_first_word(input, i);
	start->word->str_after_comand = ft_create_argoument(input,
			ft_next_word(input, i));
	start->word->next = NULL;
}

int	ft_find_next_space(char *str, int start)
{
	int	i;

	i = start;
	if (!str)
		return (-1);
	while (str[i] && ft_is_space(str[i]))
		i++;
	return (i);
}

char	*ft_clean_word(char *comand)
{
	int		i;
	char	*new_comand;
	int		j;

	if (!comand)
		return (NULL);
	new_comand = ft_calloc(sizeof(char), (ft_strlen(comand) + 1));
	if (!new_comand)
		return (NULL);
	i = 0;
	j = 0;
	iteri_comand(&comand, &i, &j, &new_comand);
	return (free(comand), new_comand);
}
