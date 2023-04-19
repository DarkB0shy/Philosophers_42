/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:41:13 by dcarassi          #+#    #+#             */
/*   Updated: 2023/04/18 18:41:14 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main (int argc, char **argv)
{
    t_rules rules;
    int     ret;

    ret = 0;
    if (argc != 5 && argc != 6)
        return (print_standard_error("wrong N of arguments"));
    if ((ret = init_philo(&rules, argv)))
        return (print_error(ret));
    if (start_philosophing(&rules))
        return (print_standard_error("error while creating the threads"));
    return (0);

}