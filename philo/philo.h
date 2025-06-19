/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:22:38 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/19 18:23:39 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
typedef struct  s_philo
{
	int				id;
	pthread_mutex_t				*l_fork;
	pthread_mutex_t				*r_fork;
	long			last_meal;
	int				meals_eaten;
	pthread_t		thread;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	long		philo_count;
	long		time_to_die;
	long		time_to_sleep;
	long		time_to_eat;
	int			meals_required;
	int			simulation_running;
	long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	simulation_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_t		monitor_treahd;
	t_philo			*philos;
}t_data;

int		validate_args(int ac, char **av);
long	ft_atol(const char *str);
int		is_valid_number(char *str);
int		init_data(t_data *data, int ac, char **av);
int		init_philosophers(t_data *data);
int		init_mutexes(t_data *data);
int		start_simulation(t_data *data);
void	*philosopher_routine(void *arg);
void	*monitor_routine(void *arg);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);
int		check_death(t_data *data);
int		check_meals_completed(t_data *data);
void	set_simulation_status(t_data *data, int status);
long	get_current_time(void);
long	get_time_diff(long start_time);
void	precise_usleep(long microseconds);
void	safe_print(t_philo *philo, char *message);
void	cleanup_mutex(t_data *data, int i);
void	init_input(t_data *data, int ac, char **av);
void	take_forks_even(t_philo *philo);
void	take_forks_odd(t_philo *philo);
int		check_running(t_data *data);
void	cleanup_all(t_data *data);
int		check_one_philo(t_data *data);

#endif
