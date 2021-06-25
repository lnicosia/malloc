/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:34:08 by lnicosia          #+#    #+#             */
/*   Updated: 2021/06/25 19:58:46 by lnicosia         ###   ########.fr       */
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
	page->curr = ptr + size;
	page->length = size;
	if (!(new = mmap(0, sizeof(t_malloc), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0)))
		return (fatal_error());
	ft_printf("New page start = %p\n", ptr);
	new->start = ptr;
	new->end = ptr + size;
	new->size = size;
	page->mem = new;
	return (ptr);
}

void	*malloc2(size_t size)
{
	t_page		*page;
	t_malloc	*new;
	t_malloc	*old;
	size_t		type;

	if (size <= TINY / 100)
	{
		ft_printf("Tiny malloc\n");
		page = g_memory.tiny;
		type = TINY;
	}
	else if (size <= SMALL / 100)
	{
		ft_printf("Small malloc\n");
		page = g_memory.small;
		type = SMALL;
	}
	else
	{
		ft_printf("Large malloc\n");
		page = g_memory.large;
		type = LARGE;
	}
	// Searching if we have some space available in our existing pages
	while (page)
	{
		ft_printf("Place needed: %d. Actual place: %dB/%dB\n", size,
		page->length, type);
		// We found some place, let's return this address
		if (page->length + size <= type)
		{
			old = page->mem;
			while (old && old->next)
				old = old->next;
			if (!(new = mmap(0, sizeof(t_malloc),
				PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0)))
				return (fatal_error());
			new->start = page->curr;
			// Incr length and the ptr
			page->length += size;
			page->curr += size;
			new->end = page->curr;
			new->size = size;
			if (!page->mem)
				page->mem = new;
			else
				old->next = new;
			// return the original ptr
			return (new->start);
		}
		page = page->next;
	}
	// We didnt find any space in our existing plage, let's create some
	ft_printf("New tiny metadata\n");
	// Failed to create a new page metadata
	if (new_metadata(type))
		return (fatal_error());
	ft_printf("Allocating tiny zone\n");
	return (new_malloc(type, size));
}