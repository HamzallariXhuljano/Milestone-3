/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollaro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:46:20 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/07 20:35:22 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_dollaro(char *str, int sgl_qts, int dbl_qts, int i)
{
	int		j;

	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !dbl_qts)
			sgl_qts = !sgl_qts;
		else if (str[i] == '\"' && !sgl_qts)
			dbl_qts = !dbl_qts;
		if (str[i] == '$' && !sgl_qts
			&& !ft_is_space(str[i + 1]) && ft_isalnum(str[i + 1]))
		{
			i ++;
			while (ft_isalnum(str[i]) == 1 && str[i])
			{
				i++;
				j++;
			}
			return (j);
		}
		i++;
	}
	return (j);
}

char	*ft_double_dollar(char *str)
{
	int		i;
	int		in_single_quotes;
	int		in_double_quotes;

	i = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (str[i] == '\"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		if (str[i] == '$' && !in_single_quotes && !ft_is_space(str[i + 1]))
		{
			if (str[i + 1] == '$')
				return (ft_itoa(892631));
			else
				return (NULL);
		}
		i++;
	}
	return (NULL);
}

char	*ft_help_take_string(char *str, int i, t_env *start)
{
	char	*var;
	int		j;

	j = 0;
	if (str[i + 1] == '?')
		return (ft_itoa(start->exit_code));
	var = ft_double_dollar(str);
	if (var)
		return (var);
	var = ft_calloc(len_dollaro(str, 0, 0, 0) + 1, sizeof(char));
	i++;
	while (str[i] != ' ' && str[i] && ft_isalnum(str[i]) == 1)
		var[j++] = str[i++];
	return (var);
}

char	*take_string(char *str, t_env *start)
{
	int		i;
	int		in_single_quotes;
	int		in_double_quotes;

	i = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (str[i] == '\"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		if ((str[i] == '$' && !in_single_quotes
				&& !ft_is_space(str[i + 1]) && ft_isalnum(str[i + 1]))
			|| (str[i] == '$' && !in_single_quotes && str[i + 1] == '?')
			|| (str[i] == '$' && !in_single_quotes && str[i + 1] == '$'))
			return (ft_help_take_string(str, i, start));
		i++;
	}
	return (str);
}

char	*check_in_env(char **envp, char *str)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(str);
	if (!str || str[0] == '\0')
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}
