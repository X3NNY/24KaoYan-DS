#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef intptr_t ElemType;      //这里是树章节涉及到将结点入栈或队的操作，故更改为指针类型，每次存/取进行转换。
// typedef int ElemType;       // 数据类型