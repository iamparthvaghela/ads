#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
    srand(time(0));

    cout << "Enter the number of elements : \n";
    int n;
    cin >> n;
    int copy_n = n;

    // since the only thing we care about is cost of operation and finding amortized cost
    // and we don't care about what element is pushed or popped
    // instead of implementing stack we need to only keep track of elements in stack

    int amortized_cost = 0, operation, elements_in_stack = 0;

    // value       : 0 or 4 ||  1   ||   2
    // operation   :  push  ||  pop || multipop

    while (n > 0 || elements_in_stack > 0)
    {
        operation = (rand() % 4);

        if (operation == 0 || operation == 3 && n > 0) // since probability of all operation was equal probable
        {                                              // At any point I was popping max 2 or 3 elements in multipop
            cout << "pushing 1 element\n";             // thus to increase the probabity of pushing (0 or 3) is taken as push operation
            n--;
            amortized_cost += 2;
            elements_in_stack++;
        }
        else if (operation == 1 && elements_in_stack > 0)
        {
            cout << "popping 1 element\n";
            elements_in_stack--;
        }
        else if (operation == 2 && elements_in_stack > 0)
        {
            int can_remove = (rand() % elements_in_stack) + 1;
            cout << "popping " << can_remove << " elements\n";
            elements_in_stack -= can_remove;
        }
    }

    cout << "\n"
         << (amortized_cost) / copy_n;

    return 0;
}