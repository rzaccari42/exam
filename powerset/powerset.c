/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razaccar <razaccar@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 23:41:13 by razaccar          #+#    #+#             */
/*   Updated: 2025/01/27 06:37:45 by razaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	print_subset(char **subset, int size)
{
	int	i;
    int first;

	first = 0;
	i = 0;
    while (i < size)
	{
        if (subset[i][0] != '0')
		{
            if (!first)
                printf(" ");
            printf("%s", subset[i]);
            first = 0;
        }
        i++;
    }
    printf("\n");
}

int	getsum(char **numbers, int size)
{
	int	sum;
	int	i;

	sum = 0;
	i = 0;
	while (i < size)
		sum += atoi(numbers[i++]);
	return (sum);
}

void	powerset(int sum, char **set, char **subset, int size, int i)
{
	if (i == size)
	{
		if (getsum(subset, size) == sum)
			print_subset(subset, size);
		return ;
	}
	subset[i] = set[i];
	powerset(sum, set, subset, size, i + 1);
	subset[i] = "0";
	powerset(sum, set, subset, size, i + 1);
}

int	main(int ac, char **av)
{
	char	**subset;
	int		sum;
	int		i;

	if (ac < 4)
	{
		printf("Error: a set must contain at least 3 numbers.");
		return (1);
	}
	subset = malloc((ac - 1) * sizeof(char*));
	if (!subset)
		return (1);
	i = 0;
	while (i < ac - 2)
	{
		subset[i] = malloc(11 * sizeof(char));
		if (!subset[i])
		{
			while (--i)
				free(subset[i]);
			free(subset);
			return (1);
		}
		subset[i][10] = 0;
		i++;
	}
	subset[ac - 2] = NULL;
	sum = atoi(av[1]);
	powerset(sum, av + 2, subset, ac - 2, 0);
}
