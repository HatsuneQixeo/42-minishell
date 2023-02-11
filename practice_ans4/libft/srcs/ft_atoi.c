/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:57:19 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/07/11 13:09:45 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_under_over_flow(const char *str, int ans)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 8 && str[i] <= 13))
		i++;
	if ((str[i] != '-') && ans < 0)
		return (-1);
	else if ((str[i] == '-') && ans > 0)
		return (0);
	else
		return (ans);
}

int	get_result(int i, const char *str)
{
	int	result;

	result = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;
	int	ans;

	i = 0;
	sign = 1;
	result = 0;
	ans = 0;
	while (str[i] == ' ' || (str[i] >= 8 && str[i] <= 13))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		if (!(str[i + 1] >= '0' && str[i + 1] <= '9'))
			return (0);
		i++;
	}
	result = get_result(i, str);
	ans = result * sign;
	return (check_under_over_flow(str, ans));
}
