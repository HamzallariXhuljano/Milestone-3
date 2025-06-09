/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:17:06 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/02 16:25:01 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_index_dollar(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '$' && ft_is_inside_a_singole_quotes(str, i) == 0
			&& ft_isalnum(str[i + 1]) == 1)
			return (i + 1);
		i++;
	}
	return (-1);
}

void	ft_copy_ddollar(char *str, char *new_str, char *replace_str, int k)
{
	int	i;
	int	j;
	int	replaced;

	i = 0;
	j = 0;
	replaced = 0;
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] == '$' || str[i + 1] == '?')
			&& !replaced)
		{
			while (k < (int)ft_strlen(replace_str))
			{
				new_str[j++] = replace_str[k];
				k++;
			}
			i += 2;
			replaced = 1;
		}
		else
			new_str[j++] = str[i++];
	}
}

int	ft_help_size_len(char *str, int replace_len)
{
	int	i;
	int	len;
	int	replaced;

	len = 0;
	i = 0;
	replaced = 0;
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] == '$' || str[i + 1] == '?')
			&& !replaced)
		{
			len += replace_len;
			i += 2;
			replaced = 1;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*ft_expand_dollar_dollar(char *str, const char *replace_str)
{
	int		len;
	int		replace_len;
	char	*new_str;

	replace_len = ft_strlen(replace_str);
	if (!str)
		return (NULL);
	len = ft_help_size_len(str, replace_len);
	new_str = ft_calloc(len + 1, 1);
	if (!new_str)
		return (perror("Error allocating memory for expanded string"), NULL);
	ft_copy_ddollar(str, new_str, (char *)replace_str, 0);
	return (new_str);
}

char	*ft_expand(char *str, char *doll_arg, int index_dollar)
{
	int		len;
	char	*new_str;
	int		i;

	i = index_dollar + 1;
	if (str[i] == '$')
		i++;
	while (str[i] && ft_isalnum(str[i]) == 1)
		i++;
	i = i - index_dollar;
	len = ft_strlen(doll_arg) + ft_strlen(str);
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
	{
		perror("Error allocating memory for new string");
		return (NULL);
	}
	ft_strlcpy(new_str, str, index_dollar + 1);
	ft_strlcat(new_str, doll_arg, index_dollar + ft_strlen(doll_arg) + 1);
	ft_strlcat(new_str, str + index_dollar + i, len + 1);
	return (new_str);
}
