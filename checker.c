/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 12:52:13 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/16 19:06:58 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	build_stack(t_stack **stack, char **av)
{
	t_stack	*last;
	t_stack	*cur;
	int		i;
	int		val;

	i = 1;
	while (av[i])
	{
		if (ft_atoi_strict(av[i], &val))
			return (1);
		cur = malloc(sizeof(*cur));
		if (!cur)
			return (1);
		if (!*stack)
			*stack = cur;
		else
			last->next = cur;
		cur->next = NULL;
		cur->val = val;
		last = cur;
		i++;
	}
	return (0);
}

int	check_duplicates(t_stack *stack)
{
	t_stack	*cur;
	int		to_check;

	while (stack)
	{
		to_check = stack->val;
		cur = stack->next;
		while (cur)
		{
			if (to_check == cur->val)
				return (1);
			cur = cur->next;
		}
		stack = stack->next;
	}
	return (0);
}

// GNL does not let us differentiate between the file ending OR a malloc failing
int	read_input(t_op **op, char **op_list)
{
	t_op	*cur;
	t_op	*last;
	int		ret;
	char	*line;

	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		ret = find_op(line, op_list);
		if (ret == -1)
			return (1);
		cur = malloc(sizeof(*cur));
		if (!cur)
			return (1);
		if (!*op)
			*op = cur;
		else
			last->next = cur;
		cur->next = NULL;
		cur->op = ret;
		last = cur;
	}
	return (0);
}

void	apply_input(t_checker *d)
{
	t_op	*curop;

	curop = d->op;
	while (curop)
	{
		d->ops[curop->op](d);
		curop = curop->next;
	}
}

int	is_sorted(t_stack *stack)
{
	while (stack)
	{
		if (stack->next && stack->val > stack->next->val)
			return (0);
		stack = stack->next;
	}
	return (1);
}
