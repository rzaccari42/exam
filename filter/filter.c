/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razaccar <razaccar@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:23:11 by razaccar          #+#    #+#             */
/*   Updated: 2024/11/22 18:23:32 by razaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1


size_t ft_strlen(char *str)
{	
	size_t i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t i;
	size_t s1len;
	size_t s2len;

	i = 0;
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	s1 = realloc(s1, s1len + s2len  + 1);
	s1[s1len + s2len] = 0;
	while (*s2)
		s1[s1len + (i++)] = *(s2++);
	return (s1);
}

char	*get_input(char *line, char *buffer, int *stop)
{
	size_t	read_len;

	while (1)
	{
		if (line && strchr(line, '\n'))
		{
			*(strchr(line, '\n') + 1) = 0;
			break ;
		}
		read_len = read(0, buffer, BUFFER_SIZE);
		if (read_len == 0)
		{
			*stop = 1;
			break ;
		}
		buffer[read_len] = 0;
		line = ft_strjoin(line, buffer);
	}
	return (line);
}

void	print_filtered(char *line, char *arg)
{
	size_t	i;
	size_t	n;
	size_t	arglen;
	
	i = 0;
	arglen = ft_strlen(arg);
	while (i < ft_strlen(line))
	{
		if (arglen > 0 && !strncmp(line + i, arg, arglen))
		{
			n = arglen;
			i += n;
			while (n--)
				printf("*");

		}
		else
			printf("%c", line[i++]);
	}

}

int	main(int argc, char **argv)
{
	char	buffer[BUFFER_SIZE + 1];
	int	stop;
	char	*line;

	if (argc == 1)
		argv[1] = "";
	stop = 0;
	line = NULL;
	while (1)
	{
		line = get_input(line, buffer, &stop);
		if (!stop)
		{
			print_filtered(line, argv[1]);
			free(line);
			line = NULL;
			continue ;
		}
		break ;
	}
}
