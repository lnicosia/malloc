/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:32:58 by lnicosia          #+#    #+#             */
/*   Updated: 2021/06/25 19:07:11 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include <stddef.h>
# include <sys/mman.h>

# define TINY	(size_t)getpagesize()
# define SMALL	(size_t)getpagesize() * 100
# define LARGE	(size_t)getpagesize() * 1000

# ifndef EXTERN
#  define EXTERN extern
# endif

typedef struct		s_malloc
{
	void			*start;
	void			*end;
	size_t			size;
	struct s_malloc	*next;
}					t_malloc;

typedef struct		s_page
{
	void			*start;
	void			*curr;
	size_t			length;
	t_malloc		*mem;
	struct s_page	*next;
}					t_page;


typedef struct		s_memory
{
	t_page			*tiny;
	t_page			*small;
	t_page			*large;
	size_t			nb_tiny;
	size_t			nb_small;
	size_t			nb_large;
}					t_memory;

EXTERN t_memory		g_memory;

void		free2(void *ptr);
void		*malloc2(size_t size);
void		*realloc(void *ptr, size_t size);
void		show_alloc_mem(void);
void		*fatal_error(void);

#endif