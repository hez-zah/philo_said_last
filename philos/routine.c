/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sellyani <sellyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:00:00 by sellyani          #+#    #+#             */
/*   Updated: 2025/07/25 02:48:45 by sellyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleeping(t_philo *philo)
{
	if (variable_stop(philo->data))
		return ;
	do_some(philo, "is sleeping");
	my_sleep(philo->sleep_time);
}

void	ft_eating(t_philo *philo)
{
	long	now;

	if (variable_stop(philo->data))
		return ;
	now = get_time();
	do_some(philo, "is eating");
	///////nbr_eat
	pthread_mutex_lock(&philo->data->nbr_eat_mtx);
	if (philo->count_eat)
		philo->count_eat--;
	pthread_mutex_unlock(&philo->data->nbr_eat_mtx);
	/////last_meal
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal = now;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	////
	my_sleep(philo->eat_time);
}

int		routine_aid(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->id % philo->data->nbr_philo]);
	if (variable_stop(philo->data))
	{
		pthread_mutex_unlock(&philo->data->forks[philo->id % philo->data->nbr_philo]);
		pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
		return (0);
	}
	do_some(philo, "has taken a fork");
	do_some(philo, "has taken a fork");
	ft_eating(philo);
	pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
	pthread_mutex_unlock(&philo->data->forks[philo->id % philo->data->nbr_philo]);
	if (variable_stop(philo->data) || finish_philos(philo->data))
		return (0);
	ft_sleeping(philo);
	if (finish_philos(philo->data) || variable_stop(philo->data))
		return (0);
	return (1);
}

void	ft_thinking(t_philo *philo)
{
	if (variable_stop(philo->data))
		return ;
	do_some(philo, "is thinking");
}
