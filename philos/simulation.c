/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   similation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sellyani <sellyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:00:00 by sellyani          #+#    #+#             */
/*   Updated: 2025/07/25 02:48:45 by sellyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*moniteur(void *arg)
{
	t_data	*data;
	int	someone_died;

	someone_died = 0;
	data = (t_data *)arg;
	if (data->nbr_philo == 1)
		return (NULL);
	while (!variable_stop(data))
	{
		if (finish_philos(data) || check_dead(data, &someone_died))
			break ;
		my_sleep(1);
	}
	return (NULL);
}

void	print_status(t_philo *philo, char *msg)
{
	long	now;

	if (break_simulation_aid(philo))
		return ;
	pthread_mutex_lock(&philo->data->print);
	now = get_time() - philo->start_time;
	printf("%ld %d %s\n", now, philo->id + 1, msg);
	pthread_mutex_unlock(&philo->data->print);
}

void    one_philo(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->forks[0]);
    print_status(philo, "has taken a fork");
    my_sleep(philo->die_time);    // Changed from data->die_time
    print_status(philo, "died");
    pthread_mutex_unlock(&philo->data->forks[0]);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nbr_philo == 1)
		return (one_philo(philo), NULL);
	if (!(philo->id % 2))
		my_sleep(philo->eat_time);
	while (!variable_stop(philo->data))
	{
		if (finish_philos(philo->data) || variable_stop(philo->data))
			break ;
		pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
		if (variable_stop(philo->data))
		{
			pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
			break ;
		}
		if (!routine_aid(philo))
			break ;
		do_some(philo, "is thinking");
		ft_thinking(philo);
	}
	return (NULL);
}

int	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_create(&data->philos[i]->thread, NULL, &routine,
				data->philos[i]))
			return (0);
		i++;
	}
	if (pthread_create(&data->monitor_thread, NULL,
			&moniteur, data))
		return (0);
	return (1);
}
