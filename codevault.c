/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codevault.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 10:54:30 by marboccu          #+#    #+#             */
/*   Updated: 2023/12/24 14:05:36 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char **av)
{
	int fd[2];
	int pid1;
	int pid2;
	char *program;
	(void)ac;

	program = "/sbin/ping";
	av = (char *[]){"ping", "-c", "2", "google.com", NULL};

	if (pipe(fd) == -1)
		err_msg("pipe");
	pid1 = fork();
	if (pid1 < 0)
		err_msg("fork");

	if (pid1 == 0)
	{
		// Child process 1 (ping)
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		execve(program, av, NULL);
	}

	pid2 = fork();
	if (pid2 < 0)
		err_msg("fork");
	if (pid2 == 0)
	{
		// Child process 2 (grep)
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		execve("/usr/bin/grep", (char *[]){"grep", "round-trip", NULL}, NULL);
	}

	close(fd[READ_END]);
	close(fd[WRITE_END]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return (0);
}

// int main()
// {
// 	int pid;
// 	int file;
// 	int file2;
// 	int err;
// 	int status;
// 	char *argv[] = {"ping", "-c", "1", "google.com", NULL};
// 	char *program = "/sbin/ping";

// 	pid = fork();
// 	if (pid == -1)
// 		err_msg("fork");

// 	if (pid == 0)
// 	{
// 		// Child process
// 		file = open("ping.txt", O_WRONLY | O_CREAT, 0777);
// 		if (file == -1)
// 			err_msg("open");

// 		printf("The fd to ping: %d\n", file);
// 		file2 = dup2(file, STDOUT_FILENO);
// 		printf("The duplicated fd: %d\n", file2);
// 		close(file);

// 		err = execve(program, argv, NULL);
// 		if (err == -1)
// 			err_msg("execve");
// 	}
// 	else
// 	{
// 		// Parent process
// 		wait(&status);
// 		printf("I am the parent process!\n");
// 	}
// }
