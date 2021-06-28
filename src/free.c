/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:53:00 by lnicosia          #+#    #+#             */
/*   Updated: 2021/06/28 12:04:31 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"

void	check_page(void *ptr, t_page *page)
{
	t_malloc	*mem;
	t_malloc	**to_remove;

	ft_printf("Checking page %p\n", page->start);
	while (page)
	{
		// Check if our ptr is in this page
		if (ptr >= page->start && ptr <= page->start + TINY)
		{
			ft_printf("Our ptr is in this page\n");
			mem = page->mem;
			while (mem)
			{
				// Check if the next node is our ptr
				if (mem->next)
				{
					// It is, let's remove it
					if (mem->next->start == ptr)
					{
						to_remove = &mem->next;
						mem->next = mem->next->next;
						if (munmap(*to_remove, sizeof(*to_remove)))
						{
							return ;
							ft_perror("Unmap error:");
						}
						return ;
					}
				}
				// Case where we only have one alloc in the page
				if (mem->start == ptr)
				{
					
				}
				mem = mem->next;
			}
		}
		page = page->next;
	}
}

void	free2(void *ptr)
{
	if (!ptr)
		return ;
	ft_printf("Freeing %p\n", ptr);
	check_page(ptr, g_memory.tiny);
	check_page(ptr, g_memory.small);
	check_page(ptr, g_memory.large);
}

void	*fatal_error(void)
{
	while (g_memory.tiny)
	{
		
	}
	return (0);
}