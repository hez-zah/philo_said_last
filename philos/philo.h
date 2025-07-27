/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sellyani <sellyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:00:00 by sellyani          #+#    #+#             */
/*   Updated: 2025/07/25 02:48:45 by sellyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	long			start_time;
	size_t			last_meal;
	size_t			die_time;
	long			sleep_time;
	long			eat_time;
	int				count_eat;

	pthread_t		thread;

	t_data	*data;
}	t_philo;

typedef struct s_data
{
	int				nbr_philo;
	int				stop;

	pthread_t		monitor_thread;

	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	nbr_eat_mtx;
	pthread_mutex_t	*forks;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print;

	t_philo			**philos;
}t_data;

int		ft_atoi(const char *str);
int		ft_atoi_0(const char *str);
int		check_0(t_data *data);
int		check_dead(t_data *data, int *someone_died);

int		init_ctrl(t_data *data, char **av);
int		init_all(t_data *data, char **av);
int		start_simulation(t_data *data);
void	free_controller(t_data *data);

void	*routine(void *arg);
void	*monitor(void *arg);
void	one_philo(t_philo *philo);

void	ft_eating(t_philo *philo);
int		routine_aid(t_philo *philo);
void	ft_sleeping(t_philo *philo);
void	ft_thinking(t_philo *philo);

int		finish_philos(t_data *data);
void	do_some(t_philo *philo, char *str);
size_t	get_time(void);
void	my_sleep(size_t ms);

int		variable_stop(t_data *data);
void	break_simulation(t_data *data);
int		break_simulation_aid(t_philo *philo);


#endif