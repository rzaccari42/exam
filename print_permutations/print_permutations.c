/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_permutations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razaccar <razaccar@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 03:54:19 by razaccar          #+#    #+#             */
/*   Updated: 2025/01/22 18:14:42 by razaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char	*remdup(char *str)
{
	char	*letters;
	int		i;

	letters = malloc(strlen(str));
	if (!letters)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (strchr(letters, *str))
			str++;
		else
			letters[i++] = *str++;
	}
	return (letters);
}

void	swap(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

void	permute(char *letters, int level)
{
	int	depth;
	int	i;
	
	depth = strlen(letters);
	if (level == depth)
		printf("%s\n", letters);	
	i = level;
	while (i < depth)
	{
		swap(letters + level, letters + i);
		permute(letters, level + 1);
		swap(letters + i, letters + level);
		i++;	
	}
}

int	main(int argc, char **argv)
{
	char	*letters;

	if (argc != 2)
	{
		printf("Usage: %s <string>\n", argv[0]);
		return (1);
	}
	letters = remdup(argv[1]);
	permute(letters, 0);
	return (0);
}
