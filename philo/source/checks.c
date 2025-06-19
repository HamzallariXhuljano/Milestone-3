/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:11:53 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/19 16:51:31 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_death(t_data *data)
{
	int	i;
	long	crt_time;
	long	last_meal;

	crt_time = get_current_time();
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->meal_mutex);
		last_meal = data->philos[i].last_meal;
		pthread_mutex_unlock(&data->meal_mutex);
		if ((get_current_time() - last_meal) > data->time_to_die)
		{
			safe_print(&data->philos[i], "is died");
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
		return(-1);
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
