/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_rr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:07:51 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/16 18:09:15 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	do_rrx(t_stack **stack)
{
	t_stack	*before_last;

	if (!*stack || !(*stack)->next)
		return ;
	before_last = get_before_last(*stack);
	before_last->next->next = *stack;
	*stack = before_last->next;
	before_last->next = NULL;
}

void	do_rra(t_checker *d)
{
	do_rrx(&d->stacka);
}

void	do_rrb(t_checker *d)
{
	do_rrx(&d->stackb);
}

void	do_rrr(t_checker *d)
{
	do_rrx(&d->stacka);
	do_rrx(&d->stackb);
}
