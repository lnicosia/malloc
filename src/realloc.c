/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 11:52:52 by lnicosia          #+#    #+#             */
/*   Updated: 2021/06/30 11:57:35 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*realloc2(void *ptr, size_t size)
{
	(void)ptr;
	(void)size;
	if (!ptr)
		return (malloc2(size));
	if (size == 0)
	{
		free2(ptr);
		return (0);
	}
	return (0);
}