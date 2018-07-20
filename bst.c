#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *left;
    struct node *right;
    int data;
} node;

node *node_new(int data) {
    node *n = malloc(sizeof(node));
    if (n == NULL) {
        exit(1);
    }

    n->left = NULL;
    n->right = NULL;
    n->data = data;
    return n;
}

void node_free(node *n) {
    if (!n) {
        return;
    }

    free(n);
}

node *bst_new(int data) {
    return node_new(data);
}

void bst_free(node *root) {
    if (!root) {
        return;
    }

    bst_free(root->left);
    bst_free(root->right);
    node_free(root);
}

void bst_insert(node *root, int data) {
    if (root->data == data) {
        printf("data %d already exist \n", data);
        return;
    }
    if (data > root->data) {
        if (root->right) {
            bst_insert(root->right, data);
        } else {
            printf("insert %d\n", data);
            root->right = node_new(data);
        }
    } else {
        if (root->left) {
            bst_insert(root->left, data);
        } else {
            printf("insert %d\n", data);
            root->left = node_new(data);
        }
    }
}



node *bst_delete(node *root, int data) {
    if (root == NULL) {
        return root;
    }

    if (data < root->data) {
        root->left = bst_delete(root->left, data);
    } else if (data > root->data) {
        root->right = bst_delete(root->right, data);
    } else {
        if (root->left == NULL) {
            node *right = root->right;
            free(root);
            return right;
        } else if (root->right == NULL) {
            node *left = root->left;
            free(root);
            return left;
        } else {
            node *min_right = root->right;
            while (min_right->left != NULL) {
                min_right = min_right->left;
            }
            root->data = min_right->data;
            root->right = bst_delete(root->right, root->data);
        }
    }

    return root;
}

void bst_convert_node(node *root, node **last_node) {
    if (root == NULL) {
        return;
    }

    if (root->left != NULL) {
        bst_convert_node(root->left, last_node);
    }

    root->left = *last_node;
    if (*last_node != NULL) {
        (*last_node)->right = root;
    }

    *last_node = root;
    if (root->right != NULL) {
        bst_convert_node(root->right, last_node);
    }
}

void bst_print_list(node *root) {
    node *current = root;
    while(current != NULL) {
        printf("data: %d\n", current->data);
        current = current->right;
    }
}

node *bst_convert_tolist(node *root) {
    if (root == NULL) {
        return NULL;
    }
    node *head = root;
    node *last_node = NULL;
    while (head->left != NULL) {
        head = head->left;
    }
    bst_convert_node(root, &last_node);
    return head;
}

int bst_search(node *root, int data) {
    if (!root) {
        return 0;
    }
    if (data == root->data) {
        return 1;
    }

    if (data > root->data) {
        return bst_search(root->right, data);
    } else {
        return bst_search(root->left, data);
    }
}

void preorder(node *root) {
    if (!root) {
        return;
    }

    printf("preorder data: %d\n", root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(node *root) {
    if (!root) {
        return;
    }

    inorder(root->left);
    printf("inorder data: %d\n", root->data);
    inorder(root->right);
}

void postorder(node *root) {
    if (!root) {
        return;
    }

    postorder(root->left);
    postorder(root->right);
    printf("postorder data: %d\n", root->data);
}


int main() {
    node *root = bst_new(10);
    bst_insert(root, 6);
    bst_insert(root, 4);
    bst_insert(root, 8);
    bst_insert(root, 14);
    bst_insert(root, 12);
    bst_insert(root, 16);

    preorder(root);
    printf("============\n");
    inorder(root);
    printf("============\n");
    postorder(root);

    if (bst_search(root, 12)) {
        printf("find 12\n");
    } else {
        printf("can not find 12\n");
    }

    if (bst_search(root, 15)) {
        printf("find 15\n");
    } else {
        printf("can not find 15\n");
    }

    bst_insert(root, 15);
    bst_insert(root, 15);

    if (bst_search(root, 15)) {
        printf("find 15\n");
    } else {
        printf("can not find 15\n");
    }

    root = bst_convert_tolist(root);
    bst_print_list(root);
    //todo free list

    /*
    root = bst_delete(root, 4);
    printf("============\n");
    preorder(root);

    root = bst_delete(root, 6);
    printf("============\n");
    preorder(root);

    root = bst_delete(root, 10);
    printf("============\n");
    preorder(root);

    bst_free(root);
     */

    return 0;
}
