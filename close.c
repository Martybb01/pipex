/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:52:14 by marboccu          #+#    #+#             */
/*   Updated: 2024/01/06 18:53:32 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close_fd(int fd)
{
	while (fd < 256)
	{
		close(fd);
		fd++;
	}
}

void	ft_close_pipe(t_pipex *pipex)
{
	close(pipex->pipe[READ_END]);
	close(pipex->pipe[WRITE_END]);
	ft_close_fd(3);
}
