/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/02 19:05:18 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


void	ft_init_table(t_table *table, char **argv)
{
	table->philo_nb = ft_atoi(argv[1]);
	table->fork_nb = table->philo_nb;
	table->time_before_dying = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
//	table->program_start = ft_get_current_time();
	dprintf(2, " Philo num:\t\t%d\n", table->philo_nb);
	dprintf(2, " Fork num:\t\t%d\n", table->philo_nb);
	dprintf(2, " Time before dying:\t%zu\n", table->time_before_dying);
	dprintf(2, " Time to eat:\t\t%zu\n", table->time_to_eat);
	dprintf(2, " Time to sleep:\t\t%zu\n", table->time_to_sleep);
//	dprintf(2, " Program start:\t\t%zu\n", table->program_start);
}

void	ft_init_forks(t_table *table)
{
	int	i;

	i = 0;
	table->fork_tab = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * table->fork_nb);
	if (!table->fork_tab)
		return ;
	while (i < table->fork_nb)
	{
		table->fork_tab[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		// check if malloc fail
//		dprintf(2, "table->fork_tab\t\t-> %d\n", i);
		i += 1;
	}
}

// INIT STATE
void	ft_init_philos(t_table *table)
{
	int	i;

	i = 0;
	table->philo_tab = (t_philo **)malloc(sizeof(t_philo *) * table->philo_nb);
	if (!table->philo_tab)
		return ;
	while (i < table->philo_nb)
	{
		table->philo_tab[i] = (t_philo *)malloc(sizeof(t_philo));
		// check if malloc fail
		// if (!table->philo_tab[i])
		//	ft_free_tab(table, i);
		table->philo_tab[i]->table = table; 
//		table->philo_tab[i]->table->program_start = ft_get_current_time(); 
//		table->philo_tab[i]->is_dead = 0; 
//		table->philo_tab[i]->program_start = ft_get_current_time(); 
		if (i == table->philo_nb - 1)
		{
			table->philo_tab[i]->left_f = table->fork_tab[i];
//			dprintf(2, "philo %d a la fourchette %d comme fourchette gauche ", i, i);
			table->philo_tab[i]->right_f = table->fork_tab[0];
//			dprintf(2, "et la fourchette 0 comme fourchette droite\n");
		}
		else
		{
			table->philo_tab[i]->right_f = table->fork_tab[i];
//			dprintf(2, "philo %d a la fourchette %d comme fourchette droite ", i, i);
			table->philo_tab[i]->left_f = table->fork_tab[i + 1];
//			dprintf(2, "et la fourchette %d comme fourchette gauche\n", i + 1);
		}
		i += 1;
	}
}

void	ft_init_threads(t_table *table)
{
	int	i;

	i = 0;
	table->thread_id = (pthread_t *)malloc(sizeof(pthread_t) * table->philo_nb);
	if (!table->thread_id)
		return ;
	// Mutex pour attendre la creation des threads
///* -----------------------------------------------------------------------------
	// Pourquoi j'ai fait ça ?
	while (i < table->philo_nb)
	{
		pthread_mutex_init(table->fork_tab[i], NULL);
		pthread_mutex_init(&table->message, NULL);
		pthread_mutex_init(&table->dead_lock, NULL);
		i += 1;
	}
	i = 0;
//----------------------------------------------------------------------------- */
//	pthread_mutex_init(&table->message, NULL);
//	pthread_mutex_init(&table->philo_tab[i]->dead_lock, NULL);
	while (i < table->philo_nb)
	{
		table->philo_tab[i]->table->program_start = ft_get_current_time(); 
//		pthread_mutex_init(table->philo_tab[i]->dead_lock, NULL);
		if (pthread_create(&(table->thread_id[i]), NULL, &ft_routine, &(table->philo_tab[i])) != 0)
		{
			dprintf(2, "Attention tout le monde, je fail !\n");
		// Attention, si le thread 3 fail, il faut join les threads crees et tout arreter
			return ;
		}
		i += 1;	
	} 
	// Unlock mutex 
	i = 0;
	while (i < table->philo_nb)
	{
		if (pthread_join(table->thread_id[i], NULL) != 0)
			return ;
		i += 1;
	}
}
