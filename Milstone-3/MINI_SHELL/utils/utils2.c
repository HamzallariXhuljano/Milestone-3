/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:18:34 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/08 19:36:37 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_help_expand(char *str, char **envp, int i, t_env *start)
{
	char	*new_str;
	char	*doll_arg;
	char	*nn_str;

	i++;
	if (ft_is_quote(str[i]) == 0)
		return (str);
	doll_arg = take_string(str, start);
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

char	*ft_expand_str2(char *str, char **envp, t_env *start)
{
	int		i;
	int		count;
	char	*new_str;

	i = 0;
	count = ft_count_dollar_to_expand(str, 0, 0, 0);
	if (count == 0)
		return (str);
	if (!str)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '$' && ft_is_inside_a_singole_quotes(str, i) == 0
				&& ft_is_space(str[i + 1]) == 0) || (str[i] == '$'
				&& ft_is_inside_double_quotes(str, i) == 1))
		{
			new_str = ft_help_expand(str, envp, i, start);
			return (new_str);
		}
		i++;
	}
	return (str);
}

int	ft_help_set(char *str, int i)
{
	char	quote;

	quote = 0;
	while (str[i] && !ft_is_space(str[i]) && str[i] != '>'
		&& str[i] != '<' && str[i] != '|')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == quote)
				quote = 0;
			i++;
		}
		else
			i++;
	}
	return (i);
}

char	*ft_help_2set(char *str, int i, t_env *data, int flags_dollar)
{
	int		filename_start;
	char	*filename;

	filename_start = i;
	i = ft_help_set(str, i);
	filename = ft_substr(str, filename_start, i
			- filename_start);
	if (flags_dollar != 0)
		filename = ft_expand_str2(filename,
				data->env_copy, data);
	filename = ft_clean_word(filename);
	return (filename);
}
