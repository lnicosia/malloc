/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:34:08 by lnicosia          #+#    #+#             */
/*   Updated: 2021/06/28 12:17:25 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define EXTERN
#include "malloc.h"

int		new_metadata(size_t type)
{
	t_page	*page;
	t_page	**page_addr;
	t_page	*new;

	if (type == TINY)
	{
		page = g_memory.tiny;
		page_addr = &g_memory.tiny;
		g_memory.nb_tiny++;
	}
	else if (type == SMALL)
	{
		page = g_memory.small;
		page_addr = &g_memory.small;
		g_memory.nb_small++;
	}
	else
	{
		page = g_memory.large;
		page_addr = &g_memory.large;
		g_memory.nb_large++;
	}
	while (page && page->next)
			page = page->next;
	if (!(new = mmap(0, sizeof(t_page), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0)))
		return (-1);
	if (!page)
		*page_addr = new;
	else
		page->next = new;
	return (0);
}

void	*new_malloc(size_t type, size_t size)
{
	t_page		*page;
	t_malloc	*new;
	void		*ptr;

	ptr = NULL;
	new = NULL;
	if (type == TINY)
		page = g_memory.tiny;		
	else if (type == SMALL)
		page = g_memory.small;		
	else
		page = g_memory.large;
	while (page->next)
		page = page->next;
	if (type != LARGE)
		ptr = mmap(0, type, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	else
		ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	page->start = ptr;
	page->end = ptr + size;
	page->used_space = size;
	if (!(new = mmap(0, sizeof(t_malloc), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0)))
		return (fatal_error());
	new->start = ptr;
	new->end = ptr + size;
	new->size = size;
	new->used = 1;
	page->mem = new;
	return (ptr);
}

void	*malloc2(size_t size)
{
	t_page		*page;
	t_malloc	*new;
	t_malloc	*mem;
	size_t		type;

	if (size <= TINY / 100)
	{
		page = g_memory.tiny;
		type = TINY;
	}
	else if (size <= SMALL / 100)
	{
		page = g_memory.small;
		type = SMALL;
	}
	else
	{
		page = g_memory.large;
		type = LARGE;
	}
	// Searching if we have some space available in our existing pages
	while (page)
	{
		// Defragmenting:
		// Checking if we have some place left between our existing allocs
		// before filling the end of the page
		mem = page->mem;
		while (mem && mem->next)
		{
			// If we can fit the new alloc between two existing ones
			// let's do it
			if (mem->used == 0 && mem->end != mem->next->start
				&& (long int)size <= mem->next->start - mem->end )
			{
				if (!(new = mmap(0, sizeof(t_malloc),
				PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0)))
					return (fatal_error());
				new->start = mem->end;
				new->end = new->start + size;
				new->size = size;
				new->used = 1;
				new->next = mem->next;
				mem->next = new;
				return (new->start);
			}
			mem = mem->next;
		}
		// No defragmentation possible
		// let's check if we have some place left after it
		if (page->used_space + size <= type)
		{
			mem = page->mem;
			while (mem && mem->next)
				mem = mem->next;
			if (!(new = mmap(0, sizeof(t_malloc),
				PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0)))
				return (fatal_error());
			new->start = page->end;
			// Incr length and the ptr
			page->used_space += size;
			page->end += size;
			new->end = page->end;
			new->size = size;
			new->used = 1;
			// Connect the list
			if (!page->mem)
				page->mem = new;
			else
				mem->next = new;
			// return the original ptr
			return (new->start);
		}
		page = page->next;
	}
	// We didnt find any space in our existing plage, let's create some
	// Failed to create a new page metadata
	if (new_metadata(type))
		return (fatal_error());
	return (new_malloc(type, size));
}