/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_timize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 12:00:20 by rapohlen          #+#    #+#             */
/*   Updated: 2026/01/06 15:02:07 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

static void	del_op(t_op **list, t_op *to_remove)
{
	if (list && *list == to_remove)
		*list = to_remove->next;
	else
		to_remove->prev->next = to_remove->next;
	if (to_remove->next)
		to_remove->next->prev = to_remove->prev;
	free(to_remove);
}

static int	cancel_out(t_op **list, t_op *cur)
{
	if ((cur->op == SA && cur->next->op == SA)
		|| (cur->op == SB && cur->next->op == SB)
		|| (cur->op == SS && cur->next->op == SS)
		|| (cur->op == PA && cur->next->op == PB)
		|| (cur->op == PB && cur->next->op == PA)
		|| (cur->op == RA && cur->next->op == RRA)
		|| (cur->op == RRA && cur->next->op == RA)
		|| (cur->op == RB && cur->next->op == RRB)
		|| (cur->op == RRB && cur->next->op == RB))
	{
		del_op(list, cur->next);
		del_op(list, cur);
		return (1);
	}
	return (0);
}

static int	merge_rota(t_op *cur)
{
	t_op	*match;

	if (cur->op == RA || cur->op == RB || cur->op == RRA || cur->op == RRB)
	{
		match = cur->next;
		while (match && (match->op == RR || match->op == RRR))
			match = match->next;
		if ((cur->op == RA && match->op == RB)
			|| (cur->op == RB && match->op == RA))
		{
			cur->op = RR;
			del_op(NULL, match);
			return (1);
		}
		else if ((cur->op == RRA && match->op == RRB)
			|| (cur->op == RRB && match->op == RRA))
		{
			cur->op = RRR;
			del_op(NULL, match);
			return (1);
		}
	}
	return (0);
}

static int	merge_swap(t_op *cur)
{
	if ((cur->op == SA && cur->next->op == SB)
		|| (cur->op == SB && cur->next->op == SA))
	{
		cur->op = SS;
		del_op(NULL, cur->next);
		return (1);
	}
	else if ((cur->op == SA && cur->next->op == SS)
		|| (cur->op == SS && cur->next->op == SA))
	{
		cur->op = SB;
		del_op(NULL, cur->next);
		return (1);
	}
	else if ((cur->op == SB && cur->next->op == SS)
		|| (cur->op == SS && cur->next->op == SB))
	{
		cur->op = SA;
		del_op(NULL, cur->next);
		return (1);
	}
	return (0);
}

void	optimize_op_list(t_op **list)
{
	t_op	*cur;

	cur = *list;
	while (cur && cur->next)
	{
		if (cancel_out(list, cur)
			|| merge_rota(cur)
			|| merge_swap(cur))
			cur = *list;
		else
			cur = cur->next;
	}
}
