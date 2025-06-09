/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:28:49 by gnicolo           #+#    #+#             */
/*   Updated: 2025/06/06 18:40:09 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//----------------------------------------------------------------------------//
t_redirect	*ft_set_list_redirect(t_env *data, int start, int end, int *flags)
{
	t_redirect	*head;
	t_redirect	*current;
	t_redirect	*new;
	char		*str;
	int			i;

	head = NULL;
	current = NULL;
	new = NULL;
	str = ft_strdup(data->input);
	i = start - 1;
	while (++i < end)
	{
		if ((str[i] == '>' || str[i] == '<') && !ft_is_inside_quotes(str, i))
		{
			new = ft_parse_redirect_at(data, str, &i, flags);
			if (!ft_add_to_redirect_list(&head, &current, new))
				return (NULL);
			current = new;
		}
	}
	if (!head)
		head = ft_calloc(sizeof(t_redirect), 1);
	return (free(str), head);
}

t_redirect	*ft_parse_redirect_at(t_env *data, char *str, int *i, int *flags)
{
	t_redirect	*new;
	int			flags_dollar;

	new = NULL;
	new = ft_calloc(1, sizeof(t_redirect));
	flags_dollar = 0;
	if (!new)
		return (perror("malloc failed"), NULL);
	new->operator = ft_set_operator(str, i, &flags_dollar);
	if (!new->operator || !new)
		return (free(new), NULL);
	*i = ft_find_next_space(str, *i);
	if (ft_true_do_it(str, *i, new, &flags) == 1)
		return (NULL);
	new->filename = ft_help_2set(data->input, *i, data, flags_dollar);
	new->next = NULL;
	return (new);
}

char	*ft_set_operator(char *str, int *i, int *flags_dollar)
{
	if (str[*i] == '<' && str[*i + 1] == '<')
		return (*i += 2, (*flags_dollar)++, ft_strdup("<<"));
	else if (str[*i] == '>' && str[*i + 1] == '>')
		return (*i += 2, ft_strdup(">>"));
	else if (str[*i] == '>')
		return ((*flags_dollar)++, (*i)++, ft_strdup(">"));
	else if (str[*i] == '<')
		return ((*flags_dollar)++, (*i)++, ft_strdup("<"));
	return (NULL);
}

int	ft_add_to_redirect_list(t_redirect **head,
		t_redirect **current, t_redirect *new_node)
{
	if (!new_node)
	{
		if ((*head))
			ft_clean_red2((*head));
		return (0);
	}
	if (!*head)
		*head = new_node;
	else
		(*current)->next = new_node;
	*current = new_node;
	return (1);
}
