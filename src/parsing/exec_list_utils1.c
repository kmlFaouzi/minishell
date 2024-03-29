/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaouzi <kfaouzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:04:31 by kfaouzi           #+#    #+#             */
/*   Updated: 2022/11/20 10:30:17 by kfaouzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"

t_execlst	*init_execlst(void)
{
	t_execlst	*e;

	e = ft_malloc(sizeof(t_execlst));
	e->cmd = NULL;
	e->red = NULL;
	e->next = NULL;
	return (e);
}

t_execlst	*getcmd(t_execlst *e, char *val)
{
	size_t	i;
	char	**new;

	if (!e)
		e = init_execlst();
	i = 0;
	while (e->cmd && e->cmd[i])
		i++;
	new = ft_malloc(sizeof(char *) * (i + 2));
	new[i] = val;
	new[i + 1] = NULL;
	while ((int)--i >= 0 && e->cmd && e->cmd[i])
		new[i] = e->cmd[i];
	i = 0;
	return (e->cmd = new, e);
}

t_enum	get_redtype(char *val)
{
	if (!ft_strcmp(val, STR_OUTR))
		return (REDOUT);
	else if (!ft_strcmp(val, STR_APND))
		return (APPND);
	else if (!ft_strcmp(val, STR_INR))
		return (REDIN);
	else if (!ft_strcmp(val, STR_HRDC))
		return (HEREDC);
	return (NON);
}

t_red	*new_red(t_tok *tok)
{
	t_red	*head;

	head = ft_malloc(sizeof(t_red));
	head->type = get_redtype(tok->value);
	head->file = tok->next->value;
	head->next = NULL;
	return (head);
}

t_red	*getredlst(t_red *red, t_tok *tok)
{
	t_red	*t;

	if (!red)
	{
		red = new_red(tok);
		if (!red)
			return (NULL);
	}
	else
	{
		t = red;
		while (t->next)
			t = t->next;
		t->next = new_red(tok);
		if (!t->next)
			return (NULL);
	}
	return (red);
}
