#include "llcpInt.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void SeedRand();
int BoundedRandomInt(int lowerBound, int upperBound);
int ListLengthCheck(Node* head, int whatItShouldBe);
bool match(Node* head, const int procInts[], int procSize);
void ShowArray(const int a[], int size);
void DebugShowCase(int whichCase, int totalCasesToDo,
                   const int caseValues[], int caseSize);

int main()
{
   int testCasesToDo = 750000,
       testCasesDone = 0,
       loSize = 1,
       hiSize = 25,
       loValue = 0,
       hiValue = 9;
   int numInts,
       numOdds,
       numEvens,
       intCount,
       newInt,
       iLenChk,
       iOdd,
       iEven,
       iProc;
   int *rawInts = 0,
       *procInts = 0,
       *rawOddInts = 0,
       *rawEvenInts = 0;
   Node* head = 0;

   InterleaveOddsAndEvensInOrigOrder(head);
   cout << "================================" << endl;
   cout << "passed crash test on empty list" << endl;

   // SeedRand(); // disabled for reproducible result

   do
   {
      ++testCasesDone;
      numInts = BoundedRandomInt(loSize, hiSize);
      numOdds = numEvens = 0;
      rawInts = new int [numInts];
      procInts = new int [numInts];
      rawOddInts = new int [numInts];
      rawEvenInts = new int [numInts];

      intCount = 0;
      while (intCount < numInts)
      {
         newInt = BoundedRandomInt(loValue, hiValue);
         rawInts[intCount++] = newInt;
         if (newInt % 2)
            rawOddInts[numOdds++] = newInt;
         else
            rawEvenInts[numEvens++] = newInt;
         InsertAsTail(head, newInt);
      }
      iOdd = iEven = iProc = 0;
      if (rawInts[0] % 2)
      {
         while (iProc < numInts)
         {
            if (iOdd < numOdds)
               procInts[iProc++] = rawOddInts[iOdd++];
            if (iEven < numEvens)
               procInts[iProc++] = rawEvenInts[iEven++];
         }
      }
      else
      {
         while (iProc < numInts)
         {
            if (iEven < numEvens)
               procInts[iProc++] = rawEvenInts[iEven++];
            if (iOdd < numOdds)
               procInts[iProc++] = rawOddInts[iOdd++];
         }
      }

      // DebugShowCase(testCasesDone, testCasesToDo, rawInts, numInts);

      InterleaveOddsAndEvensInOrigOrder(head);
      iLenChk = ListLengthCheck(head, numInts);
      if (iLenChk != 0)
      {
         if (iLenChk == -1)
         {
            cout << "Node-count error ... too few" << endl;
            cout << "test_case: ";
            ShowArray(rawInts, numInts);
            cout << "#expected: " << numInts << endl;
            cout << "#returned: " << FindListLength(head) << endl;
         }
         else
         {
            cout << "Node-count error ... too many (circular list?)" << endl;
            cout << "test_case: ";
            ShowArray(rawInts, numInts);
            cout << "#expected: " << numInts << endl;
            cout << "returned # is higher (may be infinite)" << endl;
         }
         exit(EXIT_FAILURE);
      }
      if (! match(head, procInts, numInts) )
      {
         cout << "Contents error ... mismatch found in value or order" << endl;
         cout << "initial: ";
         ShowArray(rawInts, numInts);
         cout << "ought2b: ";
         ShowArray(procInts, numInts);
         cout << "outcome: ";
         ShowAll(cout, head);
         exit(EXIT_FAILURE);
      }

      if (testCasesDone % 10000 == 0)
      {
         cout << "================================" << endl;
         clog << "testing case " << testCasesDone
              << " of " << testCasesToDo << endl;
         clog << "================================" << endl;
         // cout << "test case " << testCasesDone
         //      << " of " << testCasesToDo << endl;
         cout << "initial: ";
         ShowArray(rawInts, numInts);
         cout << "ought2b: ";
         ShowArray(procInts, numInts);
         cout << "outcome: ";
         ShowAll(cout, head);
      }

      ListClear(head, 1);
      delete [] rawInts;
      delete [] procInts;
      delete [] rawOddInts;
      delete [] rawEvenInts;
      rawInts = procInts = rawOddInts = rawEvenInts = 0;
   }
   while (testCasesDone < testCasesToDo);
   cout << "================================" << endl;
   cout << "test program terminated normally" << endl;
   cout << "================================" << endl;

   return EXIT_SUCCESS;
}

/////////////////////////////////////////////////////////////////////
// Function to seed the random number generator
// PRE:  none
// POST: The random number generator has been seeded.
/////////////////////////////////////////////////////////////////////
void SeedRand()
{
   srand( (unsigned) time(NULL) );
}

/////////////////////////////////////////////////////////////////////
// Function to generate a random integer between
// lowerBound and upperBound (inclusive)
// PRE:  lowerBound is a positive integer.
//       upperBound is a positive integer.
//       upperBound is larger than lowerBound
//       The random number generator has been seeded.
// POST: A random integer between lowerBound and upperBound
//       has been returned.
/////////////////////////////////////////////////////////////////////
int BoundedRandomInt(int lowerBound, int upperBound)
{
   return ( rand() % (upperBound - lowerBound + 1) ) + lowerBound;
}

/////////////////////////////////////////////////////////////////////
// Function to check # of nodes in list against what it should be
// POST: returns
//          -1 if # of nodes is less than what it should be
//           0 if # of nodes is equal to  what it should be
//           1 if # of nodes is more than what it should be
/////////////////////////////////////////////////////////////////////
int ListLengthCheck(Node* head, int whatItShouldBe)
{
   int length = 0;
   while (head != 0)
   {
      ++length;
      if (length > whatItShouldBe) return 1;
      head = head->link;
   }
   return (length < whatItShouldBe) ? -1 : 0;
}

bool match(Node* head, const int procInts[], int procSize)
{
   int iProc = 0;
   while (head != 0)
   {
      if (iProc == procSize) return false;
      if (head->data != procInts[iProc]) return false;
      ++iProc;
      head = head->link;
   }
   return true;
}

void ShowArray(const int a[], int size)
{
   for (int i = 0; i < size; ++i)
      cout << a[i] << "  ";
   cout << endl;
}

void DebugShowCase(int whichCase, int totalCasesToDo,
                   const int caseValues[], int caseSize)
{
      cout << "test case " << whichCase
           << " of " << totalCasesToDo << endl;
      cout << "given list: ";
      ShowArray(caseValues, caseSize);
}
