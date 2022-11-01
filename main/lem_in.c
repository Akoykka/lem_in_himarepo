/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:22:05 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/21 18:51:26 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void visit_node(int node, int *path, int parent_room)
{
	path[node] = parent_room;
}

void q_unused_root_nodes(t_path *data)
{
	int room;

	room = 0;
	while(data->room_count > room)
	{
		if ((data->adj_grid)[data->start][room]
			&&( !data->best_path || !(data->best_path)[room]))
			q_enqueue(room);
		++room;
	}
}

int *dup_path(int *path, int size)
{
	int	i;
	int *new;

	i = 0;
	new = (int *)ft_memalloc(sizeof(int) * size);
	if(!new)
		exit(1);
	if(!path)
		return(new);
	while (size > i)
	{
		if (path[i] < 0)
			new[i] = (path[i]) * -1;
		else
			new[i] = path[i];
		++i;
	}
	return (new);
}


void get_paths(t_path *data)
{
	q_add_queue(data->room_count);
	q_unused_root_nodes(data);
	while (!q_is_empty())
	{
			/*
			if (data->path_changed)
			{
				data->path_changed = 0;
				//if (data->best_path)
				//	print_paths(data); ////// DEBUG
				q_bzero();
				q_unused_root_nodes(data);
			}
			*/
			bfs(data, dup_path(data->best_path, data->room_count), q_peek());
			q_dequeue();
	}
	q_destroy();
}

int main(void)
{
	t_path data;

	q_init();
	ft_memset(&data, 0, sizeof(data));
	//allocate_memory(&data);
	read_input(&data);
	//ft_print_array(data.room_list);
	//ft_print_matrix(&data);

	get_paths(&data);
	//print_paths(&data);
	//march_ants();
	printf("best turns: %d\n", data.best_turn_count);
	exit (0);
}