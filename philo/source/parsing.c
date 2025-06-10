/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:10:21 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/10 18:35:57 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	validate_args(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (-1);
	i = 1;
	while (av[i])
	{
		if (is_valid_number(av[i]) != 0)
			return (printf("Input not valid\n"), -1);
		if (i ==  1 && ft_atoi(av[i]) < 1)
			return (printf("Philosopher: number not valid\n"), -1);
		else if (i == 2 && ft_atoi(av[i]) < 0)
			return (printf("Time die: number not valid\n"), -1);
		else if (i == 3 && ft_atoi(av[i]) < 0)
			return (printf("Time eat: number not valid\n"), -1);
		else if (i == 4 && ft_atoi(av[i]) < 0)
			return (printf("Time sleep: number not valid\n"), -1);
		else if (ac == 6 && i == 5 && ft_atoi(av[i]) < 0)
			return (printf("TMeals: number not valid\n"), -1);
		i++;
	}
	return (0);
}

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
	{
		sign = -sign;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - 48);
		i++;
	}
	return (num * sign);
}
