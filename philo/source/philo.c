/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:15:09 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/12 16:12:27 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


int	main(int ac, char **av)
{
	t_data data;
	if (validate_args(ac, av) != 0)
		return (-1);
	if (init_data(&data, ac, av) != 0)
		return (-1);
}
