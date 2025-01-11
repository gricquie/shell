
#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft.h"

# define CHAR_BEFORE (mod.space || mod.plus || nb < 0)
# define U_INTMAX 4294967296

typedef struct	s_pad
{
	int			width;
	int			prec;
}				t_pad;

typedef struct	s_mod
{
	t_pad		pad;
	int			maj;
	int			zero;
	int			sharp;
	int			minus;
	int			plus;
	int			space;
	int			l;
	int			apos;
	int			ml;
	int			valid;
}				t_mod;

int				ft_printf(const char *str, ...);

int				printf_calcsizeint(char format, va_list ap, t_mod mod);
int				printf_calcsizestr(char format, va_list ap, t_mod mod);

int				flag_s(va_list ap, t_mod mod);
int				flag_p(va_list ap, t_mod mod);
int				flag_d(va_list ap, t_mod mod);
int				flag_o(va_list ap, t_mod mod);
int				flag_u(va_list ap, t_mod mod);

int				flag_x(va_list ap, t_mod mod);
int				flag_c(va_list ap, t_mod mod);
int				flag_ls(va_list ap, t_mod mod);
int				flag_lc(va_list ap, t_mod mod);
int				flag_prc(t_mod mod);

int				flag_f(va_list ap, t_mod mod);
int				flag_e(va_list ap, t_mod mod);
int				flag_g(va_list ap, t_mod mod);
int				flag_a(va_list ap, t_mod mod);
int				flag_n(va_list ap, int final);

int				flag_b(va_list ap, t_mod mod);
void			color(const char **str, int *final);

int				calc_exp(long double *n);
int				print_double_prec(long double n, int prec);
long double		cut_double(long double n, int prec);

t_mod			search_mod(const char **str, va_list ap);

int				parsing(const char *str);

int				print_base(unsigned long long int n, char *base);
int				print_pad(int len, t_mod mod);
int				print_prec(int len, t_mod mod);
int				nbrlen_base(unsigned long long int n, int base);
int				print_apos(unsigned long long int n, t_mod mod);

long long int	type(va_list ap, t_mod mod);

int				generalflag(void *data, t_mod mod, int (*flen)(void *, t_mod), int (*print)(void *, int len, t_mod));

#endif
