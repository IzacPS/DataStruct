#ifndef DS_DEFS_H_
#define DS_DEFS_H_
#define _RED 0
#define _BLACK 1

#define IsRed(x) (x == _RED)
#define NodeColor(x) ((x == NULL) ? _BLACK : x->Color)

enum Path
{
	PRE_ORDEM,
	ORDEM,
	POS_ORDEM
};

#endif