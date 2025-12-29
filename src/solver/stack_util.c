/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:05:59 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/23 11:25:01 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

t_stack *stack_new(int val)
{
	t_stack	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->next = new;
	new->prev = new;
	new->val = val;
	new->lis = false;
	return (new);
}

void	stack_add_front(t_stack **head, t_stack *elem)
{
	if (!*head)
		*head = elem;
	else
	{
		elem->next = *head;
		elem->prev = (*head)->prev;
		(*head)->prev->next = elem;
		(*head)->prev = elem;
		*head = elem;
	}
}

void	stack_add_back(t_stack **head, t_stack *elem)
{
	if (!*head)
		*head = elem;
	else
	{
		elem->next = *head;
		elem->prev = (*head)->prev;
		(*head)->prev->next = elem;
		(*head)->prev = elem;
	}
}

t_stack	*stack_unlink(t_stack **head)
{
	t_stack	*unlinked;

	if (!*head)
		return (NULL);
	unlinked = *head;
	if (unlinked->next == unlinked)
		*head = NULL;
	else
	{
		unlinked->prev->next = unlinked->next;
		unlinked->next->prev = unlinked->prev;
		*head = unlinked->next;
		unlinked->next = unlinked;
		unlinked->prev = unlinked;
	}
	return (unlinked);
}
