/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:47:42 by aharrass          #+#    #+#             */
/*   Updated: 2023/02/13 15:51:05 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int main()
{
	int id;
	struct timeval t0;
	struct timeval t1;
	
	gettimeofday(&t0, NULL);
	gettimeofday(&t1, NULL);
	
	printf("%d\n", ft_time(t0, t1));
	id = fork();
	if (id == 0)
	{
		gettimeofday(&t1, NULL);
		printf("%d\n", ft_time(t0, t1));
		sleep(3);
		exit(0);
	}
	wait(NULL);
}