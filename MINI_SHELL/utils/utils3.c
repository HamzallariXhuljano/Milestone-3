/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:19:14 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/08 19:00:51 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_true_do_it(char *str, int i, t_redirect *new_redirect, int **flags)
{
	while (str[i] && ft_is_space(str[i]))
		i++;
	while (str[i] && ft_isalnum(str[i]) == 1)
		i++;
	if (str[i] == '\0')
		return (0);
	if (str[i] == '|' || str[i] == '>'
		|| str[i] == '<')
	{
		**flags = 1;
		return (free(new_redirect->operator), free(new_redirect),
			free(str), write(2,
				"Error: No filename after redirect\n", 35), 1);
	}
	else
		return (0);
}

int	ft_help_clean_word_to_redirect(char *input, int start)
{
	char	quote;
	int		i;

	i = ft_find_next_space(input, start);
	quote = 0;
	while (input[i] && !ft_is_space(input[i]) && input[i] != '>'
		&& input[i] != '<' && input[i] != '|' && ft_is_inside_quotes(input,
			i) == 0)
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote = input[i];
			i++;
			while (input[i] && input[i] != quote)
				i++;
			if (input[i] == quote)
				quote = 0;
			i++;
			if (input[i] == '\0')
				return (-1);
		}
		else
			i++;
	}
	return (i);
}

char	*ft_clean_word_to_redirect(char *input, int i, int j)
{
	char	*clean;

	clean = ft_calloc(ft_strlen(input) + 1, 1);
	if (!input)
		return (NULL);
	if (!clean)
		return (free(input), NULL);
	while (input[i])
	{
		if ((input[i] == '>' || input[i] == '<') && !ft_is_inside_quotes(input,
				i))
		{
			if ((input[i] == '>' && input[i + 1] == '>') || (input[i] == '<'
					&& input[i + 1] == '<'))
				i += 2;
			else
				i += 1;
			i = ft_help_clean_word_to_redirect(input, i);
			if (i == -1 || input[i] == '\0')
				return (free(input), clean);
		}
		else
			clean[j++] = input[i++];
	}
	return (free(input), clean);
}

void	ft_free_redirect_set(t_redirect **redirect, int i)
{
	if (i == 0)
		i += 1;
	while (i >= 0)
	{
		ft_clean_red2(redirect[i]);
		i--;
	}
	free(redirect);
}

int	ft_set_redirect(t_env *start, char *input, int i, int x)
{
	int	count_command;
	int	start_pos;
	int	end;

	start_pos = 0;
	end = 0;
	count_command = ft_count_command(input);
	start->redirect = ft_calloc(sizeof(t_redirect *) * (count_command + 2), 1);
	while (i <= count_command && end != -2)
	{
		end = ft_find_next_pipe(input, start_pos);
		start->redirect[i] = ft_set_list_redirect(start, start_pos, end, &x);
		if ((start->redirect[i] == NULL) || (start->redirect[i] && x != 0))
			return (ft_free_redirect_set(start->redirect, i), 1);
		start_pos = end + 1;
		i++;
	}
	start->input = ft_clean_word_to_redirect(input, 0, 0);
	if (ft_check_pipe_empty(start->input, start) == 1)
		return (ft_free_redirect_set(start->redirect, i - 1),
			free(start->input), 1);
	return (0);
}
