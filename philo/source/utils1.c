/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:10:40 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/19 16:31:24 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	cleanup_all(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->philo_count)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->simulation_mutex);
	if (data->philos)
		free(data->philos);
}


void	safe_print(t_philo *philo, char *message)
{
	 pthread_mutex_lock(&philo->data->print_mutex);

    // ✅ Non stampare se la simulazione è finita
    if (check_running(philo->data))
    {
        printf("%ld %d %s\n", get_time_diff(philo->data->start_time),
            philo->id + 1, message);
    }

    pthread_mutex_unlock(&philo->data->print_mutex);
}

