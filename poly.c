#include <stdio.h>
#include <stdlib.h>

struct node {
    int c;
    int e;
    struct node *link;
} *rhead = NULL, *phead = NULL, *qhead = NULL;

struct node* readpoly(struct node *head, int n) {
    struct node *ptr = head;
    for (int i = 0; i < n; i++) {
        struct node *newnode = (struct node*)malloc(sizeof(struct node));
        printf("Enter coefficient: ");
        scanf("%d", &newnode->c);
        printf("Enter exponent: ");
        scanf("%d", &newnode->e);
        newnode->link = NULL;

        if (head == NULL) {
            head = newnode;
        } else {
            ptr = head;
            while (ptr->link != NULL) {
                ptr = ptr->link;
            }
            ptr->link = newnode;
        }
    }
    return head;
}

void addpoly() {
    struct node *rptr = NULL;
    struct node *pptr = phead;
    struct node *qptr = qhead;

    while (pptr != NULL && qptr != NULL) {
        struct node *newnode = (struct node*)malloc(sizeof(struct node));
        newnode->link = NULL;

        if (pptr->e > qptr->e) {
            newnode->c = pptr->c;
            newnode->e = pptr->e;
            pptr = pptr->link;
        } else if (pptr->e < qptr->e) {
            newnode->c = qptr->c;
            newnode->e = qptr->e;
            qptr = qptr->link;
        } else {
            newnode->c = pptr->c + qptr->c;
            newnode->e = pptr->e;
            pptr = pptr->link;
            qptr = qptr->link;
        }

        if (rhead == NULL) {
            rhead = newnode;
            rptr = newnode;
        } else {
            rptr->link = newnode;
            rptr = newnode;
        }
    }

    while (pptr != NULL) {
        struct node *newnode = (struct node*)malloc(sizeof(struct node));
        newnode->c = pptr->c;
        newnode->e = pptr->e;
        newnode->link = NULL;

        if (rhead == NULL) {
            rhead = newnode;
            rptr = newnode;
        } else {
            rptr->link = newnode;
            rptr = newnode;
        }
        pptr = pptr->link;
    }

    while (qptr != NULL) {
        struct node *newnode = (struct node*)malloc(sizeof(struct node));
        newnode->c = qptr->c;
        newnode->e = qptr->e;
        newnode->link = NULL;

        if (rhead == NULL) {
            rhead = newnode;
            rptr = newnode;
        } else {
            rptr->link = newnode;
            rptr = newnode;
        }
        qptr = qptr->link;
    }
}

void printpoly(struct node *head) {
    struct node *ptr = head;
    while (ptr != NULL) {
        printf("%dx^%d", ptr->c, ptr->e);
        if (ptr->link != NULL) {
            printf(" + ");
        }
        ptr = ptr->link;
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of terms of first polynomial: ");
    scanf("%d", &n);
    phead = readpoly(phead, n);
    
    printf("Enter number of terms of second polynomial: ");
    scanf("%d", &n);
    qhead = readpoly(qhead, n);

    printf("\nFirst polynomial: ");
    printpoly(phead);
    
    printf("\nSecond polynomial: ");
    printpoly(qhead);  
    
    addpoly();
    
    printf("\nResultant polynomial: ");
    printpoly(rhead);

    return 0;
}
