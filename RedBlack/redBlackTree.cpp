#include <bits/stdc++.h>

using namespace std;

struct rbNode
{
    int val;
    rbNode *left;
    rbNode *right;
    rbNode *parent;
    bool red;
    rbNode(int v, rbNode *par) : val(v), left(NULL), right(NULL), red(true), parent(par){};
};

rbNode *global_root = NULL;

bool isLeftChild(rbNode *root)
{
    return (root->val < root->parent->val);
}

void rightRotate(rbNode *grandParent)
{
    rbNode *ggp = grandParent->parent;
    rbNode *parent = grandParent->left;
    rbNode *child = parent->right;
    if (grandParent == global_root)
        global_root = parent;
    parent->right = grandParent;
    grandParent->parent = parent;
    grandParent->left = child;
    if (child)
        child->parent = grandParent;
    parent->parent = ggp;
    if (ggp)
    {
        if (isLeftChild(parent))
            ggp->left = parent;
        else
            ggp->right = parent;
    }
}
void leftRotate(rbNode *grandParent)
{
    rbNode *ggp = grandParent->parent;
    rbNode *parent = grandParent->right;
    rbNode *child = parent->left;
    if (grandParent == global_root)
        global_root = parent;
    parent->left = grandParent;
    grandParent->parent = parent;
    grandParent->right = child;
    if (child)
        child->parent = grandParent;
    parent->parent = ggp;
    if (ggp)
    {
        if (isLeftChild(parent))
            ggp->left = parent;
        else
            ggp->right = parent;
    }
}

void verifyInsertion(rbNode *x)
{
    if (x->parent == NULL && x->red == true)
    {
        x->red = false;
        return;
    }
    if (x->parent->red == false)
        return;
    rbNode *xParent = x->parent;
    rbNode *xGrandParent = xParent->parent;
    rbNode *ggp = xGrandParent->parent;
    if (isLeftChild(x))
    {
        if (isLeftChild(x->parent)) // LL case
        {
            if (xGrandParent->right == NULL || xGrandParent->right->red == false) // black uncle
            {
                rightRotate(xGrandParent);
                xParent->red = false;
                xGrandParent->red = true;
                return;
            }
            else
            {
                xGrandParent->right->red = false;
                xGrandParent->red = true;
                xGrandParent->left->red = false;
                verifyInsertion(xGrandParent);
            }
        }
        else // RL case -> RR case
        {
            rightRotate(xParent);
            verifyInsertion(xParent);
        }
    }
    else
    {
        if (isLeftChild(x->parent))         // LR case -> LL case
        {
            leftRotate(xParent);
            verifyInsertion(xParent);
        }
        else //  RR case
        {
            if (xGrandParent->left == NULL || xGrandParent->left->red == false) // black uncle
            {
                leftRotate(xGrandParent);
                xParent->red = false;
                xGrandParent->red = true;
                return;
            }
            else    // red uncle
            {
                xGrandParent->right->red = false;
                xGrandParent->red = true;
                xGrandParent->left->red = false;
                verifyInsertion(xGrandParent);
            }
        }
    }
}

void insertRbNode(int val, rbNode *root, rbNode *parent)
{
    if (root == NULL)
    {
        rbNode *new_node = new rbNode(val, parent);
        if (isLeftChild(new_node))
            parent->left = new_node;
        else
            parent->right = new_node;
        verifyInsertion(new_node);
        return;
    }

    if (val > root->val)
        insertRbNode(val, root->right, root);
    else
        insertRbNode(val, root->left, root);
}

void insertHelper(int val, rbNode *root)
{
    if (root == NULL)
    {
        rbNode *new_node = new rbNode(val, NULL);
        global_root = new_node;
        new_node->red = false;
    }
    else
        insertRbNode(val, root, NULL);
}

void rbPrinter(rbNode *root)
{
    cout << "The nodes in red black tree are : \n";
    if (!root)
        return;
    queue<rbNode *> kyu;
    kyu.push(root);
    bool element_found = true;
    while (element_found)
    {
        string sol;
        element_found = false;
        int len = kyu.size();
        while (len--)
        {
            rbNode *curr = kyu.front();
            kyu.pop();
            if (curr == NULL)
            {
                sol += (" N(b) ");
                kyu.push(NULL);
                kyu.push(NULL);
            }
            else
            {
                element_found = true;
                sol += " " + to_string(curr->val) + "(" + ((curr->red) ? "r" : "b") + ") ";
                kyu.push(curr->left);
                kyu.push(curr->right);
            }
        }
        if(element_found)
            cout << sol; 
        cout << "\n";
    }
}

int main()
{
    // Nodes to be inserted in red black trees 
    vector<int> insertVec = {10, 20, 30, 15, 17, 25, 36, 9, 8, 7, 37, 38, 13, 14, 16};
    for(int i : insertVec)
    {
        cout << "Inserting value " << i << " in red black tree\n\n";
        insertHelper(i, global_root);
        rbPrinter(global_root);
    }
}
