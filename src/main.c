/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:20:12 by arcebria          #+#    #+#             */
/*   Updated: 2025/01/28 21:32:21 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pipex		pipex;
	int			exit_code;

	if (ac < 5)
		return (err_out("Usage: ",
				"./pipex file1 cmd1 cmd2 ... cmdn file2.", "", 1));
	if (ac < 6 && !ft_strncmp(av[1], "here_doc", 9))
		return (err_out("Usage: ",
				"./pipex here_doc DELIMITER cmd1 cmd2 ... cmdn file2.", "", 1));
	init_pipex(&pipex, ac, av, env);
	exit_code = run_pipex(&pipex);
	return (exit_code);
}
