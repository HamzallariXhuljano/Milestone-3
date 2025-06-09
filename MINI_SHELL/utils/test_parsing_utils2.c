/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:15:24 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/08 19:45:55 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_variable(int *i, int *j)
{
	(*i) = 0;
	(*j) = 0;
}

int	ft_iter_isalnum(char *str, int i)
{
	i++;
	while (str[i] && ft_isalnum(str[i]) == 1)
		i++;
	return (i);
}

char	*ft_help_clean_dollar(char *str, int i, int j, int in_single_quotes)
{
	char	*new_str;
	int		in_double_quotes;
	int		flag;

	set_variable(&flag, &in_double_quotes);
	new_str = ft_calloc(sizeof(char) * (ft_strlen(str) - j + 1), 1);
	if (!new_str)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (str[i] == '\"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		if ((is_true_3(str, i, in_single_quotes) == 0) && flag == 0)
		{
			flag = 1;
			i = ft_iter_isalnum(str, i);
			if (str[i] == '\0')
				break ;
		}
		new_str[j++] = str[i++];
	}
	return (new_str);
}

char	*ft_clean_dollar(char *str, int i, int sgl_quot, int in_double)
{
	int	j;

	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			sgl_quot = !sgl_quot;
		else if (str[i] == '\"' && !sgl_quot)
			in_double = !in_double;
		if (is_true_3(str, i, sgl_quot) == 0)
		{
			j = 1;
			i++;
			while (str[i] && ft_isalnum(str[i]) == 1)
			{
				i++;
				j++;
			}
			break ;
		}
		else
			i++;
	}
	return (ft_help_clean_dollar(str, 0, 0, sgl_quot));
}

int	is_true_3(char *str, int i, int in_sgl_quotes)
{
	if ((str[i] == '$' && !in_sgl_quotes && !ft_is_space(str[i + 1])
			&& ft_isalnum(str[i + 1])) || (str[i] == '$'
			&& !in_sgl_quotes && str[i + 1] == '?') || (str[i] == '$'
			&& !in_sgl_quotes && str[i + 1] == '$'))
	{
		return (0);
	}
	return (-1);
}
