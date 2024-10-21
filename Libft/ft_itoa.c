/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:37:19 by mstefano          #+#    #+#             */
/*   Updated: 2023/10/30 15:10:21 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digit_count(int n)
{
	int	digit;

	digit = 0;
	if (n <= 0)
		digit = 1;
	while (n)
	{
		n /= 10;
		digit++;
	}
	return (digit);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		d_count;
	long	n1;

	n1 = n;
	d_count = ft_digit_count(n1);
	result = (char *)malloc(sizeof(char) * (d_count + 1));
	if (!result)
		return (NULL);
	result[d_count] = '\0';
	if (n1 == 0)
		result[0] = 48;
	while (n1 < 0)
	{
		result[0] = 45;
		n1 = -n1;
	}
	while (n1 && d_count--)
	{
		result[d_count] = (n1 % 10) + 48;
		n1 /= 10;
	}
	return (result);
}
