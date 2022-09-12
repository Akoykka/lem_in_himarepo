/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:11:10 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/12 18:43:51 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

unsigned long hash_djb2(char *key)
{
	unsigned long hash = 5381;
	int c;

	while (*key)
	{
		c = *key;
		hash = hash * 33 + c;
		++*key;
	}
	return (hash);
}

void hash_init(unsigned int table_size)
{
	t_table *temp;

	temp = hash_storage();
	temp->table_size = table_size;
	temp->table = (t_hash **)ft_memalloc(sizeof(t_hash *) * table_size);
	if (!temp->table)
		exit(1);
}

void hash_destroy(void)
{
	t_table *temp;
	unsigned long i;

	i = 0;
	temp = hash_storage();
	while (temp->table_size > i)
	{
		free((temp->table)[i]->name);
		(temp->table)[i]->name = NULL;
		free((temp->table)[i]);
		(temp->table)[i] = NULL;
		++i;
	}
	free(temp);
	temp = NULL;
}

t_hash *hash_get(char *name)
{
	t_table *temp;
	unsigned long digest;
	t_hash **hash_table;

	temp = hash_storage();
	digest = hash_djb2(name) % temp->table_size;
	hash_table = temp->table;

	while (hash_table[digest])
	{
		if (!ft_strcmp(hash_table[digest]->name, name))
			return (hash_table[digest]);
		++digest;
		if (temp->table_size == digest)
			digest = 0;
	}
	ft_putstr("Error, no such name in hashtable (hash_get)");
	exit(1);
}

t_hash *hash_new(char *name, int x, int y, int number)
{
	t_hash *new;
	
	new = ft_memalloc(sizeof(t_hash));
	if(!new)
		exit(1);
	new->name = ft_strdup(name);
	if (!new->name)
		exit(1);
	new->xy[0] = x;
	new->xy[1] = y;
	new->number = number;

	return (new);

}

void hash_add(char *name, int x, int y, int number)
{
	t_table *temp;
	unsigned long digest;
	t_hash **hash_table;

	temp = hash_storage();
	digest = hash_djb2(name) % temp->table_size;
	hash_table = temp->table;

	while (hash_table[digest])
	{
		++digest;
		if (temp->table_size == digest)
		digest = 0;
	}
	hash_table[digest] = hash_new(name, x, y, number);
}	


t_table *hash_storage(void)
{
	static t_table *storage;
	return(storage);
}

int hash_get_number(char *name)
{
	t_hash *temp;

	temp = hash_get(name);
	return (temp->number);
}

int *hash_get_coords(char *name)
{
	t_hash *temp;

	temp = hash_get(name);
	return (temp->xy);
}