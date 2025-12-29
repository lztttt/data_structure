#include <stdio.h>
#include <stdlib.h>
typedef char TElemType;

typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild;  
    struct BiTNode *rchild;  
} BiTNode, *BiTree;

// 创建二叉树
void CreateBTree(BiTree &T) {
    char check;  // Y/N
    T = (BiTree)malloc(sizeof(BiTNode));
    if (T == NULL) {
        printf("内存分配失败\n");
        return;
    }
    printf("请输入当前结点的值");
    rewind(stdin);
    scanf("%c", &T->data);
    //创建左子树
    printf("为结点 '%c' 添加左孩子?", T->data);
    rewind(stdin);
    scanf("%c", &check);
    if (check == 'Y' || check == 'y') {
        CreateBTree(T->lchild);
    } else {
        T->lchild = NULL;
    }
    
    //创建右子树
    printf("为结点 '%c' 添加右孩子?", T->data);
    rewind(stdin);
    scanf("%c", &check);
    if (check == 'Y' || check == 'y') {
        CreateBTree(T->rchild); 
    } else {
        T->rchild = NULL; 
    }
}

// 叶子结点个数
int CountLeaf(BiTree T) {
    if (T == NULL) {
        return 0;
    }
    if (T->lchild == NULL && T->rchild == NULL) {
        return 1;
    }
    return CountLeaf(T->lchild) + CountLeaf(T->rchild);
}

// 输出二叉树
void DispBTree(BiTree T) {
    if (T != NULL) {
        printf("%c", T->data);
        if (T->lchild != NULL || T->rchild != NULL) {
            printf("(");
            DispBTree(T->lchild);
            if (T->rchild != NULL) {
                printf(",");
            }
            DispBTree(T->rchild);
            printf(")");
        }
    }
}

int main() {
    BiTree T = NULL; 
    int leafNum; 
    CreateBTree(T);
    
    leafNum = CountLeaf(T);
    printf("叶子结点个数为：%d\n", leafNum);
    printf("二叉树结构：\n");
    DispBTree(T);
    printf("\n");
    return 0;
}