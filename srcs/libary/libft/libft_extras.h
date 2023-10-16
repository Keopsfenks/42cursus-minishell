/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_extras.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 20:07:21 by ogenc             #+#    #+#             */
/*   Updated: 2023/10/16 20:40:52 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_EXTRAS_H
# define LIBFT_EXTRAS_H
# include <unistd.h>
# include <stdlib.h>

typedef struct s_arg
{
	char			*content;
	int				type;
	struct s_arg	*next;
}	t_arg;

int		ft_isalpha(int str);
int		ft_isalnum(int str);
int		ft_isdigit(int str);
int		ft_isascii(int str);
int		ft_isprint(int str);
size_t	ft_strlen(const char *str);
int		ft_toupper(int str);
int		ft_tolower(int str);
void	*ft_memset(void *dst, int src, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_bzero(void *dst, size_t len);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *src, int c);
char	*ft_strrchr(const char *str, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_atoi(const char *str);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
t_arg	*ft_lstnew(int type, void *content);
int		ft_lstsize(t_arg *lst);
t_arg	*ft_lstlast(t_arg *lst);
void	ft_lstadd_back(t_arg **lst, t_arg *new);
void	ft_lstadd_front(t_arg **lst, t_arg *new);
void	ft_lstdelone(t_arg *lst, void (*del)(void *));
void	ft_lstclear(t_arg **lst, void (*del)(void *));
void	ft_lstiter(t_arg *lst, void (*f)(void *));
#endif