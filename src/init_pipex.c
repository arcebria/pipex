/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:08:46 by arcebria          #+#    #+#             */
/*   Updated: 2025/01/28 21:33:00 by arcebria         ###   ########.fr       */
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
	if (pipex->here_doc == 1)
		pipex->fd_out = open(pipex->av[pipex->ac - 1], O_CREAT
				| O_WRONLY | O_APPEND, 0664);
	else
		pipex->fd_out = open(pipex->av[pipex->ac - 1], O_CREAT
				| O_WRONLY | O_TRUNC, 0664);
	if (pipex->fd_out == -1)
		err_out(strerror(errno), ": ", pipex->av[pipex->ac - 1], 1);
}

void	open_infile(t_pipex *pipex)
{
	if (pipex->here_doc == 1)
	{
		pipex->fd_in = open (".heredoc.tmp", O_RDONLY);
		if (pipex->fd_in == -1)
			err_ex(err_out("here_doc", ": ", strerror(errno), 1), pipex);
	}
	else
	{
		pipex->fd_in = open(pipex->av[1], O_RDONLY, 644);
		if (pipex->fd_in == -1)
			err_out(strerror(errno), ": ", pipex->av[1], 1);
	}
}

t_pipex	*pre_init(t_pipex *pipex, int ac, char **av, char **env)
{
	pipex->ac = ac;
	pipex->av = av;
	pipex->env = env;
	pipex->pids = NULL;
	pipex->pipe = NULL;
	pipex->here_doc = 0;
	return (pipex);
}

void	init_pipex(t_pipex *pipex, int ac, char **av, char **env)
{
	pipex = pre_init(pipex, ac, av, env);
	if (!ft_strncmp(av[1], "here_doc", 9))
		pipex->here_doc = 1;
	if (pipex->here_doc == 1)
		get_heredoc(pipex, av[2]);
	open_infile(pipex);
	open_outfile(pipex);
	pipex->n_cmds = ac - 3 - pipex->here_doc;
	pipex->pids = malloc(sizeof(pid_t) * pipex->n_cmds);
	if (!pipex->pids)
		err_ex(err_out("fork: ", "Resource temporarily unavaiable",
				"", 1), pipex);
	pipex->pipe = malloc(sizeof(pipex->pipe) * (pipex->n_cmds - 1));
	if (!pipex->pipe)
		err_ex(err_out("pipe: ", "Cannot allocate memory", "", 1), pipex);
	create_pipes(pipex);
}
