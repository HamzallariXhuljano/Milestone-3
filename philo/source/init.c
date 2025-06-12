/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:04:08 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/12 16:10:59 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_data(t_data *data, int ac, char **av)
{
	init_input(data, ac, av);
	if (init_mutexes(data) != 0)
		return (-1);
	data -> simulation_running = 1;
	if (init_philosophers(data) != 0)
		return (-1);

	return (0);
}

void	init_input(t_data *data, int ac, char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (i == 1)
			data -> philo_count = ft_atol(av[i]);
		else if ( i == 2)
			data -> time_to_die = ft_atol(av[i]);
		else if (i == 3)
			data -> time_to_eat = ft_atol(av[i]);
		else if (i == 4)
			data -> time_to_sleep = ft_atol(av[i]);
		else if (i == 5)
			data -> meals_required = ft_atol(av[i]);
		i++;
	}
	if (ac == 5)
			data -> meals_required = - 1;

}

int	init_mutexes(t_data *data)
{
	int		i;

	data -> forks = malloc (data -> philo_count * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (-1);

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			cleanup_mutex(data, i);
			return (-1);
		}
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return(cleanup_mutex(data, data->philo_count), -1);
	if (pthread_mutex_init(&data->simulation_mutex, NULL) != 0)
	{
		cleanup_mutex(data, data->philo_count);
		pthread_mutex_destroy(&data->print_mutex);
		return (-1);
	}
	return (0);
}

int	init_philosophers(t_data *data)
{
	int	i;

	data -> philos = malloc (sizeof(t_philo) * data->philo_count);
	if (!data->philos)
		return (-1);
	i = 0;
	while (i < data->philo_count)
	{
		data->philos[i].id = i;
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[(i + 1) % data->philo_count];
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].data = data;
		i++;
	}
	return (0);
}
