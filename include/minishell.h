/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 18:29:02 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/07 18:02:38 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <dirent.h>
# include <stdbool.h>
# include <fcntl.h>

# define EXIT_SYNTAX_ERROR 258
# define EXIT_CMD_NOT_FOUND 127

/* INBUILD */
int		echo(char **args);
int		export(char **argv);
int		unset(char **argv);
int		env(char **argv);
int		pwd(void);
int		cd(char **argv);

#endif
