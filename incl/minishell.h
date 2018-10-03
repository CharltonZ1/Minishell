/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chadams <chadams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 05:26:01 by chadams           #+#    #+#             */
/*   Updated: 2018/09/17 05:26:02 by chadams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <dirent.h>
# include "./libft.h"

char	*readline(int fd);
void	parse_line(char *line, char *command[]);
char	**parse_builtins(char *command[], char **envp);
void	parse_command(char *command[], char **envp);
void	siginthandler2(int sig_num);
void	siginthandler(int sig_num);
void	handle_shell(char **envp, int nbr);
int		find(char **envp, char *to_find);
void	cd(char *command[], char **envp);
void	printenv(char *command, char **envp);
char	**set_env(char *command1, char *command2, char **envp);
void	unset_env(char **envp, char *command[]);
char	**new_env(char **envp);
void	subs_env_var(char *command[], char **envp);

#endif
