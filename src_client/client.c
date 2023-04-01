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

/*Cette fonction et appele a la reception d un signaux.
elle verifie en 1 er temps que c est le serveur qui lui envoie un signaux
si le signaux et SIGUSR1 tout va bien sinon
le serveur a eu une erreur ou est occupe.
La variable global est modifier en consequence
 pour transmettre l information.*/

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

/*La fonction ft_bitgo est une fonction qui envoie un bit spécifique
 au serveur en utilisant les signaux SIGUSR1 et SIGUSR2.
La fonction prend en entrée un caractère (c) et un indice (i).
Elle effectue un décalage vers la droite de i bits sur le caractère c
et envoie le signal SIGUSR1 si le bit le plus à droite est un 1,
sinon elle envoie le signal SIGUSR2.
La fonction gère également les erreurs en vérifiant si le serveur existe
avant d'envoyer un signal et en affichant un message d'erreur
si l'ID du serveur est incorrect. */

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

/*La fonction ft_one_by_one envoie chaque bit d'un caractère c au serveur
en utilisant la fonction ft_bitgo.
La fonction commence par initialiser la variable i à 7,
le bit le plus à gauche du caractère c, et boucle jusqu'à ce que i soit égal à 0.
À chaque itération, la fonction appelle ft_bitgo
pour envoyer le bit à la position i.
La variable globale g_pidx est utilisée pour vérifier
si la réponse du processus cible a été reçue.
La fonction attend la réponse avant de passer à l'envoi du bit suivant.
Si le processus cible n'envoie pas de réponse
 ou s'il envoie une réponse incorrecte (SIGUSR2),
la fonction affiche un message d'erreur en fonction
de la valeur de index et termine le programme*/

void	ft_one_by_one(int pid, char c, int index)
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
			if ((index == 0 && i < 7) || index > 0)
				write(1, "Serveur crash\n", 14);
			write(1, "Server unavailable\n", 19);
			exit (0);
		}	
	}
}

/*Parcour la chaine pour l envoyer bits per bits*/

void	ft_send(int pid, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_one_by_one(pid, str[i], i);
		i++;
	}
	ft_one_by_one(pid, str[i], i);
	ft_putstr_fd("Everything send\n", 1);
}

/*La fonction main prend deux arguments:
l'ID du processus cible et le message à envoyer.
Elle vérifie le nombre d'arguments,
 convertit l'ID en entier et initialise un gestionnaire de signaux.
Elle associe les signaux SIGUSR1 et SIGUSR2 à la fonction reponse
et appelle la fonction ft_send pour envoyer le message
en utilisant des signaux.*/

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
