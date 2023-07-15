#ifndef COMMON
#define COMMON

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#endif

//Content

#ifndef vVec
#define vVec

typedef enum{
    no,
    yes
}bool;

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
#endif