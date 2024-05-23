/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:08:35 by fgori             #+#    #+#             */
/*   Updated: 2024/02/22 12:06:51 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	put_error(char *str)
{
	perror(str);
	exit(1);
}

int	main(int ac, char *av[], char *env[])
{
	int	i;
	int	fd[2];

	i = 1;
	if (ac < 5)
		put_error("Error!\nnot many arguments");
	if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0 && i++)
	{
		here_init(av);
		fd[1] = open(av[ac - 1], O_APPEND | O_CREAT | O_RDWR, 0777);
	}
	else
	{
		fd[0] = open(av[1], O_RDONLY, 0777);
		fd[1] = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0777);
		dup2(fd[0], 0);
	}
	if ((i < 2 && fd[0] < 0) || (fd[1] < 0 && close(fd[0])))
		put_error("ERROR\n impossible file opening");
	while (++ i < ac - 2)
		child(av[i], env);
	dup2(fd[1], 1);
	if (last_child(av[ac - 2], env))
		return (perror("ERROR\nunfind cmd"), !(close(fd[0]) + close(fd[1])));
	return (close(fd[0]) + close(fd[1]));
}

void	child(char *str, char *env[])
{
	int	id;
	int	pip[2];

	if (pipe(pip) < 0)
		put_error("ERROR\n anopen pipe");
	id = fork();
	if (id < 0 && !(close(pip[0]) + close(pip[1])))
		put_error("ERROR\nfailed fork");
	if (id == 0)
	{
		close(pip[0]);
		dup2(pip[1], 1);
		if (last_child(str, env))
			put_error("ERROR\n filed execve");
	}
	else
	{
		close(pip[1]);
		dup2(pip[0], 0);
		waitpid(id, NULL, 0);
	}
}

int	last_child(char *str, char *env[])
{
	char	**path;
	char	**full_cmd;
	char	*right_cmd;

	full_cmd = ft_split(str, ' ');
	if (!full_cmd)
		put_error("ERROR\nerror in split");
	path = find_phat(env);
	if (!path && !freemat(full_cmd))
		return (1);
	right_cmd = make_cmd(path, full_cmd[0]);
	if (!right_cmd && !freemat(full_cmd) && !freemat(path))
		return (perror("ERROR\n unfind command"), 1);
	freemat(path);
	if (execve(right_cmd, full_cmd, env) < 0)
	{
		return (freemat(full_cmd), 1);
	}
	return (0);
}

void	here_init(char *av[])
{
	int		pip[2];
	int		id;
	char	*newline;

	if (pipe(pip) < 0)
		put_error("ERROR\n unpiped here_doc");
	id = fork();
	newline = NULL;
	if (id == 0 && !close(pip[0]))
	{
		while (1)
		{
			ft_printf("pipe heredoc> ");
			if (gnl2(&newline) && newline[ft_strlen(av[2])] == '\n'
				&& ft_strncmp(newline, av[2], ft_strlen(av[2])) == 0)
				exit(close(pip[1]) + free2(newline));
			ft_putstr_fd(newline, pip[1]);
			free(newline);
		}
	}
	else
	{
		dup2(pip[0], close(pip[1]));
		wait(NULL);
	}
}
