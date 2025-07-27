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

#include "philo.h"

int	ft_atoi_0(const char *str)
{
	long	nbr;
	int		i;

	nbr = 0;
	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		if (nbr > 2147483647)
			return (-1);
		i++;
	}
	if (str[i])
		return (-2);
	if (nbr == 0)
		return (-3);
	return ((int)nbr);
}

int	ft_atoi(const char *str)
{
	long	nbr;
	int		i;

	nbr = 0;
	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		if (nbr > 2147483647)
			return (-1);
		i++;
	}
	if (str[i] || nbr == 0)
		return (-1);
	return ((int)nbr);
}

int	check_0(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->nbr_philo)
		if (data->philos[i]->count_eat == -3)
			return (0);
	return (1);
}

int	check_dead(t_data *data, int *someone_died)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if ((get_time() - data->philos[i]->last_meal)
			> data->philos[i]->die_time)
		{
			pthread_mutex_lock(&data->print);
			*someone_died = 1;
			printf("%ld %d died\n", get_time() - data->philos[i]->start_time,
				data->philos[i]->id);
			pthread_mutex_unlock(&data->print);
			break_simulation(data);
			pthread_mutex_unlock(&data->meal_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	return (*someone_died);
}
