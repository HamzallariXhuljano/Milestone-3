/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:28:57 by gnicolo           #+#    #+#             */
/*   Updated: 2025/06/08 19:01:18 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_pipe_empty(char *str, t_env *env)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	i = ft_find_next_space(str, 0);
	if (str[i] == '|')
		return (write(2, "sintax error pipe\n", 18), env->exit_code = 2, 1);
	while (str[i])
	{
		if (str[i] == '|' && !ft_is_inside_quotes(str, i))
		{
			i++;
			i = ft_find_next_space(str, i);
			if (str[i] == '|' && ft_is_inside_quotes(str, i) == 0)
				return (write(2, "sintax error\n", 18), env->exit_code = 2, 1);
			else if (str[i] == '\0')
				return (write(2, "sintax error\n", 18), env->exit_code = 2, 1);
		}
		i++;
	}
	return (0);
}

int	ft_help_check_number_quote(char *str, int i, char quote_char)
{
	i = i + 1;
	if (!str[i])
		return (ft_strlen(str));
	while (str[i] && str[i] != quote_char)
		i++;
	return (i);
}

int	ft_check_number_quote(char *str, int i, int flags_quote, t_env *env)
{
	while (str[i] && flags_quote == 0)
	{
		if (str[i] == '\'')
		{
			flags_quote = (int)str[i];
			i = ft_help_check_number_quote(str, i, flags_quote);
			if (str[i] == '\'')
				flags_quote = 0;
			else
				return (printf("Error: quote\n"), env->exit_code = 2, 1);
		}
		else if (str[i] == '\"')
		{
			flags_quote = (int)str[i];
			i = ft_help_check_number_quote(str, i, flags_quote);
			if (str[i] == '\"')
				flags_quote = 0;
			else
				return (printf("Error: quote\n"), env->exit_code = 2, 1);
		}
		i++;
	}
	return (ft_check_pipe_empty(str, env));
}

void	ft_help_first_parse(t_env *start, char *ipt, int i)
{
	char	*comand;
	char	*str_after_comand;
	int		pipe_pos;

	while (ipt[i])
	{
		i = ft_find_next_space(ipt, i);
		comand = ft_first_word(ipt, i);
		str_after_comand = NULL;
		pipe_pos = ft_find_next_pipe(ipt, i);
		if (pipe_pos != i)
			str_after_comand = ft_create_argoument(ipt, ft_next_word(ipt, i));
		ft_add_node(start, comand, str_after_comand);
		if (pipe_pos == -1)
			break ;
		i = pipe_pos;
		if (ipt[i] == '|')
			i++;
	}
}

int	ft_first_parse(t_env *start, char *input)
{
	int		i;

	if (ft_check_number_quote(input, 0, 0, start) == 1)
		return (1);
	if (ft_set_redirect(start, input, 0, 0) == 1)
		return (1);
	input = start->input;
	i = ft_find_next_space(input, 0);
	ft_set_first_node(input, i, start);
	i = ft_find_next_pipe(input, i) + 1;
	if (i == 0)
	{
		start->word->next = NULL;
		return (0);
	}
	if (i == -1)
		return (write(1, "Error: Unmatched pipe\n", 22), 1);
	if (i > (int)ft_strlen(input))
		return (0);
	ft_help_first_parse(start, input, i);
	return (0);
}
