/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:42:11 by dcarassi          #+#    #+#             */
/*   Updated: 2023/04/18 18:42:12 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start_parent_process(t_rules *rules)
{
	int	cnt_m;
	int	state;

	cnt_m = 0;
	while (waitpid(0, &state, 0))
	{
		if (((state >> 8) & 0x0000000ff) == 0)
		{
			kill(0, SIGKILL);
			break ;
		}
		if (((state >> 8) & 0x0000000ff) == 1)
		{
			cnt_m++;
			if (cnt_m == rules->num_philo)
				break ;
		}
	}
}

unsigned long	gap_time(struct timeval v)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (((t.tv_sec * 1000) + (t.tv_usec / 1000))
		- ((v.tv_sec * 1000) + (v.tv_usec / 1000)));
}

static int	sleeping(t_rules *rules)
{
	if (gap_time(rules->philo.start_eat) >= rules->time_to_eat)
	{
		rules->philo.eat_times++;
		if (rules->philo.eat_times == rules->meal_cnt)
			close_semaphores(rules);
		if (!sem_put_back_forks(rules))
		{
			if (!sem_print_action(rules, "is sleeping"))
			{
				gettimeofday(&rules->philo.start_sleep, NULL);
				if (!check_if_dead(rules))
				{
					if (gap_time(rules->philo.start_sleep) >= rules->time_to_sleep)
					{
						return (thinking(rules));
					}
				}
			}
		}
	}
	return (1);
}

int	thinking(t_rules *rules)
{
	if (!check_if_dead(rules))
	{
		if (!sem_print_action(rules, "is thinking"))
		{
			if (!check_if_dead(rules))
			{
				if (!sem_take_fork(rules))
				{
					if (!sem_take_fork(rules))
					{
						if (!sem_print_action(rules, "is eating"))
						{
							if (!check_if_dead(rules))
							{
								gettimeofday(&rules->philo.start_eat, NULL);
								return (sleeping(rules));
							}
						}
					}
				}
			}
		}
	}
	return (1);
}

void	start_child_process(t_rules *rules)
{
	int	loop;

	loop = 0;
    gettimeofday(&rules->philo.start_sleep, NULL);
    gettimeofday(&rules->start, NULL);
    while (!loop)
    {
		if (!thinking(rules))
			loop = 1;
    }
}