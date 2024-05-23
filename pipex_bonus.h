/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:13:36 by fgori             #+#    #+#             */
/*   Updated: 2024/02/22 11:01:49 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"

void	put_error(char *str);
void	child(char *str, char *env[]);
int		last_child(char *str, char *env[]);
char	**find_phat(char **env);
int		freemat(char **mat);
void	here_init(char *av[]);
int		free2(char *str);
char	*make_cmd(char **full, char *cmd);
int		gnl2(char **line);
#endif