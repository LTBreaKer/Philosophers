/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:19:04 by aharrass          #+#    #+#             */
/*   Updated: 2023/02/16 18:17:22 by aharrass         ###   ########.fr       */
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
	(sem_unlink("forks"), sem_unlink("death_check"), sem_unlink("eat_check"));
	var->eat_check = sem_open("eat_check", O_CREAT, S_IRWXU, 1);
	var->death_check = sem_open("death_check", O_CREAT, S_IRWXU, 1);
	if (var->eat_check == SEM_FAILED || var->death_check == SEM_FAILED)
		exit(1);
	var->ph_id = malloc(sizeof(int) * var->n_philo);
	if (!var->ph_id)
		exit(1);
	while (i < var->n_philo)
	{
		(*philo)[i].eat_n = 0;
		(*philo)[i].var = var;
		(*philo)[i].id = i + 1;
		i++;
	}
	var->fork_pile = forks;
	var->is_alive = 1;
	var->av_philo = var->n_philo;
	return ;
}

void	*to_do(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->id % 2)
		usleep(1000);
	while (philo->var->is_alive)
	{
		ft_eat(philo);
		if (philo->var->n_eat != -1)
			philo->eat_n++;
		if (philo->eat_n == philo->var->n_eat)
			exit(0);
		sleepnthink(philo);
	}
	return (0);
}

void	philo_manage(t_philo *philo)
{
	pthread_t		ph;
	struct timeval	curr;

	gettimeofday(&philo->last_meal_time, NULL);
	pthread_create(&ph, NULL, to_do, philo);
	pthread_detach(ph);
	while (1)
	{
		gettimeofday(&curr, NULL);
		sem_wait(philo->var->death_check);
		if (ft_time(philo->last_meal_time, curr) > philo->var->t_die)
			(sem_post(philo->var->death_check), exit(philo->id));
		sem_post(philo->var->death_check);
	}
}

void	manager(t_var *var)
{
	int		i;
	t_philo	*philo;
	sem_t	*forks;

	i = 0;
	philo = 0;
	forks = sem_open("forks", O_CREAT, S_IRWXU, var->n_philo);
	if (forks == SEM_FAILED)
		exit(1);
	initializer(var, &philo, forks);
	gettimeofday(&var->start, NULL);
	while (i < var->n_philo)
	{
		var->ph_id[i] = fork();
		if (var->ph_id[i] == 0)
		{
			philo_manage(&philo[i]);
			exit(0);
		}
		i++;
	}
	ft_death(var);
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
