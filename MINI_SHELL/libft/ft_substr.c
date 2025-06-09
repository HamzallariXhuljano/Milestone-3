/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnicolo <gnicolo@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:01:04 by gnicolo           #+#    #+#             */
/*   Updated: 2024/11/24 15:01:21 by gnicolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub_str;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (start > (unsigned int)ft_strlen(s))
	{
		sub_str = ft_calloc(sizeof(char), 1);
		return (sub_str);
	}
	if (ft_strlen(s) - start > len)
		sub_str = malloc(sizeof(char) * ((len + 1)));
	else
		sub_str = malloc(sizeof(char)
				* (((unsigned int)ft_strlen(s) - start) + 1));
	if (sub_str == NULL)
		return (NULL);
	i = 0;
	while ((char)s[start] && (size_t)i < len)
	{
		sub_str[i++] = (char)s[start];
		start++;
	}
	sub_str[i] = 0;
	return (sub_str);
}
/*int main()
{
    const char *str = "Hello, World!";
    char *substr1, *substr2, *substr3;

    // Test 1: Sottostringa da un punto valido
    substr1 = ft_substr(str, 7, 5);  // "World"
    if (substr1)
    {
        printf("Sottostringa 1: %s\n", substr1);
        free(substr1);  // Non dimenticare di liberare la memoria
    }

    // Test 2: Start oltre la fine della stringa
    substr2 = ft_substr(str, 20, 5);  // ""
    if (substr2)
    {
        printf("Sottostringa 2: %s\n", substr2);  // Dovrebbe essere vuoto
        free(substr2);
    }

    // Test 3: Lunghezza maggiore rispetto alla parte restante della stringa
    substr3 = ft_substr(str, 7, 100);  // "World!"
    if (substr3)
    {
        printf("Sottostringa 3: %s\n", substr3);
        free(substr3);
    }

    return 0;
}*/
