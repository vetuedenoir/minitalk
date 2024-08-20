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

char	*ft_resize(char **str, int *size, char c, int *i)
{
	char	*buf;

	*size = *size + 100;
	buf = malloc(sizeof(char) * (*size + 1));
	if (buf == NULL)
	{
		free(*str);
		return (NULL);
	}
	ft_memcpy(buf, *str, *i);
	free(*str);
	*str = NULL;
	buf[*i] = c;
	*i = *i + 1;
	return (buf);
}

int	ft_putsline(char *str, int	*i, int	*size, char c)
{
	if (c == '\n')
	{
		str[*i] = '\0';
		write(1, str, *i);
	}
	if (c == '\0')
	{
		write(1, str, *i - 1);
		write(1, "\n", 1);
	}
	*size = 100;
	*i = 0;
	if (c == '\n')
		return (1);
	else
		return (0);
}

int	ft_insert(char c, int pid)
{
	static char	*str;
	static int	i;
	static int	size = 100;

	if (str == NULL)
		str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (ft_erreur(pid));
	if (i < size)
		str[i++] = c;
	else
	{
		str = ft_resize(&str, &size, c, &i);
		if (str == NULL)
			return (ft_erreur(pid));
	}
	if (c == '\n' || c == '\0')
	{
		c = ft_putsline(str, &i, &size, c);
		free(str);
		str = NULL;
		return ((int)c);
	}
	return (1);
}

/*La fonction utilise des variables statiques pour stocker
les données qu'elle reçoit progressivement,
elle utilise également la fonction ft_check_id pour vérifier
si le signal provient bien du client dont le PID est stocké
dans la variable pidx.
Si le signal est SIGUSR2, cela signifie que le bit courant doit être mis à 0.
Pour cela, on utilise l'opérateur de bit à bit XOR ^
pour inverser le bit courant de c.
Le masque 0x80 >> i permet de sélectionner le bit courant.
Si le signal est SIGUSR1, cela signifie que le bit courant doit être mis à 1.
Pour cela, on utilise l'opérateur de bit à bit OR |
pour ajouter un 1 au bit courant de c.
Le masque 0x80 >> i permet de sélectionner le bit courant.
La variable c est un buffer qui stocke les bits reçus
avant de les concaténer en octets complets.*/

void	ft_reception(int num, siginfo_t *info, void *p)
{
	static int	i;
	static int	pidx;
	static char	c = 0xFF;

	(void) p;
	ft_check_id(&pidx, info->si_pid);
	if (pidx != info->si_pid)
		return ;
	if (num == SIGUSR2)
		c ^= 0x80 >> i;
	else if (num == SIGUSR1)
		c |= 0x80 >> i;
	i++;
	if (i == 8)
	{
		c = ft_insert(c, pidx);
		if (c == 0)
			pidx = 0;
		c = 0xFF;
		i = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

/*Ce programme est un serveur qui recoit une chaine de caractere et l affiche.
Il écoute en permanence les signaux SIGUSR1 et SIGUSR2
en utilisant la fonction sigaction().
Lorsqu'il reçoit un signal, il détermine l'ID du processus expéditeur
grâce à la structure siginfo_t et appelle la fonction ft_insert().
ft_insert() insère le caractère dans une chaîne de caractères
allouée dynamiquement en utilisant la fonction ft_resize()
pour agrandir la taille de la chaîne si nécessaire.
Lorsqu'un caractère de fin de ligne est reçu,
ft_insert() affiche la chaîne de caractères et renvoie 0
pour indiquer la fin de la transmission.
La communication est terminée lorsque le client reçoit cette valeur de retour*/

int	main(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_sigaction = ft_reception;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("%d\n", getpid());
	while (1)
	{
	}
	return (1);
}
