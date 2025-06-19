/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_do.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:28:44 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/19 18:08:17 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_eat(t_philo *philo)
{
	safe_print(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	precise_usleep(philo->data->time_to_eat * 1000);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		take_forks_even(philo);
	}
	else
	{
		take_forks_odd(philo);
	}
}

void	philo_sleep(t_philo *philo)
{
	safe_print(philo, "is sleaping");
	precise_usleep(philo->data->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	safe_print(philo, "is thinking");
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
