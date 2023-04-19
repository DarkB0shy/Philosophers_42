/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:42:25 by dcarassi          #+#    #+#             */
/*   Updated: 2023/04/18 18:42:26 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int sem_print_action(t_rules *rules, char *str)
{
    if (!sem_wait(rules->sem_p))
    {
        printf("%lu %d %s", gap_time(rules->start), rules->philo.id, str);
        if (!sem_post(rules->sem_p))
            return (0);
    }
    return (1);
}

void	close_semaphores(t_rules *rules)
{
	if (!sem_close(rules->sem_f))
	{
		if (!sem_close(rules->sem_p))
		{
			if (!sem_unlink("/post"))
			{
				if (!sem_unlink("/forks"))
					exit(0);
			}
		}
	}
	print_std_error(3);
}

int	check_if_dead(t_rules *rules)
{
	if (gap_time(rules->philo.start_sleep) >= rules->time_to_die)
	{
		if (!sem_print_action(rules, "died"))
		{
			close_semaphores(rules);
			exit(0);
		}
	}
	return (0);
}

int	sem_take_fork(t_rules *rules)
{
	if (!sem_wait(rules->sem_f))
	{
		if (!sem_print_action(rules, "has taken a fork"))
		{
			if (!check_if_dead(rules))
				return (0);
		}
	}
	return (1);
}

int	sem_put_back_forks(t_rules *rules)
{
	if (!sem_post(rules->sem_f))
	{
		if (!sem_post(rules->sem_f))
		{
			return (0);
		}
	}
	return (1);
}