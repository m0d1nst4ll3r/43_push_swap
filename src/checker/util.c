/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:01:31 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/16 19:22:49 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	find_op(char *s, char **op_list)
{
	int	i;
	int	j;

	i = 0;
	while (i < N_OP)
	{
		j = 0;
		while (s[j] && s[j] == op_list[i][j])
			j++;
		if (s[j] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

t_stack	*get_last(t_stack *stack)
{
	if (!stack)
		return (stack);
	while (stack->next)
		stack = stack->next;
	return (stack);
}

t_stack	*get_before_last(t_stack *stack)
{
	if (!stack || !stack->next)
		return (stack);
	while (stack->next->next)
		stack = stack->next;
	return (stack);
}
