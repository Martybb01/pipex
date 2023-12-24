/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:54:27 by marboccu          #+#    #+#             */
/*   Updated: 2023/12/24 17:54:31 by marboccu         ###   ########.fr       */
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
	char **cmds_args;
	char **cmd_path;
	char *cmd;
	char *path;
	int fd_in;
	int fd_out;
} t_pipex;

void err_msg(char *str);

#endif
