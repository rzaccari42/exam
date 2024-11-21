/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razaccar <razaccar@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:23:11 by razaccar          #+#    #+#             */
/*   Updated: 2024/11/21 17:17:33 by razaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 10

size_t ft_strlen(char *str)
{
	size_t i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t i = 0;
	char	*str;

	str = realloc(s1, ft_strlen(s1) + ft_strlen(s2) + 1);
	while (*s2)
	{
		str[ft_strlen(s1) + i] = *s2;
		i++;
		s2++;
	}
	return (s2);
}

int	main(int argc, char **argv)
{
	char	*file;
	char	buffer[BUFFER_SIZE];

	(void)argc;
	(void)argv;
	while (1)
	{
		if (read(0, buffer, BUFFER_SIZE) == 0)
			break ;
		file = ft_strjoin(file, buffer);
	}
}
