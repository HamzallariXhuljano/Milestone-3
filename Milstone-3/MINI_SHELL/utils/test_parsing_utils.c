/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:10:40 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/01 20:01:15 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Funzione per trovare il prossimo carattere pipe
int	ft_find_next_pipe(char *str, int start)
{
	int	i;

	if (!str)
		return (-1);
	i = start;
	while (str[i] && str[i] != '|')
		i++;
	if (str[i] == '|')
	{
		if (ft_is_inside_quotes(str, i) == 1)
			return (ft_find_next_pipe(str, i + 1));
		else
		{
			start = i + 1;
			while (str[start] && ft_is_space(str[start]))
				start++;
			if (str[start] == '\0')
				return (-2);
			return (i);
		}
	}
	else
		return (ft_strlen(str));
}

void	ft_help_copy_first_word(char *word, char *str, int i, char quote)
{
	int	j;

	j = 0;
	while (str[i] && (ft_is_space(str[i]) == 0 || quote != 0)
		&& str[i] != '|')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			word[j++] = str[i++];
			while (str[i] && str[i] != quote)
				word[j++] = str[i++];
			if (str[i] == quote)
			{
				word[j++] = str[i++];
				quote = 0;
			}
		}
		else
			word[j++] = str[i++];
	}
}

int	ft_help_size_first_word(char *str, int i, int length, int flags_quote)
{
	while (str[i] && (ft_is_space(str[i]) == 0 || flags_quote != 0))
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			flags_quote = str[i];
			ft_iter_pointer_two(&length, &i, 0);
			while (str[i] && str[i] != flags_quote)
			{
				length++;
				i++;
			}
			if (str[i] == flags_quote)
			{
				ft_iter_pointer_two(&length, &i, 0);
				flags_quote = 0;
			}
		}
		else
			ft_iter_pointer_two(&length, &i, 0);
	}
	return (length);
}

char	*ft_first_word(char *str, int start)
{
	int		i;
	int		length;
	char	*word;

	if (!str)
		return (NULL);
	i = ft_find_next_space(str, start);
	length = ft_help_size_first_word(str, i, 0, 0);
	word = ft_calloc(sizeof(char), length + 1);
	if (!word)
		return (perror("Error allocating memory for word"), NULL);
	i = start;
	ft_help_copy_first_word(word, str, i, 0);
	return (word);
}

// Funzione per creare un argomento
char	*ft_create_argoument(char *str, int start)
{
	int		i;
	char	*word;
	int		j;

	i = start;
	if (start == (int)ft_strlen(str))
		return (NULL);
	while ((str[i] && str[i] != '|') || (ft_is_inside_quotes(str, i)
			&& i < (int)ft_strlen(str)))
	{
		i++;
		if (str[i] == '|')
		{
			if (ft_is_inside_quotes(str, i) == 1)
				i++;
			else
				break ;
		}
	}
	word = ft_calloc(sizeof(char) * (i - start + 1), 1);
	j = 0;
	while (start < i)
		word[j++] = str[start++];
	return (word);
}
