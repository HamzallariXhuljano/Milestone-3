/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:17:13 by gnicolo           #+#    #+#             */
/*   Updated: 2025/06/06 17:25:21 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_doubledollar(char *str)
{
	int	i;
	int	count;
	int	in_single_quotes;
	int	in_double_quotes;

	i = 0;
	count = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (str[i] == '\"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		if (str[i] == '$' && str[i + 1] == '$' && !in_single_quotes)
		{
			count++;
			i += 2;
		}
		else
			i++;
	}
	return (count);
}

static void	ft_true(char *str, int *i, int *count)
{
	if (str[(*i) + 1] != '\0' && !ft_is_space(str[(*i) + 1])
		&& (ft_isalnum(str[(*i) + 1]) == 1 || ft_is_quote(str[(*i) + 1]) == 1
			|| str[(*i) + 1] == '?'))
	{
		(*count)++;
		(*i)++;
		while (str[(*i)] && ft_isalnum(str[(*i)]))
			(*i)++;
	}
	else if (!str[(*i) + 1])
		return ;
	else
		(*i)++;
}

static void	ft_is_true2(char *str, int *i, int in_single_quotes, int *count)
{
	if ((str[(*i)] == '$' && str[(*i) + 1] == '?' && !in_single_quotes)
		|| (str[(*i)] == '$' && str[(*i) + 1] == '$' && !in_single_quotes))
	{
		(*i) += 2;
		(*count)++;
	}
	return ;
}

int	ft_count_dollar_to_expand(char *str, int i, int count, int in_single_quotes)
{
	int	in_double_quotes;

	in_double_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (str[i] == '\"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		ft_is_true2(str, &i, in_single_quotes, &count);
		if (str[i] == '\0')
			return (count);
		else if (str[i] == '$' && !in_single_quotes
			&& !ft_is_space(str[i + 1] && ft_isalnum(str[i + 1])))
		{
			if (str[i + 1] == '\0' || ft_is_quote(str[i + 1]))
				return (count);
			ft_true(str, &i, &count);
			if (str[i] == '\0')
				return (count);
		}
		else
			i++;
	}
	return (count);
}

int	ft_count_command(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (-1);
	while (str[i] && i <= (int)ft_strlen(str))
	{
		if (str[i] == '|' && ft_is_inside_quotes(str, i) == 0)
		{
			count++;
			while (str[i] && ft_is_space(str[i]) == 1)
				i++;
			if (str[i] == '\0' || str[1] == '|')
				return (-1);
		}
		i++;
	}
	return (count);
}
