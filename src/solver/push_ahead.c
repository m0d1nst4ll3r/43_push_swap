/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_ahead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 15:48:29 by rapohlen          #+#    #+#             */
/*   Updated: 2026/01/06 17:55:52 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

static int	get_end_index(t_stack *head, int num_elem)
{
	int		end;
	int		i;

	end = -1;
	i = 0;
	while (i < num_elem)
	{
		if (!head->lis)
			end = i;
		head = head->next;
		i++;
	}
	return (end);
}

// How to optimize the first push is complex
// We do it naively and very much not optimally
// We simply rotate (ra) when needed, until we reach the last value to be pushed
// In some cases, this is not optimized, e.g:
//	0 1 1 0
// In this case we will pb ra ra pb
// We could instead pb rra pb
// The more consecutive 1's, the worse this gets
// However, consecutive 1's are extremely rare in a truly random list, and in
//	such a case, the stack is already sorted almost entirely, so operation
//	count will be low anyway.
// Note that sometimes you do pb rb, then ra (to skip a LIS value)
// This is not directly merged into rr, but will be eventually during op_timize
// Note that we possibly do pb rb on our very first operation, in this case the
//	rb would be wasted, but we have guardrails built into our operation
//	functions which will ensure we do NOT write a useless rb.
void	push_ahead(t_solver *d)
{
	t_stack	*cur;
	t_stack	*next;
	int		end;
	int		i;

	end = get_end_index(d->stacka, d->num_elem);
	cur = d->stacka;
	i = 0;
	while (i <= end)
	{
		next = cur->next;
		if (!cur->lis)
		{
			do_op(d, PB);
			if (cur->val < d->pivot)
				do_op(d, RB);
		}
		else
			do_op(d, RA);
		cur = next;
		i++;
	}
}
