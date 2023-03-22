/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:29:11 by kscordel          #+#    #+#             */
/*   Updated: 2023/03/21 16:13:52 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/serveur.h"

void	ft_action(int num, siginfo_t *info, void *p)
{
	int	pid;

	pid = info->si_pid;
	if (num == SIGUSR1)
	{
		write(1, "0\n", 2);
		kill(pid, SIGUSR1);
	}
	else if (num == SIGUSR2)
	{
		write(1, "1\n", 2);
		kill(pid, SIGUSR2);
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_sigaction = ft_action;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("%d\n",getpid());
	while (1)
	{}
	return (1);
}
