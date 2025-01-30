/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:29:23 by arcebria          #+#    #+#             */
/*   Updated: 2025/01/30 15:36:22 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < (pipex->n_cmds - 1) * 2)
	{
		close(pipex->pipe[i]);
		i++;
	}
}

void	close_fds(t_pipex *pipex)
{
	if (pipex->fd_in == -1)
		close(pipex->fd_in);
	if (pipex->fd_out == -1)
		close(pipex->fd_out);
	close_pipes(pipex);
}

int	err_out(char *str1, char *str2, char *str3, int err_no)
{
	ft_putstr_fd(str1, STDERR);
	ft_putstr_fd(str2, STDERR);
	ft_putendl_fd(str3, STDERR);
	return (err_no);
}

void	err_ex(int exit_code, t_pipex *pipex)
{
	if (pipex)
	{
		if (pipex->pids)
			free(pipex->pids);
		if (pipex->pipe)
			free(pipex->pipe);
		if (pipex->cmd_flags)
			ft_free_array(pipex->cmd_flags);
		if (pipex->cmd_path)
			free (pipex->cmd_path);
	}
	if (pipex->here_doc == 1)
		unlink(".here_doc.tmp");
	exit (exit_code);
}
