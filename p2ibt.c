#include<stdio.h>
#include<stdlib.h>

typedef enum {false,true} boolean;
struct node *insert(struct node *, int);
void inorder(struct node *);
void preorder(struct node *);
struct node *in_succ(struct node *);
struct node *in_pred(struct node *);

struct node
{
    struct node *lchild;
    int info;
    struct node *rchild;
    boolean lthread;
    boolean rthread;
}*root;

int main()
{
    int choice, i, count, num;
    while(1)
    {
        printf("\n1: Insert\n2: Inorder Traversal\n3: Preorder Traversal\n");
        printf("\nEnter your choice\n");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            printf("Enter the number of nodes\n");
            scanf("%d",&count);
            for(i = 0; i < count; i++)
            {
                printf("Enter the number to be inserted: ");
                scanf("%d", &num);
                root = insert(root, num);
            }
            break;
        case 2:
            inorder(root);
            break;
        case 3:
            preorder(root);
            break;
        default:
            printf("Invalid choice\n");
            break;
        }
    }
}

struct node *insert(struct node *root, int ikey)
{
    struct node *ptr, *tmp, *par;
    int found = 0;
    ptr = root;
    par = NULL;
    while(ptr != NULL)
    {
        if(ikey == ptr->info)
        {
            found = 1;
            break;
        }
        par = ptr;
        if(ikey < par-> info)
        {
            if(ptr->lthread == false)
                ptr = ptr->lchild;
            else
                break;
        }
        else
        {
            if(ptr->rthread == false)
                ptr = ptr->rchild;
            else
                break;
        }
    }
    if(found)
        printf("Duplicate key\n");
    else
    {
        tmp = (struct node *)malloc(sizeof(struct node));
        tmp->info = ikey;
        tmp->lthread = true;
        tmp->rthread = true;
        if(par == NULL)
        {
            root = tmp;
            tmp->lchild = NULL;
            tmp->rchild = NULL;
        }
        else if (ikey < par->info)
        {
            tmp->lchild = par->lchild;
            tmp->rchild = par;
            par->lthread = false;
            par->lchild = tmp;
        }
        else
        {
            tmp->lchild = par;
            tmp->rchild = par->rchild;
            par->rthread = false;
            par->rchild = tmp;
        }
    }
    return root;
}

struct node *in_pred(struct node *ptr)
{
    if(ptr->lthread == true)
        return ptr->lchild;
    else
    {
        ptr = ptr->lchild;
        while(ptr->rthread == false)
            ptr = ptr->rchild;
        return ptr;
    }
}

struct node *in_succ(struct node *ptr)
{
    if(ptr->rthread == true)
        return ptr->rchild;
    else
    {
        ptr = ptr->rchild;
        while(ptr->lthread == false)
            ptr = ptr->lchild;
        return ptr;
    }
}

void inorder(struct node *root)
{
    if(root == NULL)
    {
        printf("Tree is empty\n");
        return;
    }
    struct node *ptr = root;
    while(ptr->lthread == false)
        ptr = ptr->lchild;
    while(ptr != NULL)
    {
        printf("%d\t", ptr->info);
        ptr = in_succ(ptr);
    }
}

void preorder(struct node *root)
{
    if(root == NULL)
    {
        printf("Tree is empty\n");
        return;
    }
    struct node *ptr = root;
    while(ptr != NULL)
    {
        printf("%d\t", ptr->info);
        if(ptr->lthread == false)
            ptr = ptr->lchild;
        else if (ptr->rthread == false)
            ptr = ptr->rchild;
        else
        {
            while(ptr != NULL && ptr->rthread == true)
                ptr = ptr->rchild;
            if(ptr != NULL)
                ptr = ptr->rchild;
        }
    }
}
