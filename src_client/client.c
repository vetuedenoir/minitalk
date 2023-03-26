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

int	g_pidx = 0;

void	reponse(int num, siginfo_t *info, void *x)
{
	(void) x;
	if (info->si_pid != g_pidx)
		return ;
	if (num == SIGUSR1)
		g_pidx = 0;
	else if (num == SIGUSR2)
		g_pidx = -1;
}

void	wait(void)
{
	int	t;

	t = 1;
	while (g_pidx == -1)
	{
		if (t == 1)
			write(1, "En attente du serveur ", 22);
		sleep(t - (t - 1));
		t++;
		write(1, ". ", 2);
		if (t == 30)
		{
			write(1, "\nLe serveur ne repond pas\n", 26);
			exit (0);
		}
	}
}


void	ft_one_by_one(int pid, char c)
{
	int	i;
	int	x;
	int	r;

	i = 7;
	x = 0;
	while (i >= 0)
	{
		g_pidx = pid;
		r = c >> i;
		if (r & 1)	// si le bit est a 1
		{
			if (kill(pid, SIGUSR1))
			{
				write(1, "Wrong PID\n", 10);
				exit (0);
			}
		}
		else			// si le bit est a 0
		{
			if (kill(pid, SIGUSR2))
			{
				write(1, "Wrong PID\n", 10);
				exit (0);
			}
		}
		i--;
		while (g_pidx == pid)
			;
		if (g_pidx == -1)
			wait();
		//ft_printf("pidx = %d, ", g_pidx);
	}
}

void	ft_send(int pid, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_one_by_one(pid, str[i]);
		i++;
	}
	ft_one_by_one(pid, str[i]);
	ft_putstr_fd("tout envoyer", 1);
	
}

int	main(int argc, char *argv[])
{
	int	pid;
	struct	sigaction ba;

	if (argc != 3)
		exit (0);
	ft_memset(&ba, 0, sizeof(struct sigaction));
	ba.sa_sigaction = reponse;
	ba.sa_flags = SA_SIGINFO;
	pid = ft_atoi(argv[1]);
	if (pid == -1 || pid == 0)
		exit(0);
	g_pidx = pid;
	sigaction(SIGUSR1, &ba, NULL);
	sigaction(SIGUSR2, &ba, NULL);
	ft_send(pid, argv[2]);
	return (1);
}
