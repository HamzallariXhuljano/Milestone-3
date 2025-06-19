/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:15:09 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/19 16:06:35 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


int	main(int ac, char **av)
{
	t_data data;
	int i;

	i = 0;
	if (validate_args(ac, av) != 0)
		return (-1);
	if (init_data(&data, ac, av) != 0)
		return (-1);
	if (start_simulation(&data) != 0)
		return (cleanup_all(&data), -1);
	while(i < data.philo_count)
	{
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}
	pthread_join(data.monitor_treahd, NULL);
	cleanup_all(&data);
	return (0);
}
