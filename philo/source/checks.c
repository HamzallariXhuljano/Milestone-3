/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:11:53 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/20 19:16:14 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_death(t_data *data)
{
	int		i;
	long	last_meal;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->meal_mutex);
		last_meal = data->philos[i].last_meal;
		pthread_mutex_unlock(&data->meal_mutex);
		if ((get_current_time() - last_meal) > data->time_to_die
			&& (data->philos[i].meals_eaten < data -> meals_required
				|| data -> meals_required == -1))
		{
			safe_print(&data->philos[i], "died");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	check_meals_completed(t_data *data)
{
	int	i;
	int	completed_cnt;

	i = 0;
	completed_cnt = 0;
	if (data -> meals_required == -1)
		return (0);
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (data->philos[i].meals_eaten >= data->meals_required)
			completed_cnt++;
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	if (completed_cnt == data->philo_count)
		return (-1);
	return (0);
}

int	check_running(t_data *data)
{
	int	running;

	pthread_mutex_lock(&data->simulation_mutex);
	running = data->simulation_running;
	pthread_mutex_unlock(&data->simulation_mutex);
	return (running);
}

int	check_one_philo(t_data *data)
{
	if (data->philo_count == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(data->time_to_die * 1000);
		printf("%ld 1 died\n", data->time_to_die);
		cleanup_all(data);
		return (0);
	}
	return (-1);
}

int	check_runing_meals(t_philo *philo)
{
	if (!check_running(philo->data)
		|| (philo->meals_eaten == philo->data->meals_required))
		return (0);
	return (-1);
}
