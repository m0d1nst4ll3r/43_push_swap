/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_timize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 12:00:20 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/30 16:46:43 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

static t_op	*merge_rr(t_op **list, t_op *cur)
{
	cur->op = RR;
	del_op(list, cur->next);
	if (cur->prev)
		return (cur->prev);
	return (cur);
}

static t_op	*merge_rrr(t_op **list, t_op *cur)
{
	cur->op = RRR;
	del_op(list, cur->next);
	if (cur->prev)
		return (cur->prev);
	return (cur);
}

static t_op *cancel_out(t_op **list, t_op *cur)
{
	t_op	*tmp;

	if (cur->prev)
		tmp = cur->prev;
	else
		tmp = cur->next->next;
	del_op(list, cur->next);
	del_op(list, cur);
	return (tmp);
}

// How to do this
//	ra rr rb
// this one you simply iterate through rr and rrrs to find another rb, if you do,
// delete the rb and morph the ra into rr (or reverse)
//	ra rr pa pb rb
// here if you get ra, skip rr, you stop at pa
// but once you've cancelled out the pa pb, you're left with ra rr rb
// and if you only go back one after cancelling out, you're at rr
// you will never find the ra rb optimization

// the only simple way here is to do 2 passes
// a cancel-out pass (1st pass)
// then a merging pass (2nd pass)
// the cancel-out pass will still need to backtrack (case pa pa pa pb pb pb)
// the merging pass will need to skip rr/rrr
// so this needs to be recoded for optimal result
// yay

/* First pass - cancelling out
 *	ra + rra (rra + ra)
 *	rb + rrb (rrb + rb)
 *	pa + pb (pb + pa)
 *	sa + sa
 *	sb + sb
 * Note that we backtrack once to handle e.g (pa pa pa pb pb pb) case
 *
 * Second pass - merging
 *	ra + rb (rb + ra)
 *	rra + rrb (rrb + rra)
 * Note that we skip rr/rrr to handle e.g (ra rr rb) case
*/
void	optimize_op_list(t_op **list)
{
	t_op	*cur;

	cur = *list;
	while (cur && cur->next)
	{
		if ((cur->op == SA && cur->next->op == SA)
			|| (cur->op == SB && cur->next->op == SB)
			|| (cur->op == PA && cur->next->op == PB)
			|| (cur->op == PB && cur->next->op == PA)
			|| (cur->op == RA && cur->next->op == RRA)
			|| (cur->op == RRA && cur->next->op == RA)
			|| (cur->op == RB && cur->next->op == RRB)
			|| (cur->op == RRB && cur->next->op == RB))
			cur = cancel_out(list, cur);
		else
			cur = cur->next;
	}
	second_pass(list);
}

// Look for ra/rb or rra/rrb match (in any order)
static void	second_pass(t_op **list)
{
	t_op	*cur;
	t_op	*match;

	cur = *list;
	while (cur && cur->next)
	{
		if (cur->op == RA || cur->op == RB || cur->op == RRA || cur->op == RRB)
		{
		}
		else
			cur = cur->next;
		if ((cur->op == RA && cur->next->op == RB)
				|| (cur->op == RB && cur->next->op == RA))
			cur = merge_rr(list, cur);
		else if ((cur->op == RRA && cur->next->op == RRB)
				|| (cur->op == RRB && cur->next->op == RRA))
			cur = merge_rrr(list, cur);
	}
}
