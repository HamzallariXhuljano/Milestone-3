/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:57:27 by gnicolo           #+#    #+#             */
/*   Updated: 2025/06/08 19:28:52 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_iter_pointer_two(int *a, int *b, int flags)
{
	if (flags == 0)
	{
		(*a)++;
		(*b)++;
	}
	else
	{
		(*a)++;
		(*a)++;
		(*b)++;
	}
}

// void ft_copy_word(char *comand,int i, char *new_comand, int j)
// {
// 	char	quote_char;

// 	quote_char = 0;
// 	while (comand[i])
// 	{
// 		if ((comand[i] == '\'' || comand[i] == '\"') && quote_char == 0)
// 		{
// 			if (quote_char == 0)
// 			{
// 				quote_char = comand[i];
// 				i++;
// 			}
// 			else if (comand[i] == quote_char)
// 			{
// 				quote_char = 0;
// 				i++;
// 			}
// 			if (comand[i] == '\0')
// 				break ;
// 		}
// 		else
// 			new_comand[j++] = comand[i++];
// 	}
// }

// char	*ft_clean_word(char *comand)
// {
// 	char	*new_comand;

// 	new_comand = ft_calloc(sizeof(char), ((int) ft_strlen(comand) + 1));
// 	if (!new_comand)
// 		return (NULL);
// 	ft_copy_word(comand, 0, new_comand, 0);
// 	if (!new_comand)
// 		return (free(comand), NULL);
// 	return (free(comand), new_comand);
// }

t_list_1	*ft_clean_comand_to_quote(t_list_1 *comand)
{
	t_list_1	*head;

	head = comand;
	while (head)
	{
		head->comand = ft_clean_word(head->comand);
		head->str_after_comand = ft_clean_word(head->str_after_comand);
		head = head->next;
	}
	return (comand);
}

char	*ft_help_expand_str(char *str, char **envp, int i, t_env *start)
{
	char	*doll_arg;
	char	*new_str;
	char	*nn_str;

	doll_arg = take_string(str, start);
	if (!ft_strcmp(doll_arg, "892631") || ft_atoi(doll_arg) == start->exit_code)
	{
		new_str = ft_expand_dollar_dollar(str, doll_arg);
		free(doll_arg);
		free(str);
		return (new_str);
	}
	nn_str = check_in_env(envp, doll_arg);
	if (nn_str == NULL)
	{
		nn_str = ft_clean_dollar(str, 0, 0, 0);
		free(doll_arg);
		free(str);
		return (nn_str);
	}
	new_str = ft_expand(str, nn_str, i);
	free(doll_arg);
	free(str);
	return (new_str);
}

char	*ft_expand_str(char *str, t_env *start, int i, int in_single_quotes)
{
	int		count;
	char	*new_str;
	int		in_double_quotes;

	in_double_quotes = 0;
	count = ft_count_dollar_to_expand(str, 0, 0, 0);
	if (count == 0)
		return (str);
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (str[i] == '\"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		if (is_true_3(str, i, in_single_quotes) == 0)
		{
			new_str = ft_help_expand_str(str, start->env_copy, i, start);
			return (new_str);
		}
		else
			i++;
	}
	return (str);
}

void	iteri_comand(char **comand, int *i, int *j, char **new_comand)
{
	char	quote_char;

	quote_char = 0;
	while ((*comand)[(*i)])
	{
		if ((*comand)[(*i)] == '\'' || (*comand)[(*i)] == '\"')
		{
			if (quote_char == 0)
			{
				quote_char = (*comand)[(*i)++];
				if ((*comand)[(*i)] == '\0')
					break ;
				continue ;
			}
			else if ((*comand)[(*i)] == quote_char)
			{
				quote_char = 0;
				(*i)++;
				if ((*comand)[(*i)] == '\0')
					break ;
				continue ;
			}
		}
		(*new_comand)[(*j)++] = (*comand)[(*i)++];
	}
}
