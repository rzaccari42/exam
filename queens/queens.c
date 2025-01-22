/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razaccar <razaccar@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 00:39:23 by razaccar          #+#    #+#             */
/*   Updated: 2025/01/22 16:06:39 by razaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int	ft_atoi(const char *str)
{
	int	nbr;

	nbr = 0;
	while (*str >= '0' && *str <= '9')
	{
		nbr *= 10;
		nbr += *str - 48;
		str++;
	}
	return (nbr);
}

void	print_solution(char** grid, int	n)
{
	char	out[n + 1];
	int		i;
	int		row;
	int		col;

	i = 0;
	row = 0;
	col = 0;
	while (col < n)
	{
		while (row < n)
		{
			if (grid[row][col] == '1')
				out[i++] = 48 + row;
			row++;
		}
		row = 0;
		col++;
	}
	out[n] = 0;
	printf("%s\n", out);
}

int	is_safe(char **grid, int n, int row, int col)
{
	int	x;
	int	y;

	x = row;
	y = col;
	while (--y >= 0)
		if (grid[x][y] == '1')
			return (0);
	x = row;
	y = col;
	while (--y >= 0 && --x >= 0)
		if (grid[x][y] == '1')
			return (0);
	x = row;
	y = col;
	while (--y >= 0 && ++x < n)
		if (grid[x][y] == '1')
			return (0);
	return (1);
}

void	place_queens(char** grid, int n, int col)
{
	int	row;

	if (col == n)
	{
		print_solution(grid, n);
		return ;
	}
	row = 0;
	while (row < n)
	{
		if (is_safe(grid, n, row, col))
		{
			grid[row][col] = '1';
			place_queens(grid, n, col + 1);
			grid[row][col] = '0';
		}
		row++;
	}
	return ;
}

int	init_grid(char*** grid, int n)
{
	int		i;
	int		j;

	*grid = malloc(n * sizeof(char*));
	if (!*grid)
		return (1);
	i = 0;
	while (i < n)
	{
		(*grid)[i] = malloc((n + 1) * sizeof(char));
		if (!(*grid)[i])
		{
			while (--i)
				free((*grid)[i]);
			free(*grid);
			return (1);
		}
		j = 0;
		while (j < n)
			(*grid)[i][j++] = '0';
		(*grid)[i][j] = 0;
		i++;
	}
	return (0);
}

int	main(int argc, char** argv)
{
	char**	grid;
	int		n_queens;

	if (argc != 2)
		return (1);
	n_queens = ft_atoi(argv[1]);
	init_grid(&grid, n_queens);
	place_queens(grid, n_queens, 0);
}
