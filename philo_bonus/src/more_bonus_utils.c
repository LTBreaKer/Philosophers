/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_bonus_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:58:50 by aharrass          #+#    #+#             */
/*   Updated: 2023/02/19 23:59:22 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	ft_eat(t_philo *philo)
{
	sem_wait(philo->var->fork_pile);
	gettimeofday(&(philo->curr), NULL);
	printf("%5d %d has taken a fork\n", ft_time(philo->var->t0, philo->curr),
		philo->id);
	sem_wait(philo->var->fork_pile);
	gettimeofday(&(philo->curr), NULL);
	printf("%5d %d has taken a fork\n", ft_time(philo->var->t0, philo->curr),
		philo->id);
	sem_wait(philo->var->death_check);
	gettimeofday(&(philo->last_meal_time), NULL);
	gettimeofday(&(philo->curr), NULL);
	printf("%5d %d is eating\n", ft_time(philo->var->t0, philo->curr),
		philo->id);
	sem_post(philo->var->death_check);
	ft_wait(philo->var->t_eat);
	sem_post(philo->var->fork_pile);
	sem_post(philo->var->fork_pile);
}

void	sleepnthink(t_philo *philo)
{
	gettimeofday(&(philo->curr), NULL);
	printf("%5d %d is sleeping\n", ft_time(philo->var->t0, philo->curr),
		philo->id);
	ft_wait(philo->var->t_sleep);
	gettimeofday(&(philo->curr), NULL);
	printf("%5d %d is thinking\n", ft_time(philo->var->t0, philo->curr),
		philo->id);
}

void	ft_death(t_var *var)
{
	int	i;
	int	status;

	i = -1;
	waitpid(-1, &status, 0);
	if (WEXITSTATUS(status) == 0)
	{
		while (i++ < var->n_philo)
		{
			waitpid(-1, &status, 0);
			if (WEXITSTATUS(status) != 0)
				break ;
		}
	}
	if (WEXITSTATUS(status))
	{
		i = 0;
		gettimeofday(&var->tf, NULL);
		while (i < var->n_philo)
			kill(var->ph_id[i++], SIGKILL);
		printf("%5d %d died\n", ft_time(var->t0, var->tf), WEXITSTATUS(status));
	}
	(sem_close(var->fork_pile), sem_close(var->eat_check));
	sem_close(var->death_check);
	exit(0);
}
