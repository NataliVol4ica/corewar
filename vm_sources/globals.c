/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:11:55 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/16 16:11:55 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_global	g_g;
t_func		g_funcs[] =
{
	{0x01, &proc_live, 10},
	{0x02, &proc_load, 5},
	{0x03, &proc_store, 5},
	{0x09, &proc_zjump, 20}
};
