/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:11:32 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/31 19:29:02 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

//take string and convert it to binary
//send binary to server
static void send_signal(char *s, int served_pid)
{
    int i = 0; 
    while (s[i])
    {
        if (s[i] == '1')
            kill(served_pid, SIGUSR1);
        else if (s[i] == '0')
            kill(served_pid, SIGUSR2);
        i++;
        usleep(500);
    }
}

static void binary_convert(int value, int server_pid)
{
    int max = 128;
    int i = 0;
    char s[8];
    
    ft_printf("\nog: %d\n", value);
    while (i < 8)
    {
        if (value >= max)
        {
            value -= max;
            s[i] = '1';
        }
        else
            s[i] = '0';
        max /= 2;
        i++;
    }
    s[i] = '\0';
    ft_printf("binary: %s\n", s);
    send_signal(s, server_pid);
}

// static void send_signal2(char c, int served_pid)
// {
//     int i = 0; 
//     while (i < 8)
//     {
//         if (s[i] == '1')
//             kill(served_pid, SIGUSR1);
//         else if (s[i] == '0')
//             kill(served_pid, SIGUSR2);
//         i++;
//         usleep(500);
//     }
// }

static void ascii_convert(char *s, int server_pid)
{
    int i = 0;
    int ascii = 0;
    char c = 0;
    
    while (s[i] != '\0')
    {
        ascii = s[i];
        c = s[i];
        // send_signal2(c, server_pid);
        binary_convert(ascii, server_pid);
        i++;
    }
    binary_convert(0, server_pid);
    ft_printf("\n");
}

int main (int argv, char *argc[])
{
    int server_pid = 0;
    
    if (argv == 3)
    {
        server_pid = ft_atoi(argc[1]);
        if (!server_pid)
        {
            ft_printf("Wrong <PID>");
            return (0);
        }
        ascii_convert(argc[2], server_pid);

    }
    else
    {
        ft_printf("Incorrect argument amount.\n");
        ft_printf("Enter arguments: ./client <PID> <STRING>.\n");
    }
    return (0);
}