/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_store.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:29:56 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/19 14:29:57 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

extern t_global	g_g;

void			proc_sti(void *data)
{
	t_process	*proc;
	t_codes		cod_b;
	int			toskip;
	int			arg[3];

	toskip = COMMAND;
	proc = (t_process*)data;
	cod_b = coding_byte(proc->pc + toskip);
	toskip += CODING_BYTE;
	//ft_printf("field %#x : %b %b %b\n", get_field_val(proc->pc), cod_b.t[0], cod_b.t[1], cod_b.t[2]);
	if (cod_b.t[0] != TREG || !cod_b.t[1] || (cod_b.t[1] != TDIR && cod_b.t[2] != TREG))
	{
		proc->pc = set_pos(proc->pc + toskip);
		return ;
	}
	if (!parse_arg(cod_b.t[0], proc, &arg[0], &toskip) ||
		!parse_arg(cod_b.t[1], proc, &arg[1], &toskip) ||
		!parse_arg(cod_b.t[2], proc, &arg[2], &toskip))
	{
		proc->pc = set_pos(proc->pc +  + count_total_skip(cod_b, 1, 2));
		return ;
	}
	arg[0] = proc->registry[arg[0]];

	if (cod_b.t[1] == TREG)
		arg[1] = proc->registry[arg[1]];
	else if (cod_b.t[1] == TIND)
		arg[1] = get_int(proc->pc + arg[1], 4);

	if (cod_b.t[2] == TREG)
		arg[2] = proc->registry[arg[2]];
	
	set_int(proc->pc + (arg[0] + arg[1]) % IDX_MOD, 4, proc->registry[arg[2]]);
	proc->pc = set_pos(proc->pc + toskip);
}