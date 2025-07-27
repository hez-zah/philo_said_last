/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sellyani <sellyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:00:00 by sellyani          #+#    #+#             */
/*   Updated: 2025/07/25 02:48:45 by sellyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	variable_stop(t_data *data)
{
	int	breakk;

	pthread_mutex_lock(&data->stop_mutex);
	breakk = data->stop;
	pthread_mutex_unlock(&data->stop_mutex);
	return (breakk);
}

size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}