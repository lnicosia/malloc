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
		if (type == LARGE)
			munmap(tmp, tmp->used_space);
		else
			munmap(tmp, type);
	}
	return (0);
}

 __attribute__ ((destructor)) void	free_after_main()
{
	pthread_mutex_lock(&g_mutex);
	free_page(&g_memory.tiny, TINY);
	free_page(&g_memory.small, SMALL);
	free_page(&g_memory.large, LARGE);
	pthread_mutex_unlock(&g_mutex);
	if (pthread_mutex_destroy(&g_mutex))
		custom_error("Mutex destroy error\n");
}
