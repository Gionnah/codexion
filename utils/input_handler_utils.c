/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 20:45:52 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/14 12:46:35 by mvelonja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_integer_value(char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	while (s[i])
	{
		if ((s[i] < '0' || s[i] > '9'))
			return (0);
		i++;
	}
	return (1);
}

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

long	ft_atoi(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	if (!str)
		return (0);
	if (str[i] == '+' && str[i + 1] != '-')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		result *= 10;
		result += str[i++] - 48;
	}
	result *= sign;
	return (result);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
