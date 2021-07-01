/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 11:52:52 by lnicosia          #+#    #+#             */
/*   Updated: 2021/07/01 14:14:32 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"

void	*realloc_large(void *ptr, size_t size)
{
	/*void	*new;

	new = NULL;
	if (!(new = malloc2(size)))
		return (0);
	free2(ptr);
	return (new);*/
	(void)ptr;
	(void)size;
	return (0);
}

void	*find_in_page(void *ptr, size_t size, t_page *page)
{
	t_malloc	*mem;

	while (page)
	{
		if (ptr >= page->start && ptr <= page->start + page->used_space)
		{
			mem = page->mem;
			while (mem)
			{
				if (mem->start == ptr)
				{
					ft_printf("Found ptr (prev size = %d)\n", mem->size);
					// Case where a smaller size is requiered
					if (size <= mem->size)
					{
						ft_printf("New size fits in the block\n");
						// Defragmentation:
						// if we can fit a new block, do it
						if (mem->size - size > 32)
						{
							new_block(mem, size);
						}
						return (mem->start);
					}
					return (0);
				}
				mem = mem->next;
			}
		}
		page = page->next;
	}
	return (0);
}

// Search for the ptr in all the pages in order
// TODO - optimize according to the size arg
void	*find_ptr(void *ptr, size_t size)
{
	void	*res;

	ft_printf("Searching for %p\n", ptr);
	if ((res = find_in_page(ptr, size, g_memory.tiny)) != 0)
		return (res);
	if ((res = find_in_page(ptr, size, g_memory.small)) != 0)
		return (res);
	if ((res = find_in_page(ptr, size, g_memory.large)) != 0)
		return (res);
	return (0);
}

void	*realloc2(void *ptr, size_t size)
{
	void	*res;

	if (!ptr)
		return (malloc2(size));
	if (size == 0)
	{
		free2(ptr);
		return (0);
	}
	if ((res = find_ptr(ptr, size)) == 0)
	{
		custom_error("Warning - ptr is uninitialized\n");
		return (malloc2(size));
	}
	return (res);
}