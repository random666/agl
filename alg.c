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

void list_init()
{
	head = (struct list *) malloc (sizeof (struct list));
	head->key = 0;
	head->left = NULL;
	head->right = NULL;
}


void list_add_left (int data)
{
	struct list *iterator;
	if (head == NULL)
		list_init();
	iterator = head;
	while (iterator->left != NULL)
		iterator = iterator->left;
	iterator->left = (struct list *) malloc (sizeof (struct list));
	iterator->left->key = data;
}


void list_add_right (int data)
{
	head = get_head();
	struct list *iterator;
	if (head == NULL)
		list_init();
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

void delete (int position)
{
	head = get_head();
	struct list *temp = head;
	int count = 1;

	if (position == 1)
	{
		temp = head;
		if (temp->right != NULL)
		{
			head = temp->right;
			head->left = NULL;
			free (temp);
		}
	}
	else
	{
		while (temp->right != NULL && count != position)
		{
			temp = temp->right;
			++count;
		}
		if (temp->right == NULL)
		{
			temp->left->right == NULL;
			free (temp);
		} 
		else if (count == position) 
		{
			temp->left->right = temp->right;
			temp->right->left = temp->left;
			free (temp);
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
	struct list *iterator_right = head;
	while (iterator_right != NULL)
	{
		printf ("%d\n", iterator_right->key);
		iterator_right = iterator_right->right;
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
			if (temp_2->right->left != NULL)
				temp_2->right->left = temp_1;
			temp_2->left = temp->left;
			temp_2->right = temp->right;
		}
	}
}

struct list *get_head()
{
	while (head->left != NULL)
		head = head->left;
	return head;
}

int pivot (int l, int r)
{

}

void quick_sort (int l, int r)
{
	if ((r - l) > 1)
	{
		int p = pivot (l, r);
		quick_sort (l, p);
		quick_sort (p+1, l); 
	}
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
		swap (j,i);
	}
}

int main()
{
	list_init();
	int i = 1;
	int j = 9;
	for ( ; i < 10; ++i,--j)
		insert (i,j);
	print ();
	swap (0,1);
	print ();
	return 0;
}
