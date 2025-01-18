/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:55:18 by arcebria          #+#    #+#             */
/*   Updated: 2025/01/18 10:44:35 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	check_acces(char **dir, char *full_path)
{
	if (access(full_path, F_OK) == 0)
	{
		ft_free_array(dir);
		return (0);
	}
	free (full_path);
	return (1);
}

char	*get_path(char **env, char *cmd)
{
	int		i;
	int		j;
	char	**dir;
	char	*pre_path;
	char	*full_path;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (NULL);
	dir = ft_split(env[i] + 5, ':');
	j = 0;
	while (dir[j])
	{
		pre_path = ft_strjoin(dir[j], "/");
		full_path = ft_strjoin(pre_path, cmd);
		free (pre_path);
		if (check_acces(dir, full_path) == 0)
			return (full_path);
		j++;
	}
	ft_free_array(dir);
	return (NULL);
}

void	exe_pipes(t_pipex *pipex, char **env, char *cmd)
{
	pipex->cmd_flags = ft_split(cmd, ' ');
	if (ft_strchr(pipex->cmd_flags[0], '/'))
		pipex->cmd_path = pipex->cmd_flags[0];
	else
		pipex->cmd_path = get_path(env, pipex->cmd_flags[0]);
	if (!pipex->cmd_path)
	{
		ft_putstr_fd("Error encontrar ruta\n", 2);
		exit (1);
	}
	execve(pipex->cmd_path, pipex->cmd_flags, env);
	ft_putstr_fd("exceve ha fallado\n", STDERR);
	ft_free_array(pipex->cmd_flags);
}

void	set_pipes(t_pipex *pipex, char *cmd1)
{
	pipe(pipex->pipe);
	pipex->pids = fork();
	if (pipex->pids)
	{
		close(pipex->pipe[1]);
		dup2(pipex->pipe[0], STDIN);
		waitpid(pipex->pids, NULL, 0);
	}
	else
	{
		close(pipex->pipe[0]);
		dup2(pipex->pipe[1], STDOUT);
		exe_pipes(pipex, pipex->env, cmd1);
	}
}

int	open_files(char *filename, int flag)
{
	int		fd;

	if (flag == INFILE)
	{
		if (access(filename, F_OK))
		{
			ft_putstr_fd(filename, STDERR);
			ft_putstr_fd(": no existe el archivo o directorio\n", STDERR);
		}
		fd = open(filename, O_RDONLY);
		if (fd == -1)
			ft_putstr_fd("Error al crear el archivo de entrada\n", STDERR);
	}
	else
	{
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
			ft_putstr_fd("Error al crear el archivo de salida\n", STDERR);
	}
	return (fd);
}
