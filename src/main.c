/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:20:12 by arcebria          #+#    #+#             */
/*   Updated: 2025/01/18 10:44:21 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pipex		pipex;

	pipex.env = env;
	pipex.cmd1 = av[2];
	pipex.cmd2 = av[3];
	if (ac != 5)
	{
		ft_putstr_fd("Numero de argumentos incorrectos\n", 2);
		return (1);
	}
	pipex.fd_in = open_files(av[1], INFILE);
	if (pipex.fd_in == -1)
		return (1);
	pipex.fd_out = open_files(av[4], OUTFILE);
	if (pipex.fd_out == -1)
		return (1);
	dup2(pipex.fd_in, STDIN);
	dup2(pipex.fd_out, STDOUT);
	set_pipes(&pipex, pipex.cmd1);
	exe_pipes(&pipex, pipex.env, pipex.cmd2);
	return (0);
}
