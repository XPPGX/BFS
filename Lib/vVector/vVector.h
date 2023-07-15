#ifndef COMMON
#define COMMON

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#endif

#ifndef BOOL
#define BOOL

typedef enum{
    no,
    yes
}bool;

#endif

//Content

struct vVector{
    int* dataArr;
    int tail;
    int size;
};


struct vVector* InitvVector();
void vShowAllElement(struct vVector* _vec);
void vAppend(struct vVector* _vec, int _val);
bool vIsFull(struct vVector* _vec);
void vShrink(struct vVector* _vec);