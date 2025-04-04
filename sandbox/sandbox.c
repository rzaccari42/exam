/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razaccar <razaccar@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:27:50 by razaccar          #+#    #+#             */
/*   Updated: 2025/04/04 05:07:32 by razaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name		:	sandbox
Expected files		:	sandbox.c
Allowed functions	:	fork, waitpid, exit, alarm, sigaction, kill,
						printf, strsignal, errno
===============================================================================

Write the following function:

#include <stdbool.h>
int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)

This function must test if the function f is a nice function or a bad function,
you will return 1 if f is nice , 0 if f is bad or -1 in case of an error in
your function.

A function is considered bad if it is terminated or stopped by a signal
(segfault, abort...), if it exit with any other exit code than 0 or if it
times out.

If verbose is true, you must write the appropriate message among the following:

"Nice function!\n"
"Bad function: exited with code <exit_code>\n"
"Bad function: <signal description>\n"
"Bad function: timed out after <timeout> seconds\n"

You must not leak processes (even in zombie state, this will be checked using
wait).

We will test your code with very bad functions.
*/

#include <complex.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/wait.h>

int	siginfo;

void	sighandler(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)ucontext;

	siginfo = info->si_status;
}


int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	int					pid;
	int					pstatus;
	struct sigaction	act;

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = sighandler;
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		alarm(timeout);
		f();
	}
	else
	{
		sigaction(SIGCHLD, &act, NULL);
		waitpid(pid, &pstatus, 0);
		if (WIFEXITED(pstatus))
		{
			if (siginfo != 0)
			{
				if (verbose)
					printf("Bad function: exited with code %d\n", siginfo);
				return (0);
			}
		}
		if (WIFSIGNALED(pstatus) || WIFSTOPPED(pstatus))
		{
			if (siginfo == SIGALRM)
			{
				if (verbose)
					printf("Bad function: timed out after %d seconds\n", timeout);
				return (0);
			}
			if (verbose)
				printf("Bad function: %s\n", strsignal(siginfo));
			return (0);

		}
	}
	if (verbose)
		printf("Nice function!");
	return (1);
}

void	f(void)
{

}

int	main()
{

}
