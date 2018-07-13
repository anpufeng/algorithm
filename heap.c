#include <stdio.h>
#include <stdlib.h>

#define LEFT_CHILD(x)       (2 * x + 1)
#define RIGHT_CHILD(x)      (2 * x + 2)
#define PARENT(x)           ((x - 1) / 2)

typedef struct node {
    int data;
} node;

typedef struct heap {
    int size;
    int capacity;
    node *element;
} heap;

void max_heap_new(heap *h, int size) {
    h->size = 0;
    h->capacity = size;
    h->element = malloc(size * sizeof(node));
    if (!h->element) {
        printf("no mem\n");
        exit(1);
    }
}

void max_heap_del(heap *h) {
    free(h->element);
}

void max_heap_heapify(heap *h, int i) {
    int largest = (LEFT_CHILD(i) < h->size && h->element[LEFT_CHILD(i)].data > h->element[i].data) ? LEFT_CHILD(i) : i;
    if (RIGHT_CHILD(i) < h->size && h->element[RIGHT_CHILD(i)].data > h->element[largest].data) {
        largest = RIGHT_CHILD(i);
    }
    if (largest != i) {
        node tmp = h->element[i];
        h->element[i] = h->element[largest];
        h->element[largest] =  tmp;
        max_heap_heapify(h, largest);
    }

}
void max_heap_insert(heap *h, int data) {
    node n;
    n.data = data;

    if (h->size == h->capacity) {
        printf("capacity full, capacity: %d, resize to capacity * 2\n", h->capacity);
        h->element = realloc(h->element, h->capacity * 2 * sizeof(node));
        if (!h->element) {
            printf("no mem\n");
            exit(1);
        }
        h->capacity = h->capacity * 2;
    }

    int i = h->size;
    while (i && n.data > h->element[PARENT(i)].data) {
        h->element[i] = h->element[PARENT(i)];
        i = PARENT(i);
    }
    printf("insert data: %d\n", data);
    h->element[i] = n;
    h->size++;
}

void max_heap_print(heap *h) {
    for (int i = 0; i < h->size; i++) {
        printf("index: %d, data: %d\n", i, h->element[i].data);
    }
}

void max_heap_preorder(heap *h, int i) {
    printf("index: %d, data: %d\n", i, h->element[i].data);
    if (LEFT_CHILD(i) < h->size) {
        max_heap_preorder(h, LEFT_CHILD(i));
    }
    if (RIGHT_CHILD(i) < h->size) {
        max_heap_preorder(h, RIGHT_CHILD(i));
    }
}

void max_heap_inorder(heap *h, int i) {
    if (LEFT_CHILD(i) < h->size) {
        max_heap_inorder(h, LEFT_CHILD(i));
    }
    printf("index: %d, data: %d\n", i, h->element[i].data);
    if (RIGHT_CHILD(i) < h->size) {
        max_heap_inorder(h, RIGHT_CHILD(i));
    }
}

void max_heap_postorder(heap *h, int i) {
    if (LEFT_CHILD(i) < h->size) {
        max_heap_postorder(h, LEFT_CHILD(i));
    }
    if (RIGHT_CHILD(i) < h->size) {
        max_heap_postorder(h, RIGHT_CHILD(i));
    }
    printf("index: %d, data: %d\n", i, h->element[i].data);
}

void max_heap_delete(heap *h) {
    if (!h->size) {
        printf("heap is empty\n");
        return;
    }
    printf("delete max : %d\n", h->element[0].data);
    h->element[0] = h->element[h->size];
    h->size--;
    max_heap_heapify(h, 0);
}

int main() {

    int a[] = {5, 10, 13, 2, 1, 500, 31, 15, 19, 50};

    int len = sizeof(a) / sizeof(int);
    heap max_heap;
    max_heap_new(&max_heap, 5);

    for (int i = 0; i < len; i++) {
        max_heap_insert(&max_heap, a[i]);
    }

    printf("preorder begin \n");
    max_heap_preorder(&max_heap, 0);
    printf("preorder end======= \n");

    printf("inorder begin \n");
    max_heap_inorder(&max_heap, 0);
    printf("inorder end======= \n");

    printf("postorder begin \n");
    max_heap_postorder(&max_heap, 0);
    printf("postorder end======= \n");

    max_heap_print(&max_heap);
    max_heap_delete(&max_heap);
    max_heap_print(&max_heap);
    max_heap_delete(&max_heap);
    max_heap_print(&max_heap);
    max_heap_delete(&max_heap);
    max_heap_print(&max_heap);

    max_heap_insert(&max_heap, 999);
    max_heap_insert(&max_heap, 1999);
    max_heap_print(&max_heap);

    max_heap_del(&max_heap);

    return 0;
}