#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node 
{
	struct node *left;
	struct node *right;
	int key;
};

struct node *insert (struct node *_node, int data)
{
	if (_node != NULL)
	{
		if (data < _node->key)
			_node->left = insert (_node->left, data);
		else 
			_node->right = insert (_node->right, data);
	}
	else 
	{
		_node = malloc (sizeof (struct node));
		_node->key = data;
		_node->left = NULL;
		_node->right = NULL;
	}
	return _node;
}


void print (struct node *_node)
{
	if (_node != NULL)
	{
		print (_node->left);
		printf ("%d", _node->key);
		print (_node->right);
	}
}

int depth (struct node *_node)
{
	if (_node != NULL)
	{
		int r,l;
		l = depth (_node->right);
		r = depth (_node->left);
		int max = l > r ? l : r;
		return max + 1;
	}
	return 0;
}


int is_balanced (struct node *_node)
{
	if (_node != NULL)
	{
		int r_depth = depth (_node->right);
		int l_depth = depth (_node->left);
		int r_balanced = is_balanced (_node->right);
		int l_balanced = is_balanced (_node->left);
		return ( abs(r_depth - l_depth) <= 1 && r_balanced
			&& l_balanced); 

	}
	return 1;
}

void delete (int data)
{

}

struct node *head;

struct node *init ()
{
	head = insert (head,7);
	head = insert (head,5);
	head = insert (head,6);
	head = insert (head,4);
	head = insert (head,9);
	head = insert (head,8);
	head = insert (head,10);
	return head;
}



int main()
{
	head = init();
	int balanced = is_balanced (head);
	printf ("Is balanced %d\n", balanced);
	return 0;
}
