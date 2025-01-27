/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:20:12 by arcebria          #+#    #+#             */
/*   Updated: 2025/01/27 21:07:35 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pipex		pipex;
	int			exit_code;

	if (ac < 5)
	{
		ft_putstr_fd("Numero argumentos incorrectos", 2);
		return (1);
	}
	init_pipex(&pipex, ac, av, env);
	exit_code = run_pipex(&pipex);
	return (exit_code);
}
