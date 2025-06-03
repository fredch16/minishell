/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:33:55 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/03 22:59:12 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Joins a string and a character, returning a new string
 * @param s1 The string to append to
 * @param s2 The character to append
 * @return A new string with s2 appended to s1, or NULL if allocation fails
 */
char	*ft_charjoin(char const *s1, char const s2)
{
	size_t	len;
	char	*result;

	if (!s1)
		s1 = "";
	len = ft_strlen(s1);
	result = (char *)malloc(sizeof(char) * (len + 2));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, len + 1);
	result[len] = s2;
	result[len + 1] = '\0';
	return (result);
}
