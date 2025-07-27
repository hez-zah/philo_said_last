/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sellyani <sellyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:00:00 by sellyani          #+#    #+#             */
/*   Updated: 2025/07/25 02:48:45 by sellyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	finish_philos(t_data *data)//all_philos_don
{
	int	i;

	if (variable_stop(data))
		return (1);
	i = -1;
	while (++i < data->nbr_philo)
	{
		pthread_mutex_lock(&data->nbr_eat_mtx);
		if (data->philos[i]->count_eat)
			return (pthread_mutex_unlock(&data->nbr_eat_mtx), 0);
		pthread_mutex_unlock(&data->nbr_eat_mtx);
	}
	return (1);
}

void	do_some(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print);
	if (!variable_stop(philo->data))
		printf("%ld %d %s\n", get_time() - philo->start_time,
			philo->id, str);
	pthread_mutex_unlock(&philo->data->print);
}

void	my_sleep(size_t ms)
{
	size_t	debut;
	size_t	fin;

	debut = get_time();
	while (1)
	{
		usleep(100);
		fin = get_time() - debut;
		if (fin >= ms)
			break ;
	}
}

void	break_simulation(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
}

int	break_simulation_aid(t_philo *philo)
{
	int		stopped;

	pthread_mutex_lock(&philo->data->stop_mutex);
	stopped = philo->data->stop;
	pthread_mutex_unlock(&philo->data->stop_mutex);
	return (stopped);
}
