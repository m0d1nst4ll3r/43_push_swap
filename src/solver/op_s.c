/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:57:51 by rapohlen          #+#    #+#             */
/*   Updated: 2026/01/05 19:57:03 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

static int	do_sx(t_stack **head)
{
	t_stack	*tmp;

	if (!*head || (*head)->next == *head)
		return (0);
	tmp = (*head)->next;
	if ((*head)->next != (*head)->prev)
	{
		(*head)->next->next->prev = *head;
		(*head)->prev->next = (*head)->next;
		(*head)->next->prev = (*head)->prev;
		(*head)->prev = (*head)->next;
		(*head)->next = (*head)->next->next;
		tmp->next = *head;
	}
	*head = tmp;
	return (1);
}

void	do_sa(t_solver *d)
{
	if (do_sx(&d->stacka))
		add_op(d, SA);
}

void	do_sb(t_solver *d)
{
	if (do_sx(&d->stackb))
		add_op(d, SB);
}

// Reminder: we will optimize op list anyway, it's fine not to write SS yet
void	do_ss(t_solver *d)
{
	do_sa(d);
	do_sb(d);
}
