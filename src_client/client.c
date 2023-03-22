/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:36:13 by kscordel          #+#    #+#             */
/*   Updated: 2023/03/21 13:38:43 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/client.h"

void	reponse(int num)
{
	if (num == SIGUSR1)
		ft_putstr_fd("SIGUSR1 a bien ete recu", 1);	
	else if (num == SIGUSR2)
		ft_putstr_fd("SIGUSR2 a bien ete recu", 1);
	exit(0);	
}

int	main(int argc, char *argv[])
{
	int	pid;
	int	action;
	struct	sigaction sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = reponse;
	pid = 0;
	action = 0;
	if (argc != 3)
		exit(0);
	pid = ft_atoi(argv[1]);
	if (pid == -1 || pid == 0)
		exit(0);
	action = ft_atoi(argv[2]);
	if (action == 1)
		kill(pid, SIGUSR1);
	else if (action == 2)
		kill(pid, SIGUSR2);
	else
		exit(0);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{}
	return (1);
}
