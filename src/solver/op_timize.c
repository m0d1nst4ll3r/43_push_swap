/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_timize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 12:00:20 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/30 15:54:36 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

static void	del_op(t_op **list, t_op *to_remove)
{
	if (*list == to_remove)
		*list = to_remove->next;
	else
		to_remove->prev->next = to_remove->next;
	if (to_remove->next)
		to_remove->next->prev = to_remove->prev;
	free(to_remove);
}

static t_op	*merge_rr(t_op **list, t_op *cur)
{
	cur->op = RR_KEY;
	del_op(list, cur->next);
	if (cur->prev)
		return (cur->prev);
	return (cur);
}

static t_op	*merge_rrr(t_op **list, t_op *cur)
{
	cur->op = RRR_KEY;
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

void	optimize_op_list(t_op **list)
{
	t_op	*cur;

	cur = *list;
	while (cur && cur->next)
	{
		if ((cur->op == SA_KEY && cur->next->op == SA_KEY)
				|| (cur->op == SB_KEY && cur->next->op == SB_KEY)
				|| (cur->op == PA_KEY && cur->next->op == PB_KEY)
				|| (cur->op == PB_KEY && cur->next->op == PA_KEY)
				|| (cur->op == RA_KEY && cur->next->op == RRA_KEY)
				|| (cur->op == RRA_KEY && cur->next->op == RA_KEY)
				|| (cur->op == RB_KEY && cur->next->op == RRB_KEY)
				|| (cur->op == RRB_KEY && cur->next->op == RB_KEY))
			cur = cancel_out(list, cur);
		else if ((cur->op == RA_KEY && cur->next->op == RB_KEY)
				|| (cur->op == RB_KEY && cur->next->op == RA_KEY))
			cur = merge_rr(list, cur);
		else if ((cur->op == RRA_KEY && cur->next->op == RRB_KEY)
				|| (cur->op == RRB_KEY && cur->next->op == RRA_KEY))
			cur = merge_rrr(list, cur);
		else
			cur = cur->next;
	}
}
