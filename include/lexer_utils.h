/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 01:18:48 by toni              #+#    #+#             */
/*   Updated: 2021/11/27 01:43:58 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_UTILS_H
# define LEXER_UTILS_H

// LEXER UTILS
char	get_next_special(char *token);
size_t	get_new_tokens_size(char **tokens);
size_t	get_next_token_size(char *token, char next_special);
bool	token_is_unadjusted(char *token);
bool	is_special_char(char curr, char next);
int		jump_to_end_of_subshell(char *tokens[], int i);
int		get_subshell_count(char *tokens[], int i);
bool	token_is_subshell(char *token);
int		join_quotes(char ***tokens);
char	*get_end_of_subshell(char *tokens[], int *i, char *sub_tok);

#endif