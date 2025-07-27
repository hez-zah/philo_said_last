/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sellyani <sellyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:00:00 by sellyani          #+#    #+#             */
/*   Updated: 2025/07/25 02:48:45 by sellyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_vide(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philo)
		if (data->philos[i])
			free(data->philos[i]);
	free(data->philos);
}

static int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_join(data->philos[i]->thread, NULL))
			return (1);
		i++;
	}
	if (pthread_join(data->monitor_thread, NULL))
		return (-1);
	return (0);
}

static void    clean_all(t_data *data)
{
	int		i;

	if (data->philos)
		philo_vide(data);
	if (data->forks)
	{
		i = 0;
		while (i < data->nbr_philo)
			pthread_mutex_destroy(&data->forks[i++]);
		free(data->forks);
	}
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->nbr_eat_mtx);
	pthread_mutex_destroy(&data->print);
}

int	main(int ac, char **av)
{
	t_data	data;

	if ((ac != 5 && ac != 6) || !init_all(&data, av))
        return (printf("Wrong arguments\n"), 1);
	if (!check_0(&data))
        return (1);
	if (!start_simulation(&data))
        return (printf("Thread error\n"), clean_all(&data), 1);
	join_threads(&data);
	clean_all(&data);
	return (0);
}
