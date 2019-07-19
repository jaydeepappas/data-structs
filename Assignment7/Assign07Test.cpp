// FILE: Assign08Test.cpp
// An interactive test program for the new p_queue ADT.
#include <cctype>           // provides toupper
#include <iostream>         // provides cout and cin
#include <cstdlib>          // provides EXIT_SUCCESS and size_t
#include "DPQueue.h"        // with value_type defined as int

using namespace std;
using namespace CS3358_ssII2018_A7;

// PROTOTYPES for functions used by this test program:
void print_menu();
// Pre:  (none)
// Post: A menu of choices for this program has been written to cout.

char get_user_command();
// Pre:  (none)
// Post: The user has been prompted to enter a one character command.
// The next character has been read (skipping blanks and newline
// characters), and this character has been returned.

int get_data();
// Pre:  (none)
// Post: The user has been prompted to enter an integer. The number
// has been read, echoed to the screen, and returned by the function.

p_queue::size_type get_priority();
// Pre:  (none)
// Post: The user has been prompted to enter an integer. The number
// has been read, echoed to the screen, and returned by the function.

int main()
{
   p_queue test; // PQ to perform test on
   char choice;  // command character entered by user
   int data;     // PQ item data entered by user
   p_queue::size_type priority; // PQ item priority entered by user

   cout << "I have created an empty p_queue (PQ)." << endl;
   cout << "The data of an item of this PQ will be an integer,\n";
   cout << "and the priority associated with each item of this PQ\n";
   cout << "will be a nonnegative integer." << endl;

   do
   {
      print_menu();
      choice = toupper( get_user_command() );
      switch (choice)
      {
      case 'E':
         data = get_data();
         priority = get_priority();
         test.push(data, priority);
         cout << "Item with data " << data << " and priority "
              << priority << " has been enqueued." << endl;
         break;
      case 'D':
         if ( !test.empty() )
         {
            cout << "Item " << test.front() << " has been dequeued."
                 << endl;
            test.pop();
         }
         else
            cout << "PQ is empty, nothing to dequeue." << endl;
         break;
      case 'S':
         if ( test.empty() )
            cout << "PQ is empty." << endl;
         else
            cout << "PQ is not empty." << endl;
         break;
      case 'N':
         cout << "Number of items in PQ is " << test.size() << endl;
         break;
      case 'A':
         test.print_array("PQ as array: ");
         cout << endl;
         break;
      case 'T':
         test.print_tree("PQ as tree: ");
         break;
      case 'Q':
         cout << "Bye.." << endl;
         break;
      default:
         cout << choice << " is invalid. Sorry." << endl;
      }
   }
   while ((choice != 'Q'));

   return EXIT_SUCCESS;
}

void print_menu()
{
   clog << endl; // print blank line before the menu
   clog << "The following choices are available: " << endl;
   clog << " E   (E)nqueue (add) an item into PQ" << endl;
   clog << " D   (D)equeue (remove) an item from PQ" << endl;
   clog << " S   (S)tatus (empty or non-empty) of PQ" << endl;
   clog << " N   (N)number of items in PQ" << endl;
   clog << " A   (A)rray display of PQ" << endl;
   clog << " T   (T)ree display of PQ" << endl;
   clog << " Q   (Q)uit this test program" << endl;
}

char get_user_command()
{
   char command;

   cout << "Enter choice: ";
   cin >> command; // read a character, skipping whitespaces
   cin.ignore(999, '\n');

   cout << command << " has been read for choice." << endl;
   return command;
}

int get_data()
{
   int number;

   cout << "Enter integer item data: ";
   cin  >> number;
   while ( ! cin.good() )
   {
      cerr << "Invalid input..."<< endl;
      cin.clear();
      cin.ignore(999, '\n');
      cout << "Please re-enter integer item data: ";
      cin  >> number;
   }
   cin.ignore(999, '\n');
   cout << number << " has been read for data." << endl;
   return number;
}

p_queue::size_type get_priority()
{
   p_queue::size_type priority;
   char oneChar;
   bool done = true;

   cout << "Enter priority: " << flush;
   cin >> ws;
   oneChar = cin.peek();
   if ( !isdigit(oneChar) )
   {
      while ( !isdigit(oneChar) || !done)
      {
         if ( !isdigit(oneChar) )
            cin.get(oneChar);
         if (oneChar == '\n')
         {
            cerr << "Invalid input..."<< endl << flush;
            cout << "Please re-enter priority: " << flush;
            done = false;
         }
         else
            done = true;
         oneChar = cin.peek();
      }
   }
   cin  >> priority;
   cin.ignore(999, '\n');
   cout << priority << " has been read for priority." << endl;

   return priority;
}
