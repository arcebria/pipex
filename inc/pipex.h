/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:00:51 by arcebria          #+#    #+#             */
/*   Updated: 2025/01/27 20:33:40 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define INFILE 0
# define OUTFILE 1

typedef struct s_pipex
{
	char	**env;
	int		ac;
	char	**av;
	int		fd_in;
	int		fd_out;
	int		**pipe;
	pid_t	*pids;
	char	**cmd_flags;
	char	*cmd_path;
	int		n_cmds;
	int		child;
}	t_pipex;

void	init_pipex(t_pipex *pipex, int ac, char **av, char **env);
int		run_pipex(t_pipex *pipex);
void	get_cmd(t_pipex *pipex, char *cmd);
int		err_out(char *str1, char *str2, char *str3, int err_no);
void	err_ex(int exit_code, t_pipex *pipex);
void	close_pipes(t_pipex *pipex);
void	close_fds(t_pipex *pipex);

#endif
