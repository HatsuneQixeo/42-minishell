/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 09:18:31 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/03 16:23:36 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
   <limits.h> is used in print_decimal. It uses the declration of INT_MIN.
*/
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>

int				ft_printf(const char *str, ...);
int				flag_check_bonus(char c);

typedef struct s_fmt
{
	va_list	args;
	int		c;
	int		print_len;
	int		str;
	int		ptr;
	int		decimal;
	int		integer;
	int		unsi;
	int		hexa_lower;
	int		hexa_upper;
	int		percent;
	int		negative;
	int		zero;
	int		dot;
	int		hash;
	int		space;
	int		plus;
	int		width;
	int		percision;
	int		pad;
	int		offset;
}	t_fmt;

void			fmt_init(t_fmt *fmt);
void			fmt_update(char c, t_fmt *fmt);
void			fmt_update_flags(char c, t_fmt *fmt);
int				fmt_operation(t_fmt *fmt, va_list args);

int				print_percent(t_fmt *fmt);
int				print_c(t_fmt *fmt, int c);
int				print_s(t_fmt *fmt, char *str);
int				print_decimal(t_fmt *fmt, int num);
void			print_space(t_fmt *fmt, int space_count);
int				print_hexa(t_fmt *fmt, unsigned int num);
int				print_unsi(t_fmt *fmt, unsigned int unsi);
int				print_ptr(t_fmt *fmt, unsigned long long ptr);
void			print_prefix_unsi(t_fmt *fmt, char *unsi_num_c);
void			print_prefix_nbr(t_fmt *fmt, int num, char *unsi_num_c);

unsigned int	absolute(int num);
char			*ft_uitoa(unsigned int n);
int				calc_unsi_num_len(unsigned int num, int base);
#endif
