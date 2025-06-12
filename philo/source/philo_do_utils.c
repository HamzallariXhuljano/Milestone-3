/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_do_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:06:07 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/12 19:07:30 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_forks_even(t_philo *philo)
{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d has taken a fork\n",
			get_time_diff(philo->data->start_time), philo-> id + 1);
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d has taken a fork\n",
			get_time_diff(philo->data->start_time), philo-> id + 1);
		pthread_mutex_unlock(&philo->data->print_mutex);
}

void	take_forks_odd(t_philo *philo)
{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d has taken a fork\n",
			get_time_diff(philo->data->start_time), philo-> id + 1);
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d has taken a fork\n",
			get_time_diff(philo->data->start_time), philo-> id + 1);
		pthread_mutex_unlock(&philo->data->print_mutex);
}
