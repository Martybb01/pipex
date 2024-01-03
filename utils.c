/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:56:17 by marboccu          #+#    #+#             */
/*   Updated: 2023/12/28 19:21:50 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void err_msg(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

int ft_open_file(char *file, int rd_or_wr)
{
	int fd;

	if (rd_or_wr == 0)
		fd = open(file, O_RDONLY, 0777);
	if (rd_or_wr == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		err_msg("OPEN");
	if (access(file, F_OK) == -1)
		err_msg("File does not exist");
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

char *ft_get_cmd_path(char *cmd, char **paths)
{
	int i;
	char *cmd_path;
	char *temp;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}
