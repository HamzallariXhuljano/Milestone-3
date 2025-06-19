/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_do_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:06:07 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/19 16:53:40 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_forks_even(t_philo *philo)
{
		pthread_mutex_lock(philo->l_fork);
		safe_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		safe_print(philo, "has taken a fork");
}

void	take_forks_odd(t_philo *philo)
{
		pthread_mutex_lock(philo->r_fork);
		safe_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		safe_print(philo, "has taken a fork");

}
