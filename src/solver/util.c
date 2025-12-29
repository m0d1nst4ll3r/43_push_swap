/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 09:50:22 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/23 11:23:19 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

// Searches for val in array
// Returns index of val OR first higher value
// If no higher value, returns -1
int	bsearch_higher(int *arr, int len, int val)
{
	int	l;
	int	r;
	int	m;

	l = 0;
	r = len - 1;
	while (l <= r)
	{
		m = (r - l) / 2 + l;
		if (arr[m] < val)
			l = m + 1;
		else if (arr[m] > val)
			r = m - 1;
		else
			return (m);
	}
	if (l < len)
		return (l);
	return (-1);
}

int	is_reverse_sorted(t_stack *head)
{
	t_stack *cur;

	cur = head;
	while (1)
	{
		if (cur->next != head && cur->val < cur->next->val)
			return (0);
		cur = cur->next;
		if (cur == head)
			return (1);
	}
}
