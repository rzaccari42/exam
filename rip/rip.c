/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razaccar <razaccar@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:50:58 by razaccar          #+#    #+#             */
/*   Updated: 2025/01/22 19:08:20 by razaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_balanced(const char *str)
{
    int balance;

	balance = 0;
    while (*str)
	{
        if (*str == '(')
			balance++;
        if (*str == ')')
			balance--;
        if (balance < 0)
			return 0;
        str++;
    }
    return (balance == 0);
}

int count_pairs(const char *str)
{
	int	pairs;
    int balance;

	pairs = 0;
	balance = 0;
    while (*str)
	{
        if (*str == '(')
			balance++;
        if (*str == ')' && balance > 0)
		{
			balance--;
			pairs++;
		}
        str++;
    }
    return (pairs);
}

void rip(const char *in, char *out, int len, int i, int j, int max_pairs)
{
    if (i == len)
	{
        out[j] = '\0';
        if (is_balanced(out) && count_pairs(out) == max_pairs)
            printf("%s\n", out);
        return;
    }
    if (in[i] == '(' || in[i] == ')')
	{
        out[j] = in[i];
        rip(in, out, len, i + 1, j + 1, max_pairs);
        out[j] = ' ';
        rip(in, out, len, i + 1, j + 1, max_pairs);
    } 
}

int main(int ac, char **av)
{
	char	*out;
	int		len;

    if (ac != 2)
        return (1);
    len = strlen(av[1]);
    out = (char *)malloc(len + 1);
    if (!out)
        return 1;
    rip(av[1], out, len, 0, 0, count_pairs(av[1]));
    free(out);
    return 0;
}
