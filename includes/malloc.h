/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:32:58 by lnicosia          #+#    #+#             */
/*   Updated: 2021/06/30 11:41:58 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include <stddef.h>
# include <sys/mman.h>
# include <unistd.h>

# define PAGE_METADATA	sizeof(t_page)
# define BLOCK_METADATA	sizeof(t_malloc)
# define TINY			(size_t)getpagesize() * 4
# define SMALL			(size_t)getpagesize() * 400
# define LARGE			(size_t)getpagesize() * 4000
# define TINY_BLOCK		(TINY - PAGE_METADATA) / 100 - BLOCK_METADATA
# define SMALL_BLOCK	(SMALL - PAGE_METADATA) / 100 - BLOCK_METADATA
# define LARGE_BLOCK	(LARGE - PAGE_METADATA) / 100 - BLOCK_METADATA

# ifndef EXTERN
#  define EXTERN extern
# endif

typedef struct		s_malloc
{
	void			*start;
	size_t			size;
	size_t			used;
	struct s_malloc	*next;
}					t_malloc;

typedef struct		s_page
{
	void			*start;
	size_t			used_space;
	t_malloc		*mem;
	struct s_page	*next;
}					t_page;


typedef struct		s_memory
{
	t_page			*tiny;
	t_page			*small;
	t_page			*large;
}					t_memory;

EXTERN t_memory		g_memory;

void		free2(void *ptr);
void		*malloc2(size_t size);
void		*realloc(void *ptr, size_t size);
void		show_alloc_mem(void);
void		*fatal_error(void);

#endif