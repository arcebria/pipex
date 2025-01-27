/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:08:46 by arcebria          #+#    #+#             */
/*   Updated: 2025/01/27 21:13:05 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	create_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->n_cmds - 1)
	{
		pipex->pipe[i] = malloc(sizeof(int) * 2);
		if (pipe(pipex->pipe[i]) == -1)
			err_ex(err_out("pipe: ", "Too many open files", "", 1), pipex);
		i++;
	}
}

void	open_outfile(t_pipex *pipex)
{
	pipex->fd_out = open(pipex->av[pipex->ac - 1], O_CREAT
			| O_WRONLY | O_TRUNC, 0664);
	if (pipex->fd_out == -1)
		err_out(strerror(errno), ": ", pipex->av[pipex->ac - 1], 1);
}

void	open_infile(t_pipex *pipex)
{
	pipex->fd_in = open(pipex->av[1], O_RDONLY, 644);
	if (pipex->fd_in == -1)
		err_out(strerror(errno), ": ", pipex->av[1], 1);
}

t_pipex	*pre_init(t_pipex *pipex, int ac, char **av, char **env)
{
	pipex->ac = ac;
	pipex->av = av;
	pipex->env = env;
	pipex->pids = NULL;
	pipex->pipe = NULL;
	return (pipex);
}

void	init_pipex(t_pipex *pipex, int ac, char **av, char **env)
{
	pipex = pre_init(pipex, ac, av, env);
	open_infile(pipex);
	open_outfile(pipex);
	pipex->n_cmds = ac - 3;
	pipex->pids = malloc(sizeof(pid_t) * pipex->n_cmds);
	if (!pipex->pids)
		err_ex(err_out("fork: ", "Resource temporarily unavaiable",
				"", 1), pipex);
	pipex->pipe = malloc(sizeof(pipex->pipe) * (pipex->n_cmds - 1));
	if (!pipex->pipe)
		err_ex(err_out("pipe: ", "Cannot allocate memory", "", 1), pipex);
	create_pipes(pipex);
}
