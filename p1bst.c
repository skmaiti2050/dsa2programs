#include<stdio.h>
#include<stdlib.h>
#define MAX 100

struct node
{
    struct node *lchild;
    int info;
    struct node *rchild;
} *root;

struct node *insert(struct node *, int );
struct node *search(struct node *, int );
struct node *del(struct node *,int);
void preorder(struct node *);
void inorder(struct node *);
void postorder(struct node *);
struct node *min(struct node *);
struct node *max(struct node *);
void level(struct node *);
struct node *queue[MAX];
int rear = -1, front = -1;
void enqueue(struct node *);
struct node *dequeue();
int queue_empty();

int main()
{
    struct node *ptr;
    int choice,k;
    printf("Expt 1: Operations in Binary Search Tree\n");
    printf("\n1: Insert\n2: Search\n3: Delete\n4: Preorder\n5: Inorder\n6: Postorder\n");
    printf("7: Min element\n8: Max element\n9: Level Order\n0: Exit\n");
    do
    {
        printf("\nEnter your choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            printf("Enter the key to be inserted: ");
            scanf("%d",&k);
            root = insert(root,k);
            break;
        case 2:
            printf("Enter the data to be searched: ");
            scanf("%d",&k);
            ptr = search(root,k);
            if(ptr == NULL)
                printf("%d is not present in the BST\n",k);
            else
                printf("%d was found in the BST\n",k);
            break;
        case 3:
            printf("Enter the key to be deleted: ");
            scanf("%d",&k);
            root = del(root,k);
            break;
        case 4:
            preorder(root);
            break;
        case 5:
            inorder(root);
            break;
        case 6:
            postorder(root);
            break;
        case 7:
            ptr = min(root);
            if(ptr != NULL)
                printf("Minimum key is %d\n", ptr->info);
            break;
        case 8:
            ptr = max(root);
            if(ptr!=NULL)
                printf("Maximum key is %d\n", ptr->info);
            break;
        case 9:
            level(root);
            break;
        case 0:
            printf("Exiting program\n");
            exit(1);
        default:
            printf("Invalid input\n");
            break;
        }
    }
    while(choice!=0);
}

void preorder(struct node *ptr)
{
    if(ptr==NULL)
        return;
    printf("%d\t",ptr->info);
    preorder(ptr -> lchild);
    preorder(ptr -> rchild);
}

void inorder(struct node *ptr)
{
    if(ptr==NULL)
        return;
    inorder(ptr -> lchild);
    printf("%d\t", ptr->info);
    inorder(ptr->rchild);
}

void postorder(struct node *ptr)
{
    if(ptr==NULL)
        return;
    postorder(ptr->lchild);
    postorder(ptr->rchild);
    printf("%d\t", ptr->info);
}

struct node *search(struct node *ptr, int skey)
{
    if(ptr==NULL)
    {
        printf("Key not found\n");
        return NULL;
    }
    else if(skey < ptr->info)
        return search(ptr->lchild,skey);
    else if(skey > ptr->info)
        return search(ptr->rchild,skey);
    else
        return ptr;
}

struct node *min(struct node *ptr)
{
    if(ptr == NULL)
        return NULL;
    else if(ptr->lchild == NULL)
        return ptr;
    else
        return min(ptr->lchild);
}

struct node *max(struct node *ptr)
{
    if(ptr == NULL)
        return NULL;
    else if(ptr->rchild == NULL)
        return ptr;
    else
        return max(ptr->rchild);
}

struct node *insert(struct node *ptr,int ikey)
{
    if(ptr == NULL)
    {
        ptr = (struct node *)malloc(sizeof(struct node));
        ptr->info = ikey;
        ptr->lchild = NULL;
        ptr->rchild = NULL;
    }
    else if(ikey < ptr->info)
        ptr->lchild = insert(ptr->lchild, ikey);
    else if(ikey > ptr->info)
        ptr->rchild = insert(ptr->rchild, ikey);
    else
        printf("% is already present in BST, duplicate key not allowed\n");
    return ptr;
}

struct node *del(struct node *ptr,int dkey)
{
    struct node *tmp, *succ;
    if(ptr==NULL)
    {
        printf("Key not found\n");
        return ptr;
    }
    else if(dkey < ptr->info)
        ptr->lchild=del(ptr->lchild,dkey);
    else if(dkey > ptr->info)
        ptr->rchild=del(ptr->rchild,dkey);
    else
    {
        if(ptr->lchild!=NULL&&ptr->rchild!=NULL)
        {
            succ = ptr->rchild;
            while(succ->lchild)
                succ = succ->lchild;
            ptr->info = succ->info;
            ptr->rchild = del(ptr->rchild,succ->info);
        }
        else
        {
            tmp = ptr;
            if(ptr->lchild != NULL)
                ptr = ptr->lchild;
            else if(ptr->rchild!=NULL)
                ptr = ptr->rchild;
            else
                ptr = NULL;
            free(tmp);
        }
    }
    return ptr;
}

void enqueue(struct node *item)
{
    if(rear==MAX-1)
    {
        printf("Queue Overflow\n");
        return;
    }
    if(front==-1)
        front=0;
    rear=rear+1;
    queue[rear]=item;
}

struct node *dequeue()
{
    struct node *item;
    if(front == -1 || front == rear + 1)
    {
        printf("Queue Underflow\n");
        return 0;
    }
    item = queue[front];
    front = front + 1;
    return item;
}

int queue_empty()
{
    if(front == -1 || front == rear + 1)
        return 1;
    else
        return 0;
}

void level(struct node *root)
{
    struct node *ptr = root;
    if(ptr == NULL)
    {
        printf("Tree is empty\n");
        return ;
    }
    enqueue(ptr);
    while(!queue_empty())
    {
        ptr = dequeue();
        printf("%d\t", ptr->info);
        if(ptr->lchild != NULL)
            enqueue(ptr->lchild);
        if(ptr->rchild != NULL)
            enqueue(ptr->rchild);
    }
    printf("\n");
}
