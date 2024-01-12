/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 21:29:17 by marboccu          #+#    #+#             */
/*   Updated: 2024/01/06 19:15:25 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		return (EXIT_FAILURE);
	}
	pipex.fd_in = ft_open_file(av[1], 0);
	if (pipe(pipex.pipe) == -1)
		err_msg("PIPE");
	ft_check_paths(&pipex, envp);
	ft_pipe_exec(&pipex, av, envp);
	ft_close_pipe(&pipex);
	waitpid(pipex.pid_child1, NULL, 0);
	waitpid(pipex.pid_child2, NULL, 0);
	ft_free_pipex(&pipex);
	return (EXIT_SUCCESS);
}
