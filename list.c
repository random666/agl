#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct list
{
	int key;
	struct list *left;
	struct list *right;
};

struct list *head;

extern struct list *get_head();
extern void insert (int i, int j);
extern void delete (int k);

void init (int data)
{
	head = (struct list *) malloc (sizeof (struct list));
	head->key = data;
	head->left = NULL;
	head->right = NULL;
}



void populate (int len)
{
	int i, j;
	for (i = 1, j = len ; i < len; ++i,--j)
		insert (i,j);
}

void empty (int len)
{
	int i;
	for (i = len; i > 1; --i)
		delete (i);
}

void list_add_right (int data)
{
	head = get_head();
	struct list *iterator;
	if (head == NULL)
		init(0);
	iterator = head;
	while (iterator->right != NULL)
		iterator = iterator->right;
	iterator->right = (struct list *) malloc (sizeof (struct list));
	iterator->right->key = data;
	iterator->right->left = iterator;
}


void insert (int position, int data)
{
	int count = 1;
	head = get_head();
	struct list *iterator = head;
	if (position < 0 || position == 1)
	{
		iterator->left = (struct list*) malloc (sizeof (struct list));
		iterator->left->key = data;
		iterator->left->right = head;
		head = iterator->left;
		head->left = NULL;
	
	} else {
		 while (count != position && iterator->right != NULL)
		 {
			 iterator = iterator->right;
			 ++count;
		 }
		 if (count == position)
		 {
			 struct list *temp = malloc (sizeof (struct list));
			 temp->key = data;
			 temp->left = iterator->left;
			 temp->right = iterator;
			 iterator->left->right = temp;
			 iterator->left = temp;

		 }
		 else 
		 {
			 iterator->right = malloc (sizeof (struct list));
			 iterator->right->key = data;
			 iterator->right->left = iterator;
			 iterator->right->right = NULL;
		 }
	}
}

int count ()
{
	head = get_head();
	int count = 1;
	struct list *temp = head;
	while (temp->right != NULL)
	{
		temp = temp->right;
		++count;
	}
	return count;
}

void print ()
{
	head = get_head();
	printf ("Print list\n");
	struct list *iterator = head;
	while (iterator != NULL)
	{
		printf ("%d\n", iterator->key);
		iterator = iterator->right;
	}
}


void print_reverse ()
{
	head = get_head();
	printf ("Print list in reverse order\n");
	struct list *temp;
	temp = head;
	while (temp->right != NULL)
		temp = temp->right;
	
	while (temp != NULL)
	{
		printf ("%d\n", temp->key);
		temp = temp->left;
	}
}

struct list *find (int position)
{
	head = get_head();
	int count = 0;
	struct list *temp = head;
	while (temp->right != NULL && count != position)
	{
		temp = temp->right;
		++count;
	}
	if (count == position)
		return temp;
	else 
		return NULL;
}

void swap (int i, int k)
{
	if (k < i)
	{
		int temp = k;
		k = i;
		i = temp;
	}
	struct list *temp_1 = find (i);
	struct list *temp_2 = find (k);
	struct list *temp = malloc (sizeof (struct list));
	if (temp_1 != NULL && temp_2 != NULL)
	{
		if (abs (i-k) == 1)
		{
			temp_1->right = temp_2->right;
			temp_2->left = temp_1->left;
			temp_1->left = temp_2;
			temp_2->right = temp_1;
			if (temp_1->right != NULL)
				temp_1->right->left = temp_1;
			if (temp_2->left != NULL)
				temp_2->left->right = temp_2;
		}
		else 
		{
			temp->right = temp_1->right;
			temp->left = temp_1->left;
			if (temp_1->left != NULL)
				temp_1->left->right = temp_2;
			if (temp_1->right != NULL)
				temp_1->right->left = temp_2;
			temp_1->left = temp_2->left;
			temp_1->right = temp_2->right;
			if (temp_2->left != NULL)
				temp_2->left->right = temp_1;
			if (temp_2->right != NULL)
				temp_2->right->left = temp_1;
			temp_2->left = temp->left;
			temp_2->right = temp->right;
		}
	}
	free (temp);
}

struct list *get_head()
{
	if (head == NULL)
		init(0);

	while (head->left != NULL)
		head = head->left;
	return head;
}

int pivot (int l, int r)
{
	struct list *temp = find (r - 1);
	int i = l - 1;
	int j;
	for (j = l; j < r - 1; ++j)
	{
		struct list *cur = find (j);
		if (cur->key < temp->key)
		{
			i++;
			swap (i,j);
		}
	}
	swap (i + 1,r - 1);
	return i + 1;
}

void quick_sort (int l, int r)
{
	if ((r - l) > 1)
	{
		int p = pivot (l, r);
		quick_sort (l, p);
		quick_sort (p + 1, r); 
	}
}


void move (int to, int from)
{
	struct list *move = find (from);
	struct list *temp = find (to);
	
	if (move->right != NULL)
		move->right->left = move->left;
	if (move->left != NULL)
		move->left->right = move->right;

	move->right = temp;
	move->left = temp->left;
	if (temp->left != NULL)
		temp->left->right = move;
	temp->left = move;
}

void insert_sort ()
{
	int len = count();
	head = get_head();
	int i;
	for (i = 1; i < len; ++i)
	{
		int j = i - 1;
		struct list *temp = find (i);
		struct list *key = temp;
		while (j >= 0 && key->key < temp->left->key)
		{
			temp = temp->left;
			--j;
		}
		++j;
		move (j,i);
	}
}

void delete (int position)
{
	head = get_head();
	struct list *temp = head;
	int count = 0;
	if (position == 0)
		return;

	while (temp->right != NULL && count != position)
	{
		temp = temp->right;
		++count;
	}
	if (temp->right == NULL)
	{
		if (temp->left != NULL)
			temp->left->right = NULL;
		free (temp);
	} 
	else if (count == position) 
	{
		temp->left->right = temp->right;
		temp->right->left = temp->left;
		free (temp);
	}
}

void moveback (int i)
{
	struct list *last;
	head = get_head();
	last = head;
	while (last->right != NULL)
		last = last->right;
	struct list *temp = find (i);
	
	if (temp->left != NULL)
		temp->left->right = temp->right;
	if (temp->right != NULL)
		temp->right->left = temp->right;
	temp->left = last;
	last->right = temp;
	temp->right = NULL;
}

void merge (int l, int m, int r)
{
	struct list *temp1;
	struct list *temp2;
	int i,j;
	i = l;
	j = m;
	int len = m;
	while (i < len && j < r)
	{
		temp1 = find (i);
		temp2 = find (j);
		if (temp1->key > temp2->key)
		{
			move (i,j);
			++i;
			++j;
			++len;
		} else {
			++i;
			++len;
		}
	}
}

void merge_sort (int l, int r)
{
	if ((r - l) > 1)
	{
		int mid = (r + l) / 2;
		merge_sort (l, mid);
		merge_sort (mid, r);
		merge (l, mid, r);
	}
}


int main()
{
	init(0);
	populate (10);
	print ();
	merge_sort (0, 10);
	print ();
	return 0;
}
