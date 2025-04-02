/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razaccar <razaccar@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 08:02:26 by razaccar          #+#    #+#             */
/*   Updated: 2025/04/02 16:41:29 by razaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Allowed functions: pipe, fork, dup2, execvp, close, exit

write the following function:
	
	int	ft_popen(const char *file, char *const argv[], char type)

The function must launch the executable file with the arguments argv (using execvp).
If the type is 'r' the function must return a file descriptor connected to the output of the command.
If the type is 'w' the function must return a file descriptor connected to the input of the command.
In case of error or invalid parameter the function must return -1.

Hint: Do not leak file descriptors! */

#include <unistd.h>

int	ft_popen(const char *file, char *const argv[], char type)
{
	pid_t	pid;
	int		pipefd[2];
	
	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (type == 'r')
			dup2(pipefd[1], STDOUT_FILENO);
		if (type == 'w')
			dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execvp(file, argv);
	}
	else
	{
		if (type == 'r')
		{
			close(pipefd[1]);
			return (pipefd[0]);
		}
		if (type == 'w')
		{
			close(pipefd[0]);
			return (pipefd[1]);
		}
	}
	return (-1);
}
