/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:42:19 by dcarassi          #+#    #+#             */
/*   Updated: 2023/04/18 18:42:20 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int main (int argc, char **argv)
{
    t_rules *rules;
    int     i;

	rules = (t_rules *)malloc(sizeof(t_rules));
    if (argc < 5 || argc > 6)
        print_std_error(1);
    if (init_philos(rules, argv))
        print_std_error(2);
    i = -1;
    while (++i < rules->num_philo)
    {
        rules->parent = fork();
        if (!rules->parent)
        {
            rules->philo.id = i + 1;
            break ;
        }
    }
    if (!rules->parent)
        start_child_process(rules);
    start_parent_process(rules);
    free (rules);
    return (0);
}