/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 21:29:17 by marboccu          #+#    #+#             */
/*   Updated: 2023/12/28 14:08:06 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_firstchild_exec(t_pipex *pipex, char **av, char **envp)
{
	pipex->fd_in = ft_open_file(av[1], 0);
	dup2(pipex->pipe[WRITE_END], STDOUT_FILENO);
	close(pipex->pipe[READ_END]);
	dup2(pipex->fd_in, STDIN_FILENO);
	pipex->cmd_args = ft_split(av[2], ' ');
	pipex->path = ft_get_cmd_path(pipex->cmd_args[0], pipex->cmd_paths);
	if (!pipex->path || !pipex->cmd_args)
	{
		ft_free_child(pipex);
		close(pipex->fd_in);
		err_msg("Command not found");
	}
	execve(pipex->path, pipex->cmd_args, envp);
	// close(pipex->fd_in);
}

void ft_secondchild_exec(t_pipex *pipex, char **av, char **envp)
{
	pipex->fd_out = ft_open_file(av[4], 1);
	dup2(pipex->pipe[READ_END], STDIN_FILENO);
	close(pipex->pipe[WRITE_END]);
	dup2(pipex->fd_out, STDOUT_FILENO);
	pipex->cmd_args = ft_split(av[3], ' ');
	pipex->path = ft_get_cmd_path(pipex->cmd_args[0], pipex->cmd_paths);
	if (!pipex->path || !pipex->cmd_args)
	{
		ft_free_child(pipex);
		close(pipex->fd_out);
		err_msg("ERROR: Command not found");
	}
	execve(pipex->path, pipex->cmd_args, envp);
	// close(pipex->fd_out);
}

int main(int ac, char **av, char **envp)
{
	t_pipex pipex;

	if (ac != 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		return (EXIT_FAILURE);
	}

	if (pipe(pipex.pipe) == -1)
		err_msg("PIPE");

	pipex.env_path = ft_get_path(envp);
	pipex.cmd_paths = ft_split(pipex.env_path, ':');

	pipex.pid_child1 = fork();
	if (pipex.pid_child1 < 0)
		err_msg("FORK");
	if (pipex.pid_child1 == 0)
	{
		printf("I am the child process! My PID is %d, and my child's PID is %d\n", getpid(), pipex.pid_child1);
		ft_firstchild_exec(&pipex, av, envp);
	}

	pipex.pid_child2 = fork();
	if (pipex.pid_child2 < 0)
		err_msg("FORK");
	if (pipex.pid_child2 == 0)
	{
		printf("I am the child process! My PID is %d, and my child's PID is %d\n", getpid(), pipex.pid_child2);
		ft_secondchild_exec(&pipex, av, envp);
	}

	close(pipex.pipe[READ_END]);
	close(pipex.pipe[WRITE_END]);

	waitpid(pipex.pid_child1, NULL, 0);
	waitpid(pipex.pid_child2, NULL, 0);
	ft_free_pipex(&pipex);

	return (EXIT_SUCCESS);
}
