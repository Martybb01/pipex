/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:54:27 by marboccu          #+#    #+#             */
/*   Updated: 2023/12/24 19:56:41 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include "libft_extended/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1
#define debug printf("ciao\n");

typedef struct s_pipex
{
	int pipe[2];
	int pid_child1;
	int pid_child2;
	char **cmd_args;
	char **cmd_paths;
	char *path;
	char *env_path;
	int fd_in;
	int fd_out;
} t_pipex;

void err_msg(char *str);
int ft_open_file(char *file, int rd_or_wr);
char *ft_get_path(char **envp);
char *ft_get_cmd_path(char *cmd, char **paths);
void ft_free_pipex(t_pipex *pipex);
void ft_free_child(t_pipex *pipex);

#endif
