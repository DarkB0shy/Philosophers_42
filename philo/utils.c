/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:41:31 by dcarassi          #+#    #+#             */
/*   Updated: 2023/04/20 15:08:28 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	smart_sleep(long long time, t_rules *rules)
{
	long long	i;

	i = timestamp();
	while (!(rules->finished))
	{
		if (time_diff(i, timestamp()) >= time)
			break ;
		usleep(50);
	}
}

int	check_if_lunch_is_over(t_philosopher *philo)
{
	t_rules	*rules;
	int		i;
	int		temp;

	rules = philo->rules;
	if (!rules->nb_eat)
		return (0);
	temp = 0;
	i = rules->nb_philo;
	while (--i >= 0)
	{
		if (rules->philosophers[i].x_ate == rules->nb_eat)
			temp++;
		else
			break ;
	}
	if (temp == rules->nb_philo - 1)
		return (1);
	else
		return (0);
}
