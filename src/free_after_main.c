/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_after_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:29:55 by lnicosia          #+#    #+#             */
/*   Updated: 2022/06/13 10:58:57 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"

int		free_page(t_page **page, size_t type)
{
	t_page		*tmp;

	(void)type;
	(void)tmp;
	tmp = NULL;
	while (*page)
	{
		tmp = *page;
		*page = (*page)->next;
		//ft_printf("Freeing %p\n", tmp);
		munmap(tmp, type);
		// /ft_printf("Setting to null\n");
		*page = NULL;
		//ft_printf("Next\n");
	}
	return (0);
}

 __attribute__ ((destructor)) void	free_after_main()
{
	ft_printf("Memory after main:\n");
	show_alloc_mem_plus();
	pthread_mutex_lock(&g_mutex);
	//ft_printf("Freeing tiny pages\n");
	free_page(&g_memory.tiny, TINY);
	//ft_printf("Freeing small pages\n");
	free_page(&g_memory.small, SMALL);
	//ft_printf("Freeing large pages\n");
	free_page(&g_memory.small, LARGE);
	pthread_mutex_unlock(&g_mutex);
	ft_printf("Memory after frees:\n");
	show_alloc_mem_plus();
	if (pthread_mutex_destroy(&g_mutex))
		custom_error("Mutex destroy error\n");
}
