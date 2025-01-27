/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:08:38 by arcebria          #+#    #+#             */
/*   Updated: 2025/01/27 20:36:34 by arcebria         ###   ########.fr       */
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

void	get_cmd(t_pipex *pipex, char *cmd)
{
	pipex->cmd_flags = ft_split(cmd, ' ');
	if (!pipex->cmd_flags[0])
	{
		ft_putstr_fd("No null command accepted\n", 2);
		exit(1);
	}
	if (ft_strchr(pipex->cmd_flags[0], '/'))
		pipex->cmd_path = pipex->cmd_flags[0];
	else
		pipex->cmd_path = get_path(pipex->env, pipex->cmd_flags[0]);
	if (!pipex->cmd_path)
		err_ex(err_out("Error al encontrar", "", "", 127), pipex);
}
