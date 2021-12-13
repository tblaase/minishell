/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 21:59:04 by toni              #+#    #+#             */
/*   Updated: 2021/12/13 17:14:50 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"
#include "expander_utils.h"
#include <readline/history.h>
#include <readline/readline.h>

/**
 * @brief  Gets heredoc to wait for
 * @note
 * @param  *par_tok:
 * @retval char pointer to (by parser) allocated heredoc
 */
static char	*get_heredoc(t_par_tok *par_tok)
{
	int	i;

	i = 0;
	while (par_tok->in[i])
	{
		if (ft_strcmp(par_tok->in[i], "<<") == 0)
			return (par_tok->in[i + 1]);
		i++;
	}
	return (NULL);
}

/**
 * @brief  Waits in readline-prompt as long as heredoc is not typed
 * @note
 * @param  *par_tok:
 * @retval int to indicate success or failure
 */
int	wait_for_heredoc(t_par_tok *par_tok, t_exp_tok *exp_tok)
{
	char	*buf;
	char	*heredoc;
	int		end[2];

	if (pipe(end) == -1)
		return (ft_perror(EXIT_FAILURE, "pipe error"));
	// remove after testing until next //
	// fprintf(stderr, "read end of the pipe: %d\n", end[0]);
	// fprintf(stderr, "write end of the pipe: %d\n", end[1]);
	//
	exp_tok->in = end[0];
	heredoc = get_heredoc(par_tok);
	if (heredoc == NULL)
	{
		if (close(end[0]) == -1)
			perror("close error");
		if (close(end[1]) == -1)
			perror("close error");
		return (EXIT_FAILURE);
	}
	while (true)
	{
		buf = readline("> ");
		if (buf == NULL)
		{
			if (close(end[1]) == -1)
				return (ft_perror(EXIT_FAILURE, "close error"));
			return (EXIT_SUCCESS);
		}
		if (ft_strcmp(buf, heredoc) == 0)
			break ;
		write(end[1], buf, ft_strlen(buf));
		write(end[1], "\n", 1);
		free(buf);
	}
	free(buf);
	if (close(end[1]) == -1)
		return (ft_perror(EXIT_FAILURE, "close error"));
	if (exp_tok->cmd == NULL && exp_tok->out != STDOUT_FILENO)
	{
		if (close(exp_tok->out) == -1)
			return (ft_perror(EXIT_FAILURE, "close error"));
		exp_tok->out = STDOUT_FILENO;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief  Searches for heredoc in par_toks and waits if found
 * @note
 * @param  *par_toks[]:
 * @retval int to indicate success or failure
 */
int	check_for_heredoc(t_par_tok *par_toks[])
{
	//think about deleting this, since toni said its not needed anymore
	int	i;

	i = 0;
	while (par_toks[i])
	{
		if (par_toks[i]->redir_type[is_in_heredoc])
			return (wait_for_heredoc(par_toks[i], NULL));
		i++;
	}
	return (EXIT_SUCCESS);
}
