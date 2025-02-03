/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:38:06 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/31 19:35:47 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void signal_handler(int signal)
{
    static char c = 0;
    static int i = 7;
    static char buffer[100000];
    static int j = 0;
    
    if (signal == SIGUSR1)
    {
        c += (1 << i);
    }
    i--;
    if (i < 0)
    {        
        buffer[j] = c;
        i = 7;
        j++;
        if (c == '\0')
        {
            buffer[j] = '\0';
            ft_printf("%s\n", buffer);
            j = 0;
        }
        c = 0;
    }
}

int main (void)
{
    struct sigaction sa;
    
    sa.sa_handler = &signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    ft_printf("Server pid: %d\n", getpid());

    while (1)
        pause();
        
    return (0);
}