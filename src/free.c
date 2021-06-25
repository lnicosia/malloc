/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:53:00 by lnicosia          #+#    #+#             */
/*   Updated: 2021/06/25 19:07:39 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	free2(void *ptr)
{
	if (!ptr)
		return ;
	munmap(ptr, 4096);
}

void	*fatal_error(void)
{
	while (g_memory.tiny)
	{
		
	}
	return (0);
}