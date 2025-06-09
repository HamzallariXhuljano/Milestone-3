/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_something.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:21:17 by gnicolo           #+#    #+#             */
/*   Updated: 2025/06/01 18:34:45 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Funzione per identificare gli spazi
int	ft_is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	ft_is_inside_quotes(char *str, int pos_c)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	if (!str)
		return (1);
	while (str[i] && i < pos_c)
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote && i < pos_c)
				i++;
			if (str[i] == quote)
				i++;
			else
				return (1);
			if (str[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_is_inside_a_singole_quotes(char *str, int pos_c)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	if (!str)
		return (1);
	while (str[i] && i < pos_c)
	{
		if (str[i] == '\'' )
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote && i < pos_c)
				i++;
			if (str[i] == quote)
				i++;
			else
				return (1);
			if (str[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_is_inside_double_quotes(char *str, int pos_c)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	if (!str)
		return (1);
	while (str[i] && i < pos_c)
	{
		if (str[i] == '\"' )
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote && i < pos_c)
				i++;
			if (str[i] == quote)
				i++;
			else
				return (1);
			if (str[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_is_quote(char c)
{
	return (c == '\'' || c == '\"');
}
