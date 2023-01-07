/*
 Project 4:  Priority Queue Project 
 File name: priorityqueue.h Author: Arij Khan  NetId: akhan342  Course: CS 251
 System: Visual Studio
*/
#pragma once

#include <iostream>
#include <sstream>
#include <set>

using namespace std;

template <typename T>
class priorityqueue
{
private:
    struct NODE
    {
        int priority; // used to build BST
        T value;      // stored data for the p-queue
        bool dup;     // marked true when there are duplicate priorities
        NODE *parent; // links back to parent
        NODE *link;   // links to linked list of NODES with duplicate priorities
        NODE *left;   // links to left child
        NODE *right;  // links to right child
    };
    NODE *root; // pointer to root node of the BST
    int size;   // # of elements in the pqueue
    NODE *curr; // pointer to next item in pqueue (see begin and next)

    void recursiveEqual(const priorityqueue& other, NODE* currRoot)
    {
        if(currRoot == nullptr)
        {
            return; 
        }

        enqueue(currRoot->value, currRoot->priority); //insert the root val/pri

        recursiveEqual(other, currRoot->left); //traverse to left
        recursiveEqual(other, currRoot->link); //traverse to linked list
        recursiveEqual(other, currRoot->right); //traverse to right


    }

     void _recursiveFunctionPostOrder(NODE *node)
    {
        if (node == nullptr)
        {
            return;
        }
        else
        {
            _recursiveFunctionPostOrder(node->left); //traverse to left
            _recursiveFunctionPostOrder(node->right); //traverse to right 
            _recursiveFunctionPostOrder(node->link); // checks for duplicates
            node->left = nullptr;
            node->right = nullptr;
            delete node;
            size--;
        }
    }

       void _recursiveFunctionBegin(NODE *node)
       {

        if (node->left == nullptr)
        {
            this->curr = node;
            return;
        }
        else
        {
            _recursiveFunctionBegin(node->left);
        }
       }

     void _recursiveFunctionToString(NODE *node, stringstream &output)
     {
        // this->curr = node;
        // cout << "Catch" << endl;

        if (node == nullptr)
        {
            return;
        }
        else
        {
            // in-order traversal
            _recursiveFunctionToString(node->left, output);
            output << node->priority << " value: " << node->value << endl;
            _recursiveFunctionToString(node->link, output); // checks for duplicate
            _recursiveFunctionToString(node->right, output);
        }
    }

    
    bool recursiveEqualequal(NODE* myCurr, NODE* otherCurr) const
    {
        if (myCurr == nullptr && otherCurr == nullptr)
        {
            return true;
        }
        else if (myCurr == nullptr)
        {
            return false;
        }
        else if (otherCurr == nullptr)
        {
            return false;
        }
        else
        {
            if (recursiveEqualequal(myCurr->left, otherCurr->left) &&
             myCurr->priority == otherCurr->priority && 
             recursiveEqualequal(curr->link, otherCurr->link) && 
             recursiveEqualequal(myCurr->right, otherCurr->right))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }


public:
    //
    // default constructor:
    //
    // Creates an empty priority queue.
    // O(1)
    //
    priorityqueue()
    {

        root = NULL; // pointer to root node of the BST
        size = 0;    // # of elements in the pqueue
        curr = NULL; // pointer to next item in pqueue (see begin and next)
    }


    //
    // operator=
    //
    // Clears "this" tree and then makes a copy of the "other" tree.
    // Sets all member variables appropriately.
    // O(n), where n is total number of nodes in custom BST
    //
    priorityqueue &operator=(const priorityqueue &other)
    {
        clear(); 

        recursiveEqual(other, other.root); 

        return *this;
    }

   

    //
    // clear:
    //
    // Frees the memory associated with the priority queue but is public.
    // O(n), where n is total number of nodes in custom BST
    //
    void clear()
    {

        _recursiveFunctionPostOrder(this->root);
        this->root = nullptr;
        this->curr = nullptr;
    }

    //
    // destructor:
    //
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    //
    ~priorityqueue()
    {

        clear(); 
    }

    //
    // enqueue:
    //
    // Inserts the value into the custom BST in the correct location based on
    // priority.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
    void enqueue(T value, int priority)
    {
        NODE *prev = nullptr;
        NODE *curr = root;

        while (curr != nullptr)
        {
            if (priority == curr->priority)
            {
                prev = curr;
                curr = curr->link; // move curr ptr thru the linked list
                // curr->dup = true;
            }
            else if (priority < curr->priority)
            {
                prev = curr;
                curr = curr->left; // move curr to the left
            }
            else
            {
                prev = curr;
                curr = curr->right; // move curr to the right
            }
        } // end while loop...
        NODE *n = new NODE();
        n->priority = priority;
        n->value = value;
        n->left = nullptr;
        n->right = nullptr;
        n->link = nullptr;

        // curr = n;

        // if bst is empty
        if (prev == nullptr)
        {
            this->root = n;
        }
        else if (priority < prev->priority)
        {
            prev->left = n;
            n->parent = prev;
        }
        else if (priority > prev->priority)
        {
            prev->right = n;
            n->parent = prev;
        }
        else
        {
            prev->link = n;
            n->parent = prev; //connect the new node to its parent 
        }

        size++;
        return;
    }
    //
    // dequeue:
    //
    // returns the value of the next element in the priority queue and removes
    // the element from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //

    T dequeue()
    {

        T valueOut;
        NODE *prev = nullptr;
        NODE *curr = root;
        if (curr == nullptr)
        {
            return valueOut;
        }

        if (curr->left == nullptr && curr->right == nullptr)
        {
            if (curr->link != nullptr)
            {
                NODE *temp = curr->link;
                valueOut = curr->value;
                delete curr;
                root = temp;
                curr = nullptr;
            }
            else
            {
                valueOut = curr->value;
                delete curr;
                curr = nullptr;
                root = nullptr;
            }
            size--; 
            return valueOut;
        }

        // traverse all the way to the left to get the highest priority
        while (curr->left != nullptr)
        {
            // prev = curr;
            curr = curr->left;
        }

        if (curr->link != nullptr)
        {
            NODE *temp = curr->link;
            prev = curr->parent;

            if (prev != nullptr)
            {
                if (prev->left == curr)
                {
                    prev->left = temp;
                }
                else if (prev->right == curr)
                {
                    prev->right = temp;
                }

                temp->parent = prev;
            }

            else if (curr == root)
            {
                root = temp;
            }

            temp->left = curr->left; 
            temp->right = curr->right;
            if (curr->right != nullptr)
            {
                curr->right->parent = temp;
            }

            valueOut = curr->value;
            delete curr;
            curr->left = nullptr;
            curr->parent = nullptr;
            size--; 
            return valueOut;
            
        }

        if (curr == root)
        {
            if (curr->right != nullptr)
            {
                NODE *temp = curr->right;
                temp->parent = curr->parent;
                curr->parent = temp;
                root = temp;
            }

            valueOut = curr->value;
            delete curr;
            size--; 
            return valueOut;
        }

        if (curr->right != nullptr)
        {
            prev = curr->parent; 
            NODE *temp = curr->right;
            if (prev->left == curr)
            {
                prev->left = temp;
            }
            temp->parent = prev;
            valueOut = curr->value;
            delete curr;
            size--; 
            return valueOut;
        }
        // cout << "Six" << endl;
        else
        {
            prev = curr->parent; 
            if (prev->left == curr)
            {
                prev->left = nullptr;
            }

            valueOut = curr->value;
            size--; 
            delete curr;
        }
        
        return valueOut; // TO DO: update this return
    }

    //
    // Size:
    //
    // Returns the # of elements in the priority queue, 0 if empty.
    // O(1)
    //

    int Size()
    {

        return this->size;
    }

    //
    // begin
    //
    // Resets internal state for an inorder traversal.  After the
    // call to begin(), the internal state denotes the first inorder
    // node; this ensure that first call to next() function returns
    // the first inorder node value.
    //
    // O(logn), where n is number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (tree.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
 
    void begin()
    {

        _recursiveFunctionBegin(this->root);
    }

    //
    // next
    //
    // Uses the internal state to return the next inorder priority, and
    // then advances the internal state in anticipation of future
    // calls.  If a value/priority are in fact returned (via the reference
    // parameter), true is also returned.
    //
    // False is returned when the internal state has reached null,
    // meaning no more values/priorities are available.  This is the end of the
    // inorder traversal.
    //
    // O(logn), where n is the number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (pq.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    //
    bool next(T &value, int &priority)
    {
        
        priority = curr->priority;
        value = curr->value;

        if (curr == nullptr)
        {
            return false;
        }

        if (curr->link != nullptr)
        {

            curr = curr->link;

            return true;
        }

        else if (curr->link == nullptr && curr->parent != nullptr && curr->priority == curr->parent->priority)
        {
            while (curr->parent != nullptr && curr->priority == curr->parent->priority)
            {
                curr = curr->parent;
            }

            if (curr->right != nullptr)
            {
                curr = curr->right;
                while (curr->left != nullptr)
                {
                    curr = curr->left;
                }
                return true;
            }
        }

        else if (curr->right != nullptr)
        {
            curr = curr->right;
            while (curr->left != nullptr)
            {
                curr = curr->left;
            }
            return true;
        }
        else
        {

            while (curr->priority > curr->parent->priority)
            {
                curr = curr->parent;
                if (curr == root)
                {
                    return false;
                }
            }
            curr = curr->parent;
            return true;
        }

        return false; // TO DO: update this return
    }

   

    //
    // toString:
    //
    // Returns a string of the entire priority queue, in order.  Format:
    // "1 value: Ben
    //  2 value: Jen
    //  2 value: Sven
    //  3 value: Gwen"

    // Will call a recursive function that will traverse thru the bst
    // and output the highest to lowest priority in order
    string toString()
    {
        string str =  ""; 
        stringstream s; 
        _recursiveFunctionToString(root, s);

        str = s.str(); 
        return str; // TO DO: update this return
    }

    //
    // peek:
    //
    // returns the value of the next element in the priority queue but does not
    // remove the item from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
    T peek()
    {
        T valueOut; 

        begin(); 
        if(curr == nullptr)
        {
            return valueOut; 
        }

        valueOut = curr->value; 

        return valueOut; 
    }

    

    //
    // ==operator
    //
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    //
    bool operator==(const priorityqueue &other) const
    {

        return recursiveEqualequal(root, other.root); 
    }

    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void *getRoot()
    {
        return root;
    }
};
