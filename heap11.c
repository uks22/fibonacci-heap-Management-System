#include<stdio.h>
#include<stdlib.h>
//0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229.
/*
    1)Given code implements fibonacci heap.
    2)Fibonacci heap provides close to constant time malloc.
    3)Here we maintain multiple free list and update them accordingly based on size of allocated space to heap block.
    4)Contant time is attained due to limited series of fibonacci numbers.
    5)Merge is also not time consuming since we know that two blocks whose size is adjacent numbers in fibonacci series are buddy of each other and thus can be merged.
*/
struct node{
    int start;
    int end;
    struct node*next;
};
struct heap
{
    int*fibnum;
    struct node**fibnode;//array of free list
    struct node**allocnode;//array of allocated list
}h1;
int initialize_heap()
{
    int n;
    printf("Enter the size of heap : ");
    scanf("%d",&n);
    int a=0,b=1,i;
    for(i=0;b<=n;i++)
    {
        int temp=a+b;
        a=b;
        b=temp;
    }
    h1.fibnum=(int*)malloc(i*sizeof(int));
    h1.fibnode=(struct node**)malloc(i*sizeof(struct node*));
    h1.allocnode=(struct node**)malloc(i*sizeof(struct node*));
    h1.fibnum[0]=h1.fibnum[1]=1;
    h1.fibnode[0]=h1.fibnode[1]=NULL;
    h1.allocnode[0]=h1.allocnode[1]=NULL;
    for(int j=2;j<i;j++)
    {
        h1.fibnum[j]=h1.fibnum[j-1]+h1.fibnum[j-2];
        h1.fibnode[j]=NULL;
        h1.allocnode[j]=NULL;
    }
    h1.fibnode[i-1]=(struct node*)malloc(sizeof(struct node));
    h1.fibnode[i-1]->start=1;
    h1.fibnode[i-1]->end=a;
    return i;
}
void deleteheap(int n)
{
    free(h1.fibnum);
    for(int i=0;i<n;i++)
    {
        struct node*nptr=h1.fibnode[i];
        while(nptr)
        {
            struct node*temp=nptr->next;
            free(nptr);
            nptr=temp;
        }
    }
    for(int i=0;i<n;i++)
    {
        struct node*nptr=h1.allocnode[i];
        while(nptr)
        {
            struct node*temp=nptr->next;
            free(nptr);
            nptr=temp;
        }
    }
    free(h1.fibnode);
    free(h1.allocnode);
    h1.fibnode=NULL;
    h1.allocnode=NULL;
}
int _malloc_(int size,int n)//constant time(since size of heap is fixed thus time to find free space is log(size) thus independent of number of blocks)
{
    int i=0,retval=-1;
    while(i<n&&h1.fibnum[i]<size)i++;
    int optimalsize=h1.fibnum[i];
    while(i<n&&h1.fibnode[i]==NULL)i++;
    if(i<n)
    {
        struct node*temp;
        while(h1.fibnum[i]!=optimalsize)
        {
            temp=h1.fibnode[i];
            struct node*temp1=(struct node*)malloc(sizeof(struct node));
            temp1->start=h1.fibnode[i]->start;
            temp1->end=h1.fibnode[i]->start+h1.fibnum[i-1]-1;
            temp1->next=h1.fibnode[i-1];
            h1.fibnode[i-1]=temp1;
            temp1=(struct node*)malloc(sizeof(struct node));
            temp1->start=h1.fibnode[i]->start+h1.fibnum[i-1];
            temp1->end=h1.fibnode[i]->end;
            temp1->next=h1.fibnode[i-2];
            h1.fibnode[i-2]=temp1;
            free(h1.fibnode[i]);
            h1.fibnode[i]=NULL;
            if(h1.fibnum[i-1]!=optimalsize)i--;
            i--;
        }
        temp=h1.fibnode[i];
        if(h1.fibnode[i])h1.fibnode[i]=h1.fibnode[i]->next;
        retval=temp->start;
        struct node*tempp=(struct node*)malloc(sizeof(struct node));
        tempp->start=temp->start;
        tempp->end=temp->end;
        tempp->next=h1.allocnode[i];
        h1.allocnode[i]=tempp;
        if(temp)free(temp);
    }
    else
    {
        printf("Malloc failed\n");
        retval=-1;
    }
    return retval;
}
void merge_free(int n)//
{
    for(int i=0;i<n-1;i++)
    {
        
        if(h1.fibnode[i]&&h1.fibnode[i+1])
        {
            struct node*nptr=(struct node*)malloc(sizeof(struct node)),*n1;
            nptr->next=h1.fibnode[i];
            n1=nptr;
            while(nptr->next)
            {
                struct node*nptr2=(struct node*)malloc(sizeof(struct node)),*n2;
                nptr2->next=h1.fibnode[i+1];
                n2=nptr2;
                while(nptr2->next)
                {
                    if(nptr->next->start==nptr2->next->end+1)
                    {
                        int s=nptr2->next->start;
                        int e=nptr->next->end;
                        struct node*t=nptr->next;
                        nptr->next=t->next;
                        free(t);
                        t=nptr2->next;
                        nptr2->next=t->next;
                        free(t);
                        struct node*nl=(struct node*)malloc(sizeof(struct node));
                        nl->start=s;
                        nl->end=e;
                        if(i+2<n)
                        {
                            nl->next=h1.fibnode[i+2];
                            h1.fibnode[i+2]=nl;
                        }
                        goto w;
                    }
                    else if(nptr->next->end+1==nptr2->next->start)
                    {
                        int s=nptr->next->start;
                        int e=nptr2->next->end;
                        struct node*t=nptr->next;
                        nptr->next=t->next;
                        free(t);
                        t=nptr2->next;
                        nptr2->next=t->next;
                        free(t);
                        struct node*nl=(struct node*)malloc(sizeof(struct node));
                        nl->start=s;
                        nl->end=e;
                        if(i+2<n)
                        {
                            nl->next=h1.fibnode[i+2];
                            h1.fibnode[i+2]=nl;
                        }
                        goto w;
                    }
                    else nptr2=nptr2->next;

                }
                nptr=nptr->next;
                w:
                h1.fibnode[i+1]=n2->next;
                free(n2);
                printf("\0");
            }
            h1.fibnode[i]=n1->next;
            free(n1);
        }
    }
}
void _free_(int*loc,int n)
{
    int flag=0;
    struct node*dummy=(struct node*)malloc(sizeof(struct node));
    for(int i=0;i<n&&flag==0;i++)
    {
        dummy->next=h1.allocnode[i];
        struct node*nptr=dummy;
        while(nptr&&nptr->next&&!flag)
        {
            if(nptr->next->start==*loc)
            {
                struct node*temp=nptr->next;
                struct node*add1=(struct node*)malloc(sizeof(struct node));
                add1->start=temp->start;
                add1->end=temp->end;
                add1->next=h1.fibnode[i];
                h1.fibnode[i]=add1;
                nptr->next=temp->next;
                free(temp);
                flag=1;
            }
            else nptr=nptr->next;
        }
        h1.allocnode[i]=dummy->next;
    }
    free(dummy);
    if(flag==0)
    {
        printf("Invalid address! such address isn't malloced\n");
    }
    *loc=-1;//represents freed up space
    merge_free(n);
}
void displayAllocatedlist(int n)
{
    printf("Allocated-list\n");
    for(int j=0;j<n;j++)
    {
        printf("%d : ",h1.fibnum[j]);
        if(h1.allocnode[j])
        {
            struct node*nptr=h1.allocnode[j];
            while(nptr)
            {
                printf("%d<---->%d    ",nptr->start,nptr->end);
                nptr=nptr->next;
            }
        }
        printf("\n");
    }
    printf("\n");
}
void displayfreelist(int n)
{
    printf("Free-list\n");
    for(int j=0;j<n;j++)
    {
        printf("%d : ",h1.fibnum[j]);
        if(h1.fibnode[j])
        {
            struct node*nptr=h1.fibnode[j];
            while(nptr)
            {
                printf("%d<---->%d    ",nptr->start,nptr->end);
                nptr=nptr->next;
            }
        }
        printf("\n");
    }
    printf("\n");
}
int main()
{
    int n=initialize_heap();
    displayfreelist(n);
    displayAllocatedlist(n);
    int adr=_malloc_(101,n);
    int adr1=_malloc_(101,n);
    int adr2=_malloc_(1500,n);
    displayfreelist(n);
    displayAllocatedlist(n);
    _free_(&adr,n);
    _free_(&adr2,n);
    displayfreelist(n);
    displayAllocatedlist(n);
    deleteheap(n);
}
/*45382 46368


39604 43784

28658 39603

1 28657*/