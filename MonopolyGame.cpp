#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

//---------------LINKED LIST NODE-------------------------------
class Node
{
    public:
    
    //STORE value or data
    int data;

    //POINTER to point the previous element
    Node* prev;
    //POINTER to point the Next element
    Node* next;

    //CONSTRUCTOR= new data
    Node(int d)
    {
        data = d;
        prev= nullptr;
        next= nullptr;
    }
    
};
//======================================================
//PART 1: LINKED LSIT
//=====================================================

class DoublyLinkedList
{
    private:
    Node* head;
    Node* tail;

    public:
    //CONSTRUCTOR : starts an empty list
    DoublyLinkedList(): head(nullptr), tail(nullptr) {}

    //ALL VOID = CAUSE THEY DO SOMETHING BUT DON'T RETURN VALUE 

    //creates a NEW node and LINKS it to END of the list
    void add(int data)
    {
        //allocate a NEW node on the heap
        Node* node = new Node(data);

        //list is empty = this node is BOTH FIRST and LAST
        if(head == nullptr)
        {
            head = tail = node;
        }
        //list already has nodes= link the new one after current TAIL 
        else
        {
            // NEW NODE points back to OLD TAIL
            node -> prev = tail;
            //OLD TAIL points FORWARD to NEW NODE0
            tail -> next = node;
            //update TAIL to the NEW LAST NODE
            tail = node;
        }
    }

    //walks from head to end, checking each node's data
    void search(int data)
    {
        Node* current = head;

        //keep going until it hits END
        while(current!= nullptr)
            {
                //found a match?
                if(current-> data == data)
                {
                    cout<< "Found: " << data << endl;
                    return; //stop searching
                }
                //move to NEXT node
                current = current-> next;
            }
             cout<< "Not Found"  << endl;
        
    }

    void remove(int data)
    {
        //START walking at FIRST NODE
        Node* current = head;

        // keep walking until you find it or hit the end.
        while(current && current->data != data)
            {
                //move to next node
                current = current->next;
            }
                //did we find a node?

//--------------At this point cur is either NOT FOUND or the node to REMOVE--------
         if(!current)
            {
                cout<<"Not found, cannot remove"<< endl;
                return;
            }
//--------------FOUND node, now UNLINK it------------------------------------------
        
          //was it the previous one
         if(current-> prev)
            {
                //YES-> the person IN FRONT lets go of your hand and grabs the hand of the person BEHIND YOU.
                current-> prev-> next = current-> next;
            }
            else
            {
                //NO->CUR waS HEAD, move head FORWARDS = curernt -> next;
                head = current-> next;
            }

             //WAS IT the LAST Node?
            if(current-> next)
            {
                //YES-> the person BEHIND lets go of your hand and grabs the hand of the person IN FRONT of YOU.
                current-> next-> prev= current-> prev;
            }
            else
            {
                //NO->CUR waS TAIL, move tail BACKWARDS = curernt -> prev;
                tail = current-> prev;
            }
            //delete the memory of removed node
            delete current;
        
    }

    void print()
    {
        //start at first node
        Node* current = head;

        while(current != nullptr)
            {
                //print this nodes value
                cout << current -> data;

                if(current-> next)
                {
                    //print separator
                    cout<< " <-> ";
                }
                //move to next node
                current = current->next;

            }
        //newline at END
        cout<< endl;

    }
    
};

//======================================================
//PART 2: MONOPOLY GAME (Circular linked list)
//=====================================================

class PropertyNode
{
    public:
    string name;
    string owner;
    int cost;
    PropertyNode* next;
    
    PropertyNode(string n, int c): name(n), cost(c), owner("Unowned"), next(nullptr) {}    
};

class MonopolyBoard
{
    private:
    PropertyNode* start;
    int n;

    public:
    MonopolyBoard() : start(nullptr), n(0) {}

    PropertyNode* getStart() 
    {
        return start;
    }

    void buildBoard()
    {
        //names
        string names [] = { "Go", "Baltic Ave", "Reading RR", "Oriental Ave", "Vermont Ave", "Penn. Ave", "St. Charles", "Electric Co.", "States Ave", "Virginia Ave", "Public Utils."};
        //costs
        int costs[]={0,100,200,100,120,140,100,150,140,160,150};

        //amount of properties
        n=11;
        PropertyNode* nodes[11];
        for(int i=0; i< n; i++)
            {
                //create and link in 1 loop
                nodes[i]= new PropertyNode(names[i],costs[i]);
            }
            start = nodes[0];

        for(int i=0; i< n; i++)
            {
                nodes[i]-> next = nodes [(i+1) % n];
            }
        start = nodes[0];
    }

    void printBoard()
    {
        PropertyNode* current = start;
        
        for(int i=0; i< n; i++)
        {
            cout << "[" << i << "]" << current->name
                << " ($" <<current-> cost << ") -"
                <<current-> owner << endl;
            current = current-> next;
        }
    }
    
    PropertyNode* move(PropertyNode* pos, int steps)
    {
        while(steps--)
            {
                pos = pos-> next;
            }
            return pos;
    
    }

    void buy(PropertyNode* pos, string p)
    {
        if(pos->owner == "Unowned")
        {
            pos-> owner = p;
            cout<< p << " bought " << pos->name << " for $" << pos-> cost << endl;
        }
        else
        {
            cout<< p << " cannot buy "<< pos->name << " (owned by " << pos->owner << ")" << endl;
        }
    
    }
};

int main() 
{
    //------Part 1 Linked list--------
    cout<< "=== PART 1: Doubly Linked List ===" << endl;

    DoublyLinkedList list;
    list.add(10);
    list.add(20);
    list.add(30);
    list.add(40);

    cout << "List: ";
    list.print();

    cout << "Search 20: ";
    list.search(20);
    
    cout << "Search 99: ";
    list.search(99);

    cout << "Remove 20: ";
    list.remove(20);

    cout << "List: ";
    list.print();

    cout << "Remove 10: ";
    list.remove(10);
    list.print();

    cout<< endl;

 //------Part 2 Monopoly Game--------
    cout<< "=== PART 2: Monopoly Game ===" << endl;
    MonopolyBoard board;
    board.buildBoard();
    board.printBoard();

    //2 players
    string players[]={"Allen", "Kevin"};
    PropertyNode* positions[2]={board.getStart(), board.getStart()};
    int money[2] = {100,100};

    srand(time(0));
    for(int t= 1; t <=10; t++)
        {
            int i = (t-1) % 2;
            int d = rand() % 6 + 1;
            positions[i] = board.move(positions[i], d);
            cout << "\nTurn " << t << ": " << players[i] << " rolls" << d 
                << " , lands on " << positions[i]->name << endl;

            if(positions[i]->cost > 0)
               {
                   if(positions[i]->owner == players[i] )
                   {
                       cout << players[i] << " already owns "<< positions[i]->name 
                           <<endl;
                   }
                   else if(positions[i]->owner != "Unowned")
                   {
                       cout << players[i] << " can't buy "<< positions[i]->name 
                           <<" (owned by "<< positions[i]->owner<< ")" <<endl;
                   }
                   else if(money[i] >= positions[i]->cost)
                   {
                       board.buy(positions[i], players[i]);
                       money[i] -= positions[i]-> cost;
                   }                       
                   else
                   {
                       cout << players[i]<<" can't afford " << positions[i]->name
                           << endl;
                   }
                   cout << "Allen: $"<< money[0] << " | Kevin: $" << money[1] 
                       << endl;
               }
        }
        cout << "\n----Final Board----" << endl;
        board.printBoard();
        return 0;

}