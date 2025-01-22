/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razaccar <razaccar@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:30:56 by razaccar          #+#    #+#             */
/*   Updated: 2025/01/22 21:52:07 by razaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 10

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
}

int	main(int argc, char **argv)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*input;
	int		readlen;
	int		arglen;
	int		read_i;
	int		i;

	read_i = 1;
	input = NULL;
	readlen = read(0, buffer, BUFFER_SIZE);
	if (readlen < 0)
	{
		perror("Error: ");
		return (1);
	}
	while (readlen > 0)
	{
		buffer[BUFFER_SIZE] = 0;
		input = realloc(input, (read_i++ * BUFFER_SIZE) + 1);
		if (!input)
		{
			perror("Error: ");
			return (1);
		}
		i = 0;
		while (buffer[i])
		{
			input[ft_strlen(input) + i] = buffer[i];
			i++;
		}
		input[ft_strlen(input) + i] = 0;
		readlen = read(0, buffer, BUFFER_SIZE);
	}
	i = 0;
	printf("%s\n", input);
	while (i < ft_strlen(input))
	{
		if (!ft_strncmp(input + i, argv[1], ft_strlen(argv[1])))
		{
			arglen = ft_strlen(argv[1]);
			i += arglen;
			while (arglen--)
				printf("*");				
		}
		else
			printf("%c", input[i++]);
	}
	return (0);
}
