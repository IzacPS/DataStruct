#ifndef DS_DEFS_H_
#define DS_DEFS_H_
#define _RED 0
#define _BLACK 1

#define IsRed(x) (x == _RED)
#define NodeColor(x) ((x == NULL) ? _BLACK : x->Color)
#define MAX(x, y) (x > y) ? x : y
#define NodeHeight(x) (x == NULL) ? -1 : x->height

enum Path
{
	PREORDER,
	INORDER,
	POSTORDER
};

enum Traversal
{
	ITERATIVE,
	RECURSIVE
};

enum Direction
{
	left,
	right
};

enum Parity
{
	Even,
	Odd
};

#endif