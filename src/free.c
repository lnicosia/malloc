/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:53:00 by lnicosia          #+#    #+#             */
/*   Updated: 2021/07/08 16:27:43 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"

int		check_large_page(void *ptr, t_page *page)
{
	t_page		*prev;

	prev = NULL;
	while (page)
	{
		// Check if the ptr is in the next page so we can remove the node
		// easily if empty afterwards
		if (ptr == page->mem->start)
		{
			// Specific case if it's the first node
			if (prev == NULL)
				g_memory.large = page->next;
			else
				prev->next = page->next;
			// Unmapping the actual memory
			munmap(page, page->used_space);
			return (1);
		}
		prev = page;
		page = page->next;
	}
	return (0);
}

int		check_page(void *ptr, t_page *page, size_t type)
{
	t_malloc	*mem;
	t_malloc	*prev_mem;
	t_page		*prev;

	prev = NULL;
	while (page)
	{
		// Check if the ptr is in the next page so we can remove the node
		// easily if empty afterwards
		if (ptr >= page->start && ptr <= page->start + type)
		{
			prev_mem = NULL;
			mem = page->mem;
			while (mem)
			{
				if (mem->start == ptr)
				{
					if (mem->used == 0)
					{
						custom_error("Error - Attempting double free on %p\n", ptr);
						return (1);
					}
					mem->used = 0;
					page->used_space -= mem->size + BLOCK_METADATA;
					// If the block before is free, merge with it
					if (prev_mem && prev_mem->used == 0)
					{
						prev_mem->size += mem->size + BLOCK_METADATA;
						prev_mem->next = mem->next;
					}
					// If the block after is free, merge with it
					if (mem->next && mem->next->used == 0)
					{
						mem->size += mem->next->size + BLOCK_METADATA;
						mem->next = mem->next->next;
					}
					break ;
				}
				prev_mem = mem;
				mem = mem->next;
			}
			// If our plage is now empty, unmap it
			if (page->used_space == PAGE_METADATA)
			{
				// Specific case if it's the first node
				if (prev == NULL)
				{
					if (type == TINY)
						g_memory.tiny = page->next;
					else if (type == SMALL)
						g_memory.small = page->next;
					else
						g_memory.large = page->next;
				}
				else
					prev->next = page->next;
				// Unmapping the actual memory
				if (type != LARGE)
					munmap(page, type);
				else
					munmap(page, page->used_space);
			}
			return (1);
		}
		prev = page;
		page = page->next;
	}
	return (0);
}

void	free(void *ptr)
{
	ft_printf("Freeing %p\n", ptr);
	if ((size_t)ptr % (size_t)16 != 0)
			custom_error("{red} NOT ALIGNED!!{reset}\n");
	if (!ptr)
		return ;
	pthread_mutex_lock(&g_mutex);
	if (check_page(ptr, g_memory.tiny, TINY))
	{
		ft_printf("Tiny free ok\n");
		//show_alloc_mem();
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	if (check_page(ptr, g_memory.small, SMALL))
	{
		ft_printf("Small free ok\n");
		//show_alloc_mem();
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	if (check_large_page(ptr, g_memory.large))
	{
		ft_printf("Large free ok\n");
		//show_alloc_mem();
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	pthread_mutex_unlock(&g_mutex);
}

void	*fatal_error(void)
{
	custom_error("{red}Fatal error{reset}\n");
	while (g_memory.tiny)
	{
		
	}
	exit(0);
	return (0);
}