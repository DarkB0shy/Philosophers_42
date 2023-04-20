/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:41:24 by dcarassi          #+#    #+#             */
/*   Updated: 2023/04/20 12:40:55 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	stop_philosophing(t_rules *rules)
{
	int				i;
	t_philosopher	*philos;

	philos = rules->philosophers;
	i = -1;
	while (++i < rules->nb_philo)
		pthread_mutex_destroy(&(rules->forks[i]));
	pthread_mutex_destroy(&(rules->writing));
	pthread_mutex_destroy(&(rules->meal_check));
}

int	print_action(t_philosopher *philo, char *str)
{
	if (!safe_mutex_lock(philo, 1))
	{
		if (!philo->rules->finished)
		{
			printf("%lli ", timestamp() - philo->rules->first_timestamp);
			printf("%i ", philo->id + 1);
			printf("%s\n", str);
			if (!safe_mutex_unlock(philo, 1))
				return (0);
		}
	}
	return (1);
}
