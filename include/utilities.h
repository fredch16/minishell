/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:07:28 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/03 21:53:15 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include "minishell.h"

int		handle_error(t_mini *mini);
int		check_syntax_errors(t_token_list *token_list);
bool	g2g(t_token_list *list);
void	tk_err(t_token_list *token_list, int error_code);

#endif