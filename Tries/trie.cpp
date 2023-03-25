#include <bits/stdc++.h>

using namespace std;

struct TrieNode
{
    char val;
    TrieNode *parent;
    TrieNode *child;
    TrieNode *right;
    TrieNode(char v, TrieNode *p) : parent(p), val(v), child(NULL), right(NULL){};
};

TrieNode *insertToRight(TrieNode *prev, TrieNode *parent, char x)
{
    TrieNode *temp = prev->right;
    TrieNode *new_node = new TrieNode(x, parent);
    prev->right = new_node;
    new_node->right = temp;
    return new_node;
}

TrieNode *insertHelper(TrieNode *root, TrieNode *parent, string &new_string, int inx)
{
    if (inx == new_string.size())
        return NULL;

    if (root == NULL)
        root = new TrieNode(new_string[inx], parent);

    TrieNode *temp = root, *prev = NULL;
    while (temp)
    {
        if (temp->val == new_string[inx])
        {
            temp->child = insertHelper(temp->child, temp, new_string, inx + 1);
            return root;
        }
        prev = temp;
        temp = temp->right;
    }

    TrieNode *new_node = insertToRight(prev, parent, new_string[inx]);
    new_node->child = insertHelper(new_node->child, new_node, new_string, inx + 1);
    return root;
}

void insertStr(TrieNode *root)
{
    string new_string;
    cout << "Enter the string : ";
    cin >> new_string;
    new_string.push_back('#');
    root->child = insertHelper(root->child, root, new_string, 0);
}

void deleteNode(TrieNode *root, TrieNode *prev)
{
    if (prev == NULL)
        root->parent->child = root->right;
    else
        prev->right = root->right;
    delete root;
}

bool deleteStr(TrieNode *root, string str_to_delete, int inx)
{
    if (root == NULL)
    {
        if (inx != str_to_delete.size())
            return false;
        else
            return true;
    }
    TrieNode *curr_node = NULL, *temp = root, *prev = NULL;
    while (temp != NULL)
    {
        if (str_to_delete[inx] == temp->val)
        {
            curr_node = temp;
            break;
        }
        prev = temp;
        temp = temp->right;
    }
    if (curr_node == NULL)
        return false;

    bool can_delete = deleteStr(curr_node->child, str_to_delete, inx + 1);
    if (can_delete == false)
        return false;

    if (curr_node->child == NULL)
        deleteNode(curr_node, prev);
    else
        return false;
    return true;
}

void TriePrinter(TrieNode *root, string &curr_string)
{
    if (root == NULL)
        return;

    TrieNode *temp = root->child;
    while (temp)
    {
        if (temp->val == '#')
        {
            cout << curr_string << '\n';
            temp = temp->right;
            continue;
        }
        curr_string.push_back(temp->val);
        TriePrinter(temp, curr_string);
        curr_string.pop_back();
        temp = temp->right;
    }
}

void findPrefix(TrieNode *root, string &prefix)
{
    TrieNode *temp = root->child;
    for (int i = 0; i < prefix.size(); i++)
    {
        while (temp)
        {
            if (temp->val == prefix[i])
            {
                temp = temp->child;
                break;
            }
            temp = temp->right;
        }
        if (temp == NULL)
        {
            cout << "No string found!!\n";
            return;
        }
    }

    cout << "Strings starting with prefix " << prefix << " are : \n";
    TriePrinter(temp->parent, prefix);
}

int main()
{
    cout << "******************Trie Operations*************** \n";

    TrieNode *root = new TrieNode('$', NULL);
    string temp = "";
    while (1)
    {
        cout << "**********Enter the operation you want to perform **************** \n1. Insert \n2. Find prefix strings\n3. Delete\n4. Print All Strings in Trie\n5. Any other key to exit\n";
        int choice;
        cin >> choice;
        if (choice == 1)
            insertStr(root);
        else if (choice == 2)
        {
            string prefix;
            cout << "Enter the prefix string : ";
            cin >> prefix;
            findPrefix(root, prefix);
        }
        else if (choice == 3)
        {
            string str_to_delete;
            cout << "Enter the string to delete from Trie : ";
            cin >> str_to_delete;
            str_to_delete.push_back('#');
            deleteStr(root->child, str_to_delete, 0);
        }
        else if (choice == 4)
        {
            cout << "The strings in tries are : \n";
            TriePrinter(root, temp);
            cout << '\n';
        }
        else
            break;
    }
}