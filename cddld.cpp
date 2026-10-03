#include <iostream>
using namespace std;

class Dnode
{
    friend class cdlld;

private:
    int data;
    Dnode *next, *prev;
};
class cdlld
{
private:
    Dnode head; // dumy header node
public:
    cdlld()
    { // empty linklist
        head.next = &head;
        head.prev = &head;
        //  head is an object now
    }

    void display()
    {
        Dnode *curr = head.next;
        if (curr == &head)
        {
            return;
        }
        while (curr != &head)
        { // because its circular also so last node points to head
            cout << curr->data << " ";
            curr = curr->next;
        }
    }

    void reversedisplay()
    {
        Dnode *curr = head.prev;
        if (curr == &head)
        {
            return;
        }
        while (curr != &head)
        { // because its circular also so last node points to head
            cout << curr->data << endl;
            curr = curr->prev;
        }
    }

    bool insertatstart(int val)
    { // o(1)
        Dnode *temp = new Dnode;
        temp->data = val;
        temp->next = head.next;
        temp->prev = &head; // haed is an object
        head.next->prev = temp;
        head.next = temp;

        return true;
    }

    bool insertatend(int val)
    {
        Dnode *temp = new Dnode;
        temp->data = val;
        temp->next = &head;
        temp->prev = head.prev;
        head.prev->next = temp;
        head.prev = temp;

        return true;
    }

    void reverse()
    {
        Dnode *curr = head.next;
        Dnode *temp = nullptr;

        while (curr != &head)
        {
            temp = curr->next;
            curr->next = curr->prev;
            curr->prev = temp;
            curr = temp;
        }
        temp = head.next;
        head.next = head.prev;
        head.prev = temp;
    }
    bool merge(cdlld &list1, cdlld &list2)
    {
        if (!list1.isSorted() || !list2.isSorted())
        {
            return false;
        }
        // both are empty

        if (list1.head.next == &list1.head && list2.head.next == &list2.head)
        {
            head.next = &head;
            head.prev = &head;
        }
        // list 1 is empty
        else if (list1.head.next == &list1.head)
        {
            head.next = list1.head.next;
            list1.head.next->prev = &head;
            list1.head.prev->next = &head;
            head.prev = list1.head.prev;
        }
        // list 2 is empty
        else if (list2.head.next == &list2.head)
        {
            head.next = list2.head.next;
            list2.head.next->prev = &head;
            list2.head.prev->next = &head;
            head.prev = list2.head.prev;
        }
        // if both list are empty
        else
        {
            Dnode *p1 = list1.head.next;
            Dnode *p2 = list2.head.next;
            Dnode *tail = &head;

            while (p1 != &list1.head && p2 != &list2.head)
            {
                // now take smaller one
                if (p1->data <= p2->data)
                {
                    tail->next = p1;
                    p1->prev = tail;
                    tail = p1;
                    p1 = p1->next;
                }
                else
                {
                    tail->next = p2;
                    p2->prev = tail;
                    tail = p2;
                    p2 = p2->next;
                }
            }

            if (p1 != &list1.head)
            {
                tail->next = p1;
                p1->prev = tail;
                list1.head.prev->next = &head;
                head.prev = list1.head.prev;
            }
            else if (p2 != &list2.head)
            {

                tail->next = p2;
                p2->prev = tail;
                list2.head.prev->next = &head;
                head.prev = list2.head.prev;
            }
            else
            {
                tail->next = &head;
                head.prev = tail;
            }
        }

        // make list empty
        list1.head.next = &list1.head;
        list1.head.prev = &list1.head;
        list2.head.next = &list2.head;
        list2.head.next = &list2.head;
        return true;
    }

    void mergeSort()
    {
        int count = countnode();
        if (count > 1)
        {
            cdlld left, right;
            splitList(left, right);
            left.mergeSort();
            right.mergeSort();
            merge(left, right);
        }
    }

   void selectionSort()
{
    Dnode *sorted = &head;  // sentinel for sorted list
    Dnode *tail = &head;

    while (head.next != &head)
    {
        Dnode *min_node = head.next;
        Dnode *prev_min = &head;

        Dnode *curr = head.next->next;

        while (curr != &head)
        {
            if (curr->data < min_node->data)
            {
                min_node = curr;
                prev_min = curr->prev;
            }
            curr = curr->next;
        }

        // detach min node
        min_node->prev->next = min_node->next;
        min_node->next->prev = min_node->prev;

        // append to sorted
        tail->next = min_node;
        min_node->prev = tail;
        min_node->next = sorted;
        sorted->prev = min_node;
        tail = min_node;
    }
}
    void insertionSort()
    {

        if(head.next==&head||head.next->next==&head){
            cout<<" we dont deal with one node or empty lists ";
            return ;
        }

    Dnode*curr=head.next->next;

    while(curr!=&head){
        Dnode*nextnode=curr->next;
        // detach the node 
        curr->prev->next=curr->next;
        curr->next->prev=curr->prev;

        Dnode*position=head.next;

        while(position!=&head&&position->data<curr->data){
            position=position->next;
        }
        curr->next=position;
       position->prev->next=curr;
        curr->prev=position->prev;
        position->prev=curr;
      

      curr=nextnode;
    }
    }
    void removeDuplicates() {
    Dnode* curr = head.next; // start from first real node
    while (curr != &head) {   // stop at sentinel
        if (curr->data == curr->next->data) {
            Dnode* dup = curr->next;
            curr->next = dup->next;
            dup->next->prev = curr; // extra DLL step
            delete dup;
        } else {
            curr = curr->next;
        }
    }
}

    

    cdlld(const cdlld &orig)
    {
        cout << "copy constructor called" << endl;

        head.next = &head;
        head.prev = &head;

        if (orig.head.next == &orig.head && orig.head.prev == &orig.head)
        {
            return;
        }

        Dnode *p1 = orig.head.next;
        while (p1 != &orig.head)
        {
            Dnode *temp = new Dnode;
            temp->data = p1->data;
            temp->next = &head;
            temp->prev = head.prev;
            head.prev->next = temp;
            head.prev = temp;
            p1 = p1->next;
        }
    }

    cdlld &operator=(const cdlld &orig)
    {

        if (this == &orig)
        {
            return *this;
        }

        Dnode *curr = head.next;
        Dnode *temp;
        while (curr != &head)
        {
            temp = curr;
            curr = curr->next;
            delete temp;
            temp = nullptr;
        }

        head.next = &head; // make it empty bcz it contain garbage
        head.prev = &head;

        Dnode *p1 = orig.head.next;
        while (p1 != &orig.head)
        {
            Dnode *temp = new Dnode;
            temp->data = p1->data;
            temp->next = &head;
            temp->prev = head.prev;
            head.prev->next = temp;
            head.prev = temp;

            p1 = p1->next;
        }

        return *this;
    }

    bool sortedinsert(int val)
    {
        Dnode *temp = new Dnode;
        Dnode *curr = head.next;
        temp->data = val;
        while (curr != &head && curr->data < val)
        {
            curr = curr->next;
        }
        temp->next = curr;
        temp->prev = curr->prev;
        curr->prev->next = temp;
        curr->prev = temp;
        return true;
    }
    bool sortedremove(int val)
    {
        if (head.next == &head && head.prev == &head)
        {
            return false;
        }
        Dnode *curr = head.next;
        while (curr != &head && curr->data < val)
        {
            curr = curr->next;
        }
        if (curr != &head && curr->data == val)
        {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            delete curr;
            curr = nullptr;
            return true;
        }
        return false;
    }

    bool unsortedremove(int val)
    {

        if (head.next == &head && head.prev == &head)
        {
            return false;
        }
        Dnode *curr = head.next;
        while (curr != &head && curr->data != val)
        {
            curr = curr->next;
        }

        if (curr != &head)
        {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            delete curr;
            curr = nullptr;

            return true;
        }

        return false;
    }

    /*
if (Both list1 and list2 are EMPTY)
{
...
}
else if (list1 is EMPTY)
{
...
}
else if (list2 is EMPTY)
{
...
}
else
{
}     */

    void combine(cdlld &list1, cdlld &list2)
    {
        if (list1.head.next == &list1.head && list2.head.next == &list2.head)
        {
            head.next = &head;
            head.prev = &head;
        }
        else if (list1.head.next == &list1.head)
        {
            head.next = list2.head.next;
            list2.head.next->prev = &head;
            head.prev = list2.head.prev;
            list2.head.prev->next = &head;
        }
        else if (list2.head.next == &list2.head)
        {

            head.next = list1.head.next;
            list1.head.next->prev = &head;
            head.prev = list1.head.prev;
            list1.head.prev->next = &head;
        }
        else
        {
            list1.head.prev->next = list2.head.next;
            list2.head.next->prev = list1.head.prev;
            head.next = list1.head.next;
            list1.head.next->prev = &head;
            head.prev = list2.head.prev;
            list2.head.prev->next = &head;
        }

        list1.head.next = &(list1.head);
        list1.head.prev = &(list1.head);
        list2.head.next = &(list2.head);
        list2.head.prev = &(list2.head);
    }
    int countnode()
    {
        Dnode *curr = head.next;
        int count = 0;
        while (curr != &head)
        {
            count++;
            curr = curr->next;
        }
        return count;
    }
    // lab 09 task

    void shuffleMerge(cdlld &list1, cdlld &list2)
    {
        Dnode *p1 = list1.head.next;
        Dnode *p2 = list2.head.next;
        Dnode *tailpointer = &head;
        while (p1 != &list1.head || p2 != &list2.head)
        {
            if (p1 != &list1.head)
            {
                Dnode *next1 = p1->next;
                tailpointer->next = p1;
                p1->prev = tailpointer;
                tailpointer = p1;
                p1 = next1;
            }
            if (p2 != &list2.head)
            {
                Dnode *next2 = p2->next;
                tailpointer->next = p2;
                p2->prev = tailpointer;
                tailpointer = p2;
                p2 = next2;
            }
        }

        tailpointer->next = &head;
        head.prev = tailpointer;

        list1.head.next = &list1.head;
        list1.head.prev = &list1.head;
        list2.head.next = &list2.head;
        list2.head.next = &list2.head;
    }

    void splitList(cdlld &leftHalf, cdlld &rightHalf)
    {
        Dnode *slow = head.next;
        Dnode *fast = head.next;
        while (fast->next != &head && fast->next->next != &head)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        Dnode *aftermid = slow->next;
        if (slow != &head)
        {
            leftHalf.head.next = head.next;
            head.next->prev = &leftHalf.head;
            slow->next = &leftHalf.head;
            leftHalf.head.prev = slow;
        }
        if (aftermid != &head)
        {
            rightHalf.head.next = aftermid;
            aftermid->prev = &rightHalf.head;
            head.prev->next = &rightHalf.head;
            rightHalf.head.prev = head.prev;
        }
        head.next = &head;
        head.prev = &head;
    }

    bool isSorted() const
    {
        if (head.next == &head)
            return true; // empty list is sorted
        Dnode *curr = head.next;
        while (curr->next != &head)
        { // stop before last node
            if (curr->data > curr->next->data)
                return false;
            curr = curr->next;
        }
        return true;
    }
    bool removeLastNode(int &val)
    {
        if (head.next == &head && head.prev == &head)
        {
            return false;
        }
        Dnode *temp = head.prev;
        val = temp->data;
        head.prev->prev->next = &head;
        head.prev = head.prev->prev;

        delete temp;
        temp = nullptr;
    }
    bool removesecondLastNode(int &val)
    {
        if (countnode() < 2)
        {
            return false;
        }
        if (head.next == &head && head.prev == &head)
        {
            return false;
        }
        Dnode *temp = head.prev->prev;
        val = temp->data;
        head.prev->prev->prev->next = head.prev;
        head.prev->prev = head.prev->prev->prev;

        delete temp;
        temp = nullptr;
    }

    bool removekthnode(int k, int &val)
    {
        if (k < 0 || k > countnode())
        {
            return false;
        }
        Dnode *curr = head.next;
        int position = 1;
        while (curr != &head && position < k)
        {
            position++;
            curr = curr->next;
        }
        val = curr->data;
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;

        delete curr;
        curr = nullptr;
    }

    ~cdlld()
    {
        Dnode *curr = head.next;
        Dnode *temp;
        while (curr != &head)
        {
            temp = curr;
            curr = curr->next;
            delete temp;
            temp = nullptr;
        }
        head.next = &head;
        head.prev = &head;
    }
};
int main()
{
    int gh;
    cdlld l2;
    cdlld l3;
    cdlld l1;

    l1.insertatstart(1234);


    l1.display();
    cout<<endl;
    l1.insertionSort();
    cout<<"after sorting by insertion sort"<<endl;
    l1.display();

    
}