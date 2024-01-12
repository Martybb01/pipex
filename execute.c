/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:13:39 by marboccu          #+#    #+#             */
/*   Updated: 2024/01/06 19:28:48 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_firstchild_exec(t_pipex *pipex, char **av, char **envp)
{
	dup2(pipex->pipe[WRITE_END], STDOUT_FILENO);
	close(pipex->pipe[READ_END]);
	dup2(pipex->fd_in, STDIN_FILENO);
	close(pipex->fd_in);
	pipex->cmd_args = ft_split(av[2], ' ');
	pipex->path = ft_get_cmd_path(pipex->cmd_args[0], pipex->cmd_paths);
	if (!pipex->path || !pipex->cmd_args)
	{
		ft_free_child(pipex);
		err_msg("Command not found");
	}
	else
		execve(pipex->path, pipex->cmd_args, envp);
}

void	ft_secondchild_exec(t_pipex *pipex, char **av, char **envp)
{
	pipex->fd_out = ft_open_file(av[4], 1);
	dup2(pipex->pipe[READ_END], STDIN_FILENO);
	close(pipex->pipe[WRITE_END]);
	dup2(pipex->fd_out, STDOUT_FILENO);
	close(pipex->fd_out);
	pipex->cmd_args = ft_split(av[3], ' ');
	pipex->path = ft_get_cmd_path(pipex->cmd_args[0], pipex->cmd_paths);
	if (!pipex->path || !pipex->cmd_args)
	{
		ft_free_child(pipex);
		err_msg("ERROR: Command not found");
	}
	execve(pipex->path, pipex->cmd_args, envp);
}

void	ft_pipe_exec(t_pipex *pipex, char **av, char **envp)
{
	pipex->pid_child1 = fork();
	if (pipex->pid_child1 < 0)
		err_msg("FORK");
	if (pipex->pid_child1 == 0)
		ft_firstchild_exec(pipex, av, envp);
	pipex->pid_child2 = fork();
	if (pipex->pid_child2 < 0)
		err_msg("FORK");
	if (pipex->pid_child2 == 0)
		ft_secondchild_exec(pipex, av, envp);
}
