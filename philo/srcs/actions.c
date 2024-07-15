/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/15 15:58:22 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_take_forks(t_table *table, t_philo **philo, int id)
{
	if (pthread_mutex_lock((*philo)->left_f) == 0)
//		ft_print_message("has taken a fork", table, philo, id);
		ft_print_message("has taken a fork", table, id);
	else // si la fourchette est occupee, je ne rentre pas dans le else parce que pthread ne retourne rien dans ce cas la, donc je reste coincee sur cette meme ligne
		printf("error\n");
	if (pthread_mutex_lock((*philo)->right_f) == 0)
	//	ft_print_message("has taken a fork", table, philo, id);
		ft_print_message("has taken a fork", table, id);
		//printf("%zu %d has taken a fork (right)\n", ft_usleep((*philo)->table->time_to_sleep), id);
//		printf("%d has taken a fork (left) \n", id);
	else
		printf("error\n");
}

void	ft_drop_forks(t_philo **philo)
{
	if (pthread_mutex_unlock((*philo)->right_f) != 0)
		printf("Error: right fork unlok failed\n");
	if (pthread_mutex_unlock((*philo)->left_f) != 0)
		printf("Error: right fork unlok failed\n");
}

void	ft_eat(t_table *table, t_philo **philo, int id)
{
	ft_take_forks(table, philo, id);
//	ft_print_message("is eating", table, philo, id);
	ft_print_message("is eating", table, id);
	ft_usleep((*philo)->table->time_to_eat);
	ft_drop_forks(philo);
}

void	ft_sleep(t_table *table, t_philo **philo, int id)
{
	//dprintf(2, "\t->%s\n", __func__);
	//ft_print_message("is sleeping", table, philo, id);
	ft_print_message("is sleeping", table, id);
	ft_usleep((*philo)->table->time_to_sleep);
//	printf("%d is sleeping 😴\n", id);
}

void	ft_think(t_table *table, t_philo **philo, int id)
{
	(void)philo;
	//ft_print_message("is thinking", table, philo, id);
	ft_print_message("is thinking", table, id);
}
