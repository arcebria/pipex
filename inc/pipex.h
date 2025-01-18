/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:00:51 by arcebria          #+#    #+#             */
/*   Updated: 2025/01/18 10:44:56 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include <sys/wait.h>
# include <fcntl.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define INFILE 0
# define OUTFILE 1

typedef struct s_pipex
{
	int		fd_in;
	int		fd_out;
	int		pipe[2];
	int		pids;
	char	**env;
	char	**cmd_flags;
	char	*cmd_path;
	char	*cmd1;
	char	*cmd2;
}	t_pipex;

int		open_files(char *filename, int flag);
void	set_pipes(t_pipex *pipex, char *cmd1);
void	exe_pipes(t_pipex *pipex, char **env, char *cmd);
char	*get_path(char **env, char *cmd);
int		check_acces(char **dir, char *full_path);

#endif
