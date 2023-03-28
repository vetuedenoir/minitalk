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
	static int	pid;

	if (pid == 0)
		pid = g_pidx;
	(void) x;
	if (info->si_pid != pid)
		return ;
	if (num == SIGUSR1)
		g_pidx = 0;
	else if (num == SIGUSR2)
		g_pidx = -1;
}

void	ft_bitgo(int pid, char c, int i)
{
	int	r;

	r = c >> i;
	if (r & 1)
	{
		if (kill(pid, SIGUSR1))
		{
			write(1, "Wrong PID\n", 10);
			exit (0);
		}
	}
	else
	{
		if (kill(pid, SIGUSR2))
		{
			write(1, "Wrong PID\n", 10);
			exit (0);
		}
	}
}

void	ft_one_by_one(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		g_pidx = pid;
		ft_bitgo(pid, c, i);
		i--;
		while (g_pidx == pid)
			;
		if (g_pidx == -1)
		{
			write(1, "Server unavailable\n", 19);
			exit (0);
		}	
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
	ft_putstr_fd("Everything send\n", 1);
}

int	main(int argc, char *argv[])
{
	int					pid;
	struct sigaction	ba;

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
