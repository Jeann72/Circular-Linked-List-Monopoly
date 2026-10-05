#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

//---------------LINKED LIST NODE-------------------------------
class Node
{
    //accesible outside of class
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

    //store the property's name
    string name;
    //stor owner who owns property
    string owner;
    //store the property's cost
    int cost;
    //A pointer to the next PropertyNode in the linked list
    PropertyNode* next;

    //sets: name member to the parameter n,cost member to the parameter c, and sets owner to "Unowned"
    //This node doesn't point to any other node yet.
    PropertyNode(string n, int c): name(n), cost(c), owner("Unowned"), next(nullptr) {}    
};

class MonopolyBoard
{
    private:
    //Pointer to the first node in the linked list (nullptr = empty list)
    PropertyNode* start;
    //Integer to track how many properties are in the list
    int n;

    public:
    //Default constructor: empty board, no properties
    MonopolyBoard() : start(nullptr), n(0) {}

    //returns a pointer to the first node(to abe able to walk throught ther list)
    PropertyNode* getStart() 
    {
        return start;
    }

    void buildBoard()
    {
        //Array of all property names
        string names [] = { "Go", "Baltic Ave", "Reading RR", "Oriental Ave", "Vermont Ave", "Penn. Ave", "St. Charles", "Electric Co.", "States Ave", "Virginia Ave", "Public Utils."};
        //array of all corresponding costs(dollars)
        int costs[]={0,100,200,100,120,140,100,150,140,160,150};

        //Temporary array of 11 pointers (to hold each node before linking)
        PropertyNode* nodes[11];
        //Set the property count to 11
        n=11;
        //Loop 1: create all 11 nodes
        for(int i=0; i< n; i++)
            {
                //Allocate a new PropertyNode with this name and cost, store pointer
                nodes[i]= new PropertyNode(names[i],costs[i]);
            }
            //Set the board's start pointer to the first node
            start = nodes[0];
        
        //Loop 2: Link each node to the next one(CIRCULAR)
        for(int i=0; i< n; i++)
            {
                //current point accces next pointer and assigns to it the next node on the list
                nodes[i]-> next = nodes [(i+1) % n];
            }
            //Re-assign start
            start = nodes[0];
        
    }

    void printBoard()
    {
        //starts at first node
        PropertyNode* current = start;

        //Loop exactly n times(n= 11 properties)
        for(int i=0; i< n; i++)
        {
            //print
            cout << "[" << i << "]" << current->name
                << " ($" <<current-> cost << ") -"
                <<current-> owner << endl;
            //Move to nect node in the circle
            current = current-> next;
        }
    }

    //Takes a node pointer and a number of steps to move forward
    PropertyNode* move(PropertyNode* pos, int steps)
    {
        //Loop while steps > 0, decrementing each time
        while(steps--)
            {
                //Move the pointer one node fowars in the circle
                pos = pos-> next;
            }
        //return new position affter moving 
            return pos;
    
    }

    //Attempts to buy the property at position pos for player p
    void buy(PropertyNode* pos, string p)
    {
        //check og the property is unowned
        if(pos->owner == "Unowned")
        {
            //set the owner to the players name
            pos-> owner = p;
            //print confirmation message
            cout<< p << " bought " << pos->name << " for $" << pos-> cost << endl;
        }
        else
        {
            //Property is already taken
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
    //create a board object and build 11-node circular list
    MonopolyBoard board;
    board.buildBoard();
    //print initial board(unowned)
    board.printBoard();

    //2 players
    string players[]={"Allen", "Kevin"};
    //Both start at Go(first node)
    PropertyNode* positions[2]={board.getStart(), board.getStart()};
    //each with $1,500
    int money[2] = {1500,1500};

    //seed the random number generator with vurrrent time
    srand(time(0));
    //Game loop: 10 turrn total
    for(int t= 1; t <=10; t++)
        {
            //turn 1->Allen(0), turn 2->Kevin(1),.....
            int i = (t-1) % 2;
            //Roll a die(1-6)
            int d = rand() % 6 + 1;
            //Move player forward d steps on the circular board
            positions[i] = board.move(positions[i], d);
            //print what happend in this turn
            cout << "\nTurn " << t << ": " << players[i] << " rolls" << d 
                << " , lands on " << positions[i]->name << endl;

            //Only if the square has a cost(not Go)
            if(positions[i]->cost > 0)
               {
                   //Case 1: Player already wons it = do nothing
                   if(positions[i]->owner == players[i] )
                   {
                       cout << players[i] << " already owns "<< positions[i]->name 
                           <<endl;
                   }
                    //Case 2:Someone else owns it = can't buy
                   else if(positions[i]->owner != "Unowned")
                   {
                       cout << players[i] << " can't buy "<< positions[i]->name 
                           <<" (owned by "<< positions[i]->owner<< ")" <<endl;
                   }
                    //Case 3: Unowned and player can afford it = BUY
                   else if(money[i] >= positions[i]->cost)
                   {
                       board.buy(positions[i], players[i]);
                       money[i] -= positions[i]-> cost;
                   }
                    //Case 4: Unowned player can't afford it 
                   else
                   {
                       cout << players[i]<<" can't afford " << positions[i]->name
                           << endl;
                   }
                   //show both playewwrs money after the transaction
                   cout << "Allen: $"<< money[0] << " | Kevin: $" << money[1] 
                       << endl;
               }
        }
        //print the final state of the board(who owns what)
        cout << "\n----Final Board----" << endl;
        board.printBoard();
        //end program
        return 0;

}
