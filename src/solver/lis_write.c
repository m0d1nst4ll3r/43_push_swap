/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_write.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 14:59:08 by rapohlen          #+#    #+#             */
/*   Updated: 2026/01/04 15:19:22 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

static int	get_last_lis_index(int *lis_len, int num_elem)
{
	int	i;
	int	max;

	i = 1;
	max = 0;
	while (i < num_elem)
	{
		if (lis_len[i] > lis_len[max])
			max = i;
		i++;
	}
	return (max);
}

void	write_boolean_flags(t_stack *head, int *lis_len, int *lis_sub,
		int num_elem)
{
	t_stack	*cur;
	int		i;
	int		next_index;

	next_index = get_last_lis_index(lis_len, num_elem);
	cur = head->prev;
	i = num_elem - 1;
	while (next_index != -1)
	{
		while (i > next_index)
		{
			cur = cur->prev;
			i--;
		}
		cur->lis = true;
		next_index = lis_sub[next_index];
	}
}
