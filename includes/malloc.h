/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:32:58 by lnicosia          #+#    #+#             */
/*   Updated: 2022/06/13 16:19:29 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include <stddef.h>
# include <sys/mman.h>
# include <unistd.h>
# include <pthread.h>

# define PAGE_METADATA	sizeof(t_page)
# define BLOCK_METADATA	sizeof(t_malloc)
# define TINY			(size_t)getpagesize() * 4
# define SMALL			(size_t)getpagesize() * 400
# define LARGE			(size_t)getpagesize() * 4000
# define TINY_BLOCK		(TINY - PAGE_METADATA) / 128 - BLOCK_METADATA
# define SMALL_BLOCK	(SMALL - PAGE_METADATA) / 128 - BLOCK_METADATA
# define LARGE_BLOCK	(LARGE - PAGE_METADATA) / 128 - BLOCK_METADATA

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

typedef struct		s_thread
{

	pthread_once_t	init;
	char			padding[4];
}					t_thread;


EXTERN t_memory		g_memory;
EXTERN pthread_mutex_t	g_mutex;

void		free(void *ptr);
void		*memalign(size_t alignment, size_t size);
void		*malloc(size_t size);
void		*calloc(size_t nmemb, size_t size);
void		*realloc(void *ptr, size_t size);
void		*reallocf(void *ptr, size_t size);
void		*reallocarray(void *ptr, size_t nmemb, size_t size);
int			posix_memalign(void **memptr, size_t alignment, size_t size);
void		*aligned_alloc(size_t alignment, size_t size);
void		*valloc(size_t size);
void		*pvalloc(size_t size);
void		show_alloc_mem(void);
void		show_alloc_mem_plus(void);
void		show_alloc_mem_ex(void);
int			new_block(t_malloc *mem, size_t alignment, size_t size);
int			is_power_of_two(size_t nb);

#endif
