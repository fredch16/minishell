/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 00:00:00 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/25 11:12:47 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include <stdlib.h>
# include "minishell.h"

typedef enum e_gc_type			t_gc_type;
typedef struct s_garbage_list	t_garbage_list;

t_garbage_list	*get_gc_data(void);

/**
 * Allocate memory and track it for automatic cleanup
 * @param size Size of memory to allocate
 * @return Pointer to allocated memory or NULL on failure
 */
void			*gc_malloc(size_t size, t_gc_type type);

/**
 * Free a specific pointer from the garbage collection list
 * @param ptr Pointer to free
 * @return 1 if freed, 0 if not found
 */
int				gc_free(void *ptr);

/**
 * Free all allocated memory in the garbage collection list
 */
void			gc_free_all(void);

/**
 * Track an externally allocated pointer in the garbage collection list
 * @param ptr Pointer to track
 * @param type Type of gc node
 * @return 1 on success, 0 on failure
 */
int				gc_track(void *ptr, t_gc_type type);

void			gc_free_by_type(t_gc_type type);

#endif