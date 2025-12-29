#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char TElemType;
typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

int FindRootIndex(TElemType *in_order, int in_start, int in_end, TElemType root_val) {
    for (int i = in_start; i <= in_end; i++) {
        if (in_order[i] == root_val) {
            return i;
        }
    }
    return -1;
}

// 递归构造二叉树
BiTree BuildTreeFromPreIn(TElemType *pre_order, TElemType *in_order, int in_start, int in_end, int *pre_idx) {
    if (in_start > in_end) {
        return NULL;
    }
    TElemType root_val = pre_order[*pre_idx];
    (*pre_idx)++; 
    BiTree root = (BiTree)malloc(sizeof(BiTNode));
    root->data = root_val;
    root->lchild = root->rchild = NULL;

    if (in_start == in_end) {
        return root;
    }

    int root_in_idx = FindRootIndex(in_order, in_start, in_end, root_val);
    root->lchild = BuildTreeFromPreIn(pre_order, in_order, in_start, root_in_idx - 1, pre_idx);
    root->rchild = BuildTreeFromPreIn(pre_order, in_order, root_in_idx + 1, in_end, pre_idx);

    return root;
}

void PostOrderTraverse(BiTree T) {
    if (T != NULL) {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        printf("%c", T->data);
    }
}

void DestroyTree(BiTree *T) {
    if (*T != NULL) {
        DestroyTree(&((*T)->lchild));
        DestroyTree(&((*T)->rchild));
        free(*T);
        *T = NULL;
    }
}

int main() {
    TElemType pre_order[] = "ABDFCEGH";
    TElemType in_order[] = "BFDAGEHC";
    int pre_idx = 0;
    BiTree T = BuildTreeFromPreIn(pre_order, in_order, 0, strlen(in_order) - 1, &pre_idx);
    printf("先序序列：%s\n", pre_order);
    printf("中序序列：%s\n", in_order);
    printf("构造二叉树的后序遍历序列：");
    PostOrderTraverse(T);
    printf("\n");
    DestroyTree(&T);
    return 0;
}