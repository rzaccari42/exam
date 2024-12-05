/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razaccar <razaccar@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:23:11 by razaccar          #+#    #+#             */
/*   Updated: 2024/12/05 22:43:30 by razaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * If, as said in the exam subject, we have to reproduce the bash script but in 
 * a strict way; we maybe have to handle \n as argument in a specific way 
 * because sed can't use this as a part of its command 
 * => (because of the s/search/replace/ syntax)
 * Here it works because the \n character is catched when parsing the input read
 * from the stdin stream.
 **/

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 10

void	filter(char *arg);
char	*get_input(int *eof);
void	print_filtered(char *input, char *arg);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(char *str);

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	if (argv[1][0] == 0)
		return (1);
	filter(argv[1]);
	return (0);
}

void	filter(char *arg)
{
	char	*input;
	int		eof;

	input = NULL;
	eof = 0;
	while (1)
	{
		input = get_input(&eof);
		print_filtered(input, arg);
		free(input);
		if (eof)
			break ;
	}
}

char	*get_input(int *eof)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*input;
	size_t	readlen;

	input = NULL;
	readlen = read(0, buffer, BUFFER_SIZE);
	if (readlen < 0)
	{
		perror("Error: ");
		return (NULL);
	}
	while (readlen > 0)
	{
		buffer[readlen] = 0;
		input = ft_strjoin(input, buffer);
		if (ft_strchr(input, '\n'))
			break ;
		readlen = read(0, buffer, BUFFER_SIZE);
	}
	if (readlen == 0)
		*eof = 1;
	return (input);
}

void	print_filtered(char *input, char *arg)
{
	size_t	arglen;
	size_t	n;
	size_t	i;
	
	i = 0;
	arglen = ft_strlen(arg);
	while (i < ft_strlen(input))
	{
		if (!ft_strncmp(input + i, arg, arglen))
		{
			n = arglen;
			i += n;
			while (n--)
				printf("*");
		}
		else
			printf("%c", input[i++]);
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t s1len;
	size_t s2len;
	size_t i;

	i = 0;
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	s1 = realloc(s1, s1len + s2len + 1);
	if (!s1)
	{
		perror("Error: ");
		return (NULL);
	}
	while (*s2)
		s1[s1len + (i++)] = *(s2++);
	s1[s1len + s2len] = 0;
	return (s1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

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
