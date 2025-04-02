/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:38:06 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/02/27 18:27:16 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	write_message(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

void	signal_to_string(int signal, pid_t pid)
{
	static char	c = 0;
	static int	i = 7;
	static char	buffer[200000];
	static int	j = 0;

	if (signal == SIGUSR2)
		c += (1 << i);
	if (--i < 0)
	{
		buffer[j] = c;
		i = 7;
		j++;
		if (c == '\0')
		{
			write_message(buffer);
			if (kill(pid, SIGUSR2) == -1)
				exit(ft_printf("Failed to send SIGUR2\n") || EXIT_FAILURE);
			j = 0;
		}
		c = 0;
	}
	if (kill(pid, SIGUSR1) == -1)
		exit(ft_printf("Failed to send SIGUR1\n") || EXIT_FAILURE);
}

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static pid_t	pid;

	(void)context;
	if (info->si_pid)
		pid = info->si_pid;
	if (signal == SIGUSR1 || signal == SIGUSR2)
		signal_to_string(signal, pid);
	else
		write(1, "Unknown signal", 14);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &signal_handler;
	if (sigemptyset(&sa.sa_mask) == -1)
		exit(EXIT_FAILURE);
	if (sigaddset(&sa.sa_mask, SIGUSR1) == -1)
		exit(EXIT_FAILURE);
	if (sigaddset(&sa.sa_mask, SIGUSR2) == -1)
		exit(EXIT_FAILURE);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		exit(EXIT_FAILURE);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		exit(EXIT_FAILURE);
	ft_printf("Server pid: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
