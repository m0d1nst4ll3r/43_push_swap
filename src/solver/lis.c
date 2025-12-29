/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 22:48:04 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/23 11:56:51 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

static int	get_lis_len(t_stack *head, int *arr)
{
	t_stack	*cur;
	int		len;
	int		ret;

	len = 0;
	cur = head;
	while (1)
	{
		ret = bsearch_higher(arr, len, cur->val);
		if (ret == -1)
		{
			arr[len] = cur->val;
			len++;
		}
		else
			arr[ret] = cur->val;
		cur = cur->next;
		if (cur == head)
			return (len);
	}
}

static t_stack	*get_lis_addr(t_stack *head, int *arr)
{
	t_stack	*cur;
	int		max_len;
	t_stack	*max_addr;
	int		ret;

	max_len = 0;
	cur = head;
	while (1)
	{
		ret = get_lis_len(cur, arr);
		if (ret > max_len)
		{
			max_len = ret;
			max_addr = cur;
		}
		cur = cur->next;
		if (cur == head)
			return (max_addr);
	}
}

void	write_lis()
