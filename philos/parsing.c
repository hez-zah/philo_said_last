/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sellyani <sellyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:00:00 by sellyani          #+#    #+#             */
/*   Updated: 2025/07/25 02:48:45 by sellyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"///

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->print, NULL))
		return (0);
	if (pthread_mutex_init(&data->nbr_eat_mtx, NULL))
		return (0);
	if (pthread_mutex_init(&data->meal_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&data->stop_mutex, NULL))
		return (0);
	return (1);
}

static int    check_args(t_data *data, char **av)
{
    if (data->nbr_philo < 1 || data->nbr_philo > 200)
        return (0);
    if (ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60)
        return (0);
    return (1);
}

t_philo	*new_philo(t_philo *philo, char **av)
{
	if (!get_time())
		return (NULL);
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->die_time = ft_atoi(av[2]);
	philo->eat_time = ft_atoi(av[3]);
	philo->sleep_time = ft_atoi(av[4]);
	philo->start_time = get_time();
	philo->last_meal = philo->start_time;
	if (av[5])
		philo->count_eat = ft_atoi_0(av[5]);
	else
		philo->count_eat = -1;
	return (philo);
}

int	init_philosophers(t_data *data, char **argv)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < data->nbr_philo)
	{
		philo = new_philo(data->philos[i], argv);
		if (!philo || philo->count_eat == -2)
			return (0);
		data->philos[i] = philo;
		// free(philo);
		data->philos[i]->id = i + 1;
		data->philos[i]->data = data;
		i++;
	}
	return (1);
}

int	init_all(t_data *data, char **av)
{
    data->nbr_philo = ft_atoi(av[1]);
    data->stop = 0;
    if (!check_args(data, av))
        return (0);
    data->philos = malloc(sizeof(t_philo) * data->nbr_philo);
    if (!data->philos)
        return (0);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_philo);
    if (!data->forks)
        return (0);
	if (!init_mutexes(data) || !init_philosophers(data, av))
		return (0);
	return (1);
}
