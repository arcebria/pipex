/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:54:40 by arcebria          #+#    #+#             */
/*   Updated: 2025/01/30 15:47:37 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	dup_files(t_pipex *pipex)
{
	if (pipex->child == 0)
	{
		if (dup2(pipex->fd_in, STDIN) == -1)
			err_ex(1, pipex);
		if (dup2(pipex->pipe[1], STDOUT) == -1)
			err_ex(1, pipex);
	}
	else if (pipex->child == (pipex->n_cmds - 1))
	{
		if (dup2(pipex->pipe[2 * pipex->child - 2], STDIN) == -1)
			err_ex(1, pipex);
		if (dup2(pipex->fd_out, STDOUT) == -1)
			err_ex(1, pipex);
	}
	else
	{
		if (dup2(pipex->pipe[2 * pipex->child - 2], STDIN) == -1)
			err_ex(1, pipex);
		if (dup2(pipex->pipe[2 * pipex->child + 1], STDOUT) == -1)
			err_ex(1, pipex);
	}
}

/*El macro WIFEXITED(stats) es false si hubo algun problema
y true si el proceso termino correctamente
en este caso exit_status se actualiza para que devuelva su valor
normalmente 0, si no devuelve 1*/

int	exe_parent(t_pipex *pipex)
{
	int		exit_status;
	int		status;
	pid_t	wpid;

	exit_status = 1;
	pipex->child--;
	close_fds(pipex);
	close(pipex->fd_in);
	close(pipex->fd_out);
	while (pipex->child >= 0)
	{
		wpid = waitpid(pipex->pids[pipex->child], &status, 0);
		if (wpid == pipex->pids[pipex->n_cmds - 1])
		{
			if (pipex->child == (pipex->n_cmds - 1) && WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
		}
		pipex->child--;
	}
	free(pipex->pids);
	free(pipex->pipe);
	if (pipex->here_doc)
		unlink(".heredoc.tmp");
	return (exit_status);
}

void	exe_child(t_pipex *pipex)
{
	dup_files(pipex);
	close_pipes(pipex);
	if (execve(pipex->cmd_path, pipex->cmd_flags, pipex->env) == -1)
		err_ex(err_out(pipex->cmd_flags[0], ": ", strerror(errno), 127), pipex);
}

//free(pipex->cmd_path);
//ft_free_array(pipex->cmd_flags);

int	run_pipex(t_pipex *pipex)
{
	pipex->child = 0;
	while (pipex->child < pipex->n_cmds)
	{
		get_cmd(pipex, pipex->av[2 + pipex->child + pipex->here_doc]);
		pipex->pids[pipex->child] = fork();
		if (pipex->pids[pipex->child] == -1)
			err_ex(err_out("fork: ", strerror(errno), "", 1), pipex);
		else if (pipex->pids[pipex->child] == 0)
			exe_child(pipex);
		free(pipex->cmd_path);
		ft_free_array(pipex->cmd_flags);
		pipex->child++;
	}
	return (exe_parent(pipex));
}
