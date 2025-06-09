/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:43:57 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/08 19:10:42 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha((unsigned char)str[i]) && str[i] != '_')
		return (-1);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum((unsigned char)str[i]))
			return (-1);
		i++;
	}
	return (0);
}

void	sort_export(char **env_cpy)
{
	char	*tmp;
	int		i;
	int		j;
	int		n;

	n = 0;
	while (env_cpy[n])
		n++;
	i = 0;
	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (ft_strcmp(env_cpy[i], env_cpy[j]) > 0)
			{
				tmp = env_cpy[i];
				env_cpy[i] = env_cpy[j];
				env_cpy[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	check_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (-1);
}

char	*get_name(char	*str)
{
	int		len;
	char	*name;

	len = 0;
	if (!str || !*str)
		return (NULL);
	while (str[len] && str[len] != '=')
		len++;
	name = malloc((len + 1) * sizeof(char));
	if (!name)
		return (NULL);
	ft_strlcpy(name, str, len + 1);
	return (name);
}

char	*get_value(char	*str)
{
	char	*equal_sign;
	char	*value;

	if (!str)
		return (NULL);
	equal_sign = ft_strchr(str, '=');
	if (!equal_sign)
		return (NULL);
	value = ft_strdup(equal_sign + 1);
	return (value);
}
