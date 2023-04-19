/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:41:21 by dcarassi          #+#    #+#             */
/*   Updated: 2023/04/18 18:41:22 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int  eating_part_two(t_philosopher *philo)
{
    if (!safe_mutex_unlock(philo, 2))
    {
        smart_sleep(philo->rules->time_eat, philo->rules);
        if (!safe_mutex_unlock(philo, 3))
        {
            if (!safe_mutex_unlock(philo, 0))
            {
                if (!check_if_lunch_is_over(philo->rules))
                {
                    if (!print_action(philo, SLEEPING))
                    {
                        smart_sleep(philo->rules->time_sleep, philo->rules);
                        if (!print_action(philo, THINKING))
                            return (0);
                    }
                }
            }
        }
    }
    return (1);
}

static int eating(t_philosopher *philo)
{
    if (!safe_mutex_lock(philo, 0))
    {
        if(!print_action(philo, TAKE_FORK))
        {
            if (!safe_mutex_lock(philo, 3))
            {
                if (!print_action(philo, TAKE_FORK))
                {
                    if (!safe_mutex_lock(philo, 2))
                    {
                        if (!print_action(philo, EATING))
                        {
                            philo->t_last_meal = timestamp();
                            philo->x_ate++;
                            if (!eating_part_two(philo))
                                return (0);
                        }
                    }
                }
            }
        }
    }
    return (1);
}

static void *philo_thread(void *void_philo)
{
    t_philosopher   *philo;

    philo = (t_philosopher *)void_philo;
    if (philo->id % 2)
        usleep(15000);
    while (!philo->rules->finished)
    {
        if (!print_action(philo, THINKING))
        {
            if (!eating(philo))
            {
                if (check_if_lunch_is_over(philo->rules))
                   break ;
            }
        }
    }
    return (NULL);
}

static void	death_checker(t_rules *rules, t_philosopher *philos)
{
	int i;

	while (!(rules->finished))
	{
		i = -1;
		while (++i < rules->nb_philo && !(rules->finished))
		{
			if (!safe_mutex_lock(&philos[i], 2))
            {
    			if (time_diff(philos[i].t_last_meal, timestamp()) > rules->time_death)
                {
                    if (!print_action(&philos[i], "died"))
                    {
                        rules->finished = 1;
                        break ;
                    }
                }
                if (!safe_mutex_unlock(&philos[i], 2))
                    usleep(100);
            }
        }
        if (check_if_lunch_is_over(rules) || rules->finished == 1)
            break ;
	}
}

int start_philosophing(t_rules *rules)
{
    int             i;
    t_philosopher   *philo;

    i = 0;
    philo = rules->philosophers;
    rules->first_timestamp = timestamp();
    while (i < rules->nb_philo)
    {
        if (pthread_create(&(philo[i].thread_id), NULL, philo_thread, &(philo[i])))
            return (1);
        philo[i].t_last_meal = timestamp();
        i++;
    }
    death_checker(rules, rules->philosophers);
    stop_philosophing(rules);
    return (0);
}