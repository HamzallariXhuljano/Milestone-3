/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:20:55 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/19 16:34:22 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	cleanup_mutex(t_data *data, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&data->forks[j]);
		j++;
	}
}

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long get_time_diff(long start_time)
{
	return (get_current_time() - start_time);
}

void	precise_usleep(long microseconds)
{
	long	start;
	long	target;

	start = get_current_time() * 1000;
	target = start + microseconds;
	while((get_current_time() * 1000) < target)
	{
		usleep(50);
	}
}


void	set_simulation_status(t_data *data, int status)
{
	pthread_mutex_lock(&data->simulation_mutex);
	data->simulation_running = status;
	pthread_mutex_unlock(&data->simulation_mutex);
}
