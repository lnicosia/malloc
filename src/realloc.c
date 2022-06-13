/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 11:52:52 by lnicosia          #+#    #+#             */
/*   Updated: 2021/10/25 17:37:36 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "malloc.h"
#include "libft.h"

// If the asked realloc changes the page type
int		is_type_changing(size_t old, size_t new)
{
	if (old <= TINY_BLOCK && new > TINY_BLOCK)
		return (1);
	if (old <= SMALL_BLOCK && (new > SMALL_BLOCK || new <= TINY_BLOCK))
		return (1);
	if (old > SMALL_BLOCK && new <= SMALL_BLOCK)
		return (1);
	return (0);
}

void	*find_in_page(void *ptr, size_t size, size_t type, t_page *page)
{
	t_malloc	*mem;
	size_t		diff;
	void		*res;

	pthread_mutex_lock(&g_mutex);
	while (page)
	{
		if (type == LARGE)
			type = page->used_space;
		//ft_printf("Checking if %p is between %p and %p\n", ptr,
		//page->start, page->start + type);
		if (ptr >= page->start && ptr <= page->start + type)
		{
			mem = page->mem;
			while (mem)
			{
				diff = size - mem->size;
				if (mem->start == ptr)
				{
					//ft_printf("Found %p\n", ptr);
					// Case where we reduce the size
					if (size <= mem->size && type != LARGE)
					{
						// Defragmentation:
						// if we can fit a new block, do it
						// (without breaking the alignment of course)
						if (mem->size - size > BLOCK_METADATA
							&& mem->size - size % 16 == 0)
						{
							new_block(mem, 16, size);
							page->used_space += BLOCK_METADATA;
						}
						//ft_printf("Returning %p\n", mem->start);
						pthread_mutex_unlock(&g_mutex);
						return (mem->start);
					}
					// Case where we can increase the size of our current block
					else if (!is_type_changing(mem->size, size)
						&& page->used_space + diff <= type && !mem->next)
					{
						page->used_space += diff;
						mem->size += diff;
						//show_alloc_mem();
						pthread_mutex_unlock(&g_mutex);
						return (mem->start);
					}
					else
					{
						pthread_mutex_unlock(&g_mutex);
						//ft_printf("Need new alloc\n");
						if (!(res = malloc(size)))
							return (0);
						//ft_printf("Malloc from realloc ok\n");
						ft_memcpy(res, mem->start, mem->size);
						//ft_printf("Need to free\n");
						free(ptr);

						//ft_printf("Returning %p\n", res);
						return (res);
					}
					pthread_mutex_unlock(&g_mutex);
					return (0);
				}
				mem = mem->next;
			}
		}
		page = page->next;
	}
	pthread_mutex_unlock(&g_mutex);
	return (0);
}

// Search for the ptr in all the pages in order
// TODO - optimize according to the size arg
void	*find_ptr(void *ptr, size_t size)
{
	void	*res;

	if ((res = find_in_page(ptr, size, TINY, g_memory.tiny)) != 0)
		return (res);
	if ((res = find_in_page(ptr, size, SMALL, g_memory.small)) != 0)
		return (res);
	if ((res = find_in_page(ptr, size, LARGE, g_memory.large)) != 0)
		return (res);
	//custom_error("Didnt find %p in any page\n", ptr);
	return (0);
}

void	*realloc(void *ptr, size_t size)
{
	void	*res;

	//ft_printf("Reallocating %p to %d\n", ptr, size);
	//if ((size_t)ptr % (size_t)16 != 0)
			//custom_error("{red} NOT ALIGNED!!{reset}\n");
	//show_alloc_mem();
	if (!ptr)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (0);
	}
	if ((res = find_ptr(ptr, size)) == 0)
	{
		//custom_error("Warning - %p is uninitialized\n", ptr);
		return (NULL);
		//return (malloc(size));
	}
	//ft_printf("Returning %p from realloc\n", res);
	//show_alloc_mem();
	return (res);
}

void	*reallocf(void *ptr, size_t size)
{
	//ft_printf("CC reallocf(%p, %d)\n", ptr, size);
	return (realloc(ptr, size));
}

void	*reallocarray(void *ptr, size_t nmemb, size_t size)
{
	//ft_printf("CC reallocarray(%p, %d, %d)\n", ptr, nmemb, size);
	if (nmemb * size > INT_MAX)
		return (NULL);
	return (realloc(ptr, nmemb * size));
}
