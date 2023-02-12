/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:19:04 by aharrass          #+#    #+#             */
/*   Updated: 2023/02/12 09:44:39 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	initializer(t_var *var, t_philo **philo, sem_t *forks)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * var->n_philo);
	if (!philo)
		exit(1);
	sem_unlink("forks");
	var->ph_id = malloc(sizeof(int) * var->n_philo);
	if (!var->ph_id)
		exit(1);
	while (i < var->n_philo)
	{
		(*philo)[i].var = var;
		(*philo)[i].id = i + 1;
		(*philo)[i].fork_pile = forks;
		i++;
	}
	var->is_alive = 1;
	var->av_philo = var->n_philo;
	return ;
}

void	manager(t_var *var)
{
	int		i;
	t_philo	*philo;
	sem_t	*forks;

	i = 0;
	philo = 0;
	forks = sem_open("forks", O_CREAT, 0660, var->n_philo);
	if (forks == SEM_FAILED)
		exit(1);
	initializer(var, &philo, forks);
	while (i < var->n_philo)
	{
		var->ph_id[i] = fork();
		if (var->ph_id[i] == 0)
			(printf("hello\n"), exit(0));
		else
			i++;
	}
	while (1)
	{
		waitpid(-1, NULL, 0);
		exit(0);
	}
}

int	main(int ac, char **av)
{
	t_var	var;

	if (ac < 5 || ac > 6)
	{
		printf("Error: Invalid arguments");
		return (1);
	}
	if (is_valid(av))
		return (2);
	var.n_eat = -1;
	var.n_philo = ft_atoi(av[1]);
	var.t_die = ft_atoi(av[2]);
	var.t_eat = ft_atoi(av[3]);
	var.t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		var.n_eat = ft_atoi(av[5]);
	if (var.n_philo <= 0 || var.t_die <= 0 || var.t_eat <= 0
		|| var.t_sleep <= 0)
		return (3);
	manager(&var);
}
