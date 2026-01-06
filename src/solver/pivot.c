/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pivot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 15:25:41 by rapohlen          #+#    #+#             */
/*   Updated: 2026/01/06 15:08:58 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

static int	fill_pivot_arr(t_stack *head, int *arr)
{
	t_stack	*cur;
	int		i;

	i = 0;
	cur = head;
	while (1)
	{
		if (!cur->lis)
		{
			arr[i] = cur->val;
			i++;
		}
		cur = cur->next;
		if (cur == head)
			return (i);
	}
}

int	get_pivot(t_stack *head, int *arr)
{
	int	len;

	len = fill_pivot_arr(head, arr);
	ft_select_sort(arr, len);
	return (arr[len / 2]);
}
