/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:08:38 by arcebria          #+#    #+#             */
/*   Updated: 2025/01/30 15:49:40 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	get_heredoc(t_pipex *pipex, char *limiter)
{
	char	*line;
	int		heredoc_fd;
	int		stdin_fd;

	stdin_fd = dup(STDIN);
	line = NULL;
	heredoc_fd = open (".heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (heredoc_fd == -1 || stdin_fd == -1)
		err_ex(err_out("here_doc", ": ", strerror(errno), 1), pipex);
	while (1)
	{
		ft_putstr_fd("here_doc> ", STDOUT);
		line = get_next_line(stdin_fd);
		if (!line)
			break ;
		if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
			close(stdin_fd);
		else
			ft_putstr_fd(line, heredoc_fd);
		free(line);
	}
	close(heredoc_fd);
}

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

void	get_cmd(t_pipex *pipex, char *cmd)
{
	pipex->cmd_flags = ft_split(cmd, ' ');
	if (!pipex->cmd_flags[0])
	{
		ft_putstr_fd("No null command accepted\n", 2);
		exit(1);
	}
	if (ft_strchr(pipex->cmd_flags[0], '/'))
		pipex->cmd_path = ft_strdup(cmd);
	else
		pipex->cmd_path = get_path(pipex->env, pipex->cmd_flags[0]);
}
