#include <bits/stdc++.h>

using namespace std;

struct heapNode
{
    int val;
    heapNode *left;
    heapNode *right;
    int sValue;
    heapNode(int v) : val(v), left(NULL), right(NULL), sValue(0){};
};

// operations : Merge, getMin, DeleteMin, insert

int sValue(heapNode *node)
{
    if (!node)
        return -1;
    return node->sValue;
}

void verifyMerge(heapNode *parent)
{
    if (sValue(parent->left) < sValue(parent->right))
    {
        heapNode *temp = parent->left;
        parent->left = parent->right;
        parent->right = temp;
    }
    parent->sValue = sValue(parent->right) + 1;
}

heapNode *mergeHeaps(heapNode *root1, heapNode *root2)
{
    stack<heapNode *> st;
    heapNode *ptr1 = root1, *ptr2 = root2;
    while (ptr1 && ptr2)
    {
        if (ptr1->val < ptr2->val)
        {
            st.push(ptr1);
            ptr1 = ptr1->right;
        }
        else
        {
            st.push(ptr2);
            ptr2 = ptr2->right;
        }
    }

    heapNode *child = (ptr1) ? ptr1 : ptr2;
    heapNode *parent;
    while (!st.empty())
    {
        parent = st.top();
        st.pop();
        parent->right = child;
        verifyMerge(parent);
        child = parent;
    }
    return child;
}

heapNode *insertNodes(heapNode *root)
{
    int addNodes;
    cout << "\nEnter the number of elements to add in heap : ";
    cin >> addNodes;
    cout << "Enter the nodes to be added: ";
    while(addNodes--)
    {
        int val;
        cin >> val;
        heapNode *new_node = new heapNode(val);
        root = mergeHeaps(root, new_node);
    }
    return root;
}

heapNode *deleteMinNode(heapNode *root)
{
    if (!root)
        return NULL;
    return mergeHeaps(root->left, root->right);
}

void printHeap(heapNode *root)
{
    queue<heapNode *> kyu;
    if (root)
        kyu.push(root);

    while (!kyu.empty())
    {
        int len = kyu.size();
        string final;
        string temp;
        while (len--)
        {
            heapNode *curr = kyu.front();
            kyu.pop();
            if (curr)
            {
                temp += (to_string(curr->val) + "(" + to_string(curr->sValue) + ") ");
                final += temp;
                temp.clear();
                kyu.push(curr->left);
                kyu.push(curr->right);
            }
            else
            {
                temp += "N(-1)  ";
                kyu.push(NULL);
                kyu.push(NULL);
            }
        }
        if(final.size() == 0)
            break;
        cout << final << '\n';
    }
}

int main()
{
    int operation;
    heapNode *root1 = NULL;
    heapNode *root2 = NULL;
    while (1)
    {
        cout << "\n\n**************** Leftist Heap Operations ****************\n";
        cout << "Enter the operation you want to perform : \n1. Insertion\n2. Delete Minimum element\n3. Merging\n4. Get Minimum element\n5. Print Heaps\n";
        cin >> operation;

        switch (operation)
        {
        case 1: // insertion
            cout << "\nInsertion in heap 1 : ";
            root1 = insertNodes(root1);
            cout << "\nInsertion in heap 2 : ";
            root2 = insertNodes(root2);
            break;
        case 2: // delete Min
            char heapDel;
            cout << "\nDelete minimum element in heap1 ? (y/n) : ";
            cin >> heapDel;
            if (heapDel == 'y')
                root1 = deleteMinNode(root1);
            cout << "\nDelete minimum element in heap2 ? (y/n) : ";
            cin >> heapDel;
            if (heapDel == 'y')
                root2 = deleteMinNode(root2);
            break;
        case 3: // Merging
            cout << "\nThe merged heap will be stored in heap1 and heap2 will be empty\nThe heap after merging is : \n";
            root1 = mergeHeaps(root1, root2);
            root2 = NULL;
            printHeap(root1);
            break;
        case 4: // find Min
            cout << "The minimum elements of heap1 & heap2 are : " << ((root1) ? root1->val : 'n') << " " << ((root2) ? root2->val : 'n');
            break;
        case 5:
            cout << "\nHeap1 is : \n";
            printHeap(root1);
            cout << "\nHeap2 is : \n";
            printHeap(root2);
            break;
        default:
            return 0;
        }
    }
}