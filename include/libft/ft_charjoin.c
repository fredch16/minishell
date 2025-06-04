/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:33:55 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/04 15:21:33 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_charjoin(char const *s1, char const s2)
{
	int		totallen;
	char	*new;

	if (!s2)
		return (ft_strdup((char *)s1));
	totallen = ft_strlen((char *)s1) + 1;
	if (totallen == 0)
		return (ft_strdup(""));
	new = (char *)malloc(sizeof (char) * totallen + 1);
	if (!new)
		return (NULL);
	ft_strlcpy(new, (char *)s1, ft_strlen((char *)s1) + 1);
	ft_strlcat(new, &s2, totallen + 1);
	return (new);
}