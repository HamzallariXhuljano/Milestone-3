/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:16:25 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/20 19:06:46 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	start_simulation(t_data *data)
{
	int	i;

	data -> start_time = get_current_time();
	i = 0;
	while (i < data -> philo_count)
	{
		data->philos[i].last_meal = data->start_time;
		i++;
	}
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philosopher_routine, &data->philos[i]))
			return (-1);
		i++;
	}
	if (pthread_create(&data->monitor_treahd, NULL, monitor_routine, data))
		return (-1);
	return (0);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo -> id % 2 == 1)
		usleep(1000);
	while (check_running(philo->data) == 1)
	{
		if (check_runing_meals(philo) == 0)
			break ;
		take_forks(philo);
		if (check_runing_meals(philo) == 0)
		{
			drop_forks(philo);
			break ;
		}
		philo_eat(philo);
		drop_forks(philo);
		if (check_runing_meals(philo) == 0)
			break ;
		philo_sleep(philo);
		if (check_runing_meals(philo) == 0)
			break ;
		philo_think(philo);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (check_running(data))
	{
		if (check_death(data) == -1 || check_meals_completed(data) == -1)
		{
			set_simulation_status(data, 0);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}
