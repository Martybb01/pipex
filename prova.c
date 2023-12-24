/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prova.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 21:29:17 by marboccu          #+#    #+#             */
/*   Updated: 2023/12/24 17:53:04 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int ft_open_file(char *file, int rd_or_wr)
{
	int fd;

	if (rd_or_wr == 0)
		fd = open(file, O_RDONLY);
	if (rd_or_wr == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		err_msg("OPEN");
	return (fd);
}

char *ft_get_path(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

void ft_fchild_exec(t_pipex *pipex, char **av, char **envp)
{
	(void)av;
	(void)envp;
	dup2(pipex->pipe[WRITE_END], STDOUT_FILENO);
	close(pipex->pipe[READ_END]);
	dup2(pipex->fd_in, STDIN_FILENO);
	close(pipex->fd_in);
}

void ft_schild_exec(t_pipex *pipex, char **av, char **envp)
{
	(void)av;
	(void)envp;
	dup2(pipex->pipe[READ_END], STDIN_FILENO);
	close(pipex->pipe[WRITE_END]);
	dup2(pipex->fd_out, STDOUT_FILENO);
	close(pipex->fd_out);
}

int main(int ac, char **av, char **envp)
{
	t_pipex pipex;
	(void)ac;
	(void)envp;

	// if (ac != 5)
	// 	err_msg("Wrong number of arguments");
	pipex.fd_in = ft_open_file(av[1], 0);
	pipex.fd_out = ft_open_file(av[4], 1);

	if (pipe(pipex.pipe) == -1)
		err_msg("PIPE");

	pipex.path = ft_get_path(envp);
	pipex.cmd_path = ft_split(pipex.path, ':');
	printf("%s\n", pipex.cmd_path[1]);

	pipex.pid_child1 = fork();
	if (pipex.pid_child1 < 0)
		err_msg("FORK");
	if (pipex.pid_child1 == 0)
	{
		printf("I am the child process! My PID is %d, and my child's PID is %d\n", getpid(), pipex.pid_child1);
		ft_fchild_exec(&pipex, av, envp);
	}
	pipex.pid_child2 = fork();
	if (pipex.pid_child2 < 0)
		err_msg("FORK");
	if (pipex.pid_child2 == 0)
	{
		printf("I am the child process! My PID is %d, and my child's PID is %d\n", getpid(), pipex.pid_child2);
		ft_schild_exec(&pipex, av, envp);
	}

	close(pipex.pipe[READ_END]);
	close(pipex.pipe[WRITE_END]);

	waitpid(pipex.pid_child1, NULL, 0);
	waitpid(pipex.pid_child2, NULL, 0);
	return (0);
}
