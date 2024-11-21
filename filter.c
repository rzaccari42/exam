/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razaccar <razaccar@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:23:11 by razaccar          #+#    #+#             */
/*   Updated: 2024/11/21 18:53:24 by razaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1

size_t ft_strlen(char *str)
{	
	size_t i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t i = 0;
	size_t s1len;
	size_t s2len;
	char	*str;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	str = realloc(s1, s1len + s2len  + 1);
	while (*s2)
	{
		str[s1len + i] = *s2;
		i++;
		s2++;
	}
	str[s1len + s2len] = 0;
	return (str);
}

char	*get_input(char *input, char *buffer, int *stop)
{
	size_t	read_len;

	while (1)
	{
		if (input && strchr(input, '\n'))
			break ;
		read_len = read(0, buffer, BUFFER_SIZE);
		buffer[read_len] = 0;
		if (read_len == 0)
		{
			*stop = 1;
			break ;
		}
		input = ft_strjoin(input, buffer);
	}
	return (input);
}

int	main(int argc, char **argv)
{
	size_t	arglen;
	char	_buffer[BUFFER_SIZE + 1];
	int	stop;
	char	*buffer;
	buffer = NULL;
	(void)argc;
	arglen = ft_strlen(argv[1]);
	stop = 0;
	while (1)
	{
		buffer = get_input(buffer, _buffer, &stop);
		if (stop)
			break;
		size_t i = 0;
		while (i < ft_strlen(buffer))
		{
			if (strncmp(buffer + i, argv[1], arglen) == 0)
			{
				size_t n = arglen;
				while (n--)
					printf("*");
				i += arglen;
			}
			else
			{
				printf("%c", buffer[i]);
				i++;
			}

		}
		free(buffer);
		buffer = NULL;
	}
}
