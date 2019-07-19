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
                   const int caseValues1[], int caseSize1,
                   const int caseValues2[], int caseSize2);
void InsertSortedNonDec(int array[], int& used, int newValue);
void CombineSortedNonDec(const int array1[], const int array2[], int array3[],
                         int used1, int used2) ;

int main()
{
   int testCasesToDo = 990000,
       testCasesDone = 0,
       loSize = 0,
       hiSize = 10,
       loValue = -9,
       hiValue = 9;
   int used1,
       used2,
       used3,
       intCount,
       newInt,
       iLenChk1;
   int *intArr1 = 0,
       *intArr2 = 0,
       *intArr3 = 0;
   Node *headX = 0,
        *headY = 0,
        *headZ = 0;
   SortedMergeRecur(headX, headY, headZ);
   cout << "================================" << endl;
   if (headX == 0 && headY == 0 && headZ == 0)
      cout << "passed test on empty List X & Y" << endl;
   else
   {
      cout << "failed test on empty List X & Y ... 1 or more of the 3 lists  not empty" << endl;
      exit(EXIT_FAILURE);
   }

   // SeedRand(); // disabled for reproducible result

   do
   {
      ++testCasesDone;
      used1 = BoundedRandomInt(loSize, hiSize);
      used2 = BoundedRandomInt(loSize, hiSize);
      used3 = used1 + used2;
      if (used1 > 0) intArr1 = new int [used1];
      if (used2 > 0) intArr2 = new int [used2];
      if (used3 > 0) intArr3 = new int [used3];

      intCount = 0;
      while (intCount < used1)
      {
         newInt = BoundedRandomInt(loValue, hiValue);
         InsertSortedNonDec(intArr1, intCount, newInt);
         InsertSortedUp(headX, newInt);
      }
      intCount = 0;
      while (intCount < used2)
      {
         newInt = BoundedRandomInt(loValue, hiValue);
         InsertSortedNonDec(intArr2, intCount, newInt);
         InsertSortedUp(headY, newInt);
      }
      CombineSortedNonDec(intArr1, intArr2, intArr3, used1, used2);

    //DebugShowCase(testCasesDone, testCasesToDo, intArr1, used1, intArr2, used2);

      SortedMergeRecur(headX, headY, headZ);

      if (headX != 0 || headY != 0)
      {
         cout << "ListX and/or ListY not empty ..." << endl;
         cout << "test_case - ListX: ";
         ShowArray(intArr1, used1);
         cout << "            ListY: ";
         ShowArray(intArr2, used2);
         exit(EXIT_FAILURE);
      }

      iLenChk1 = ListLengthCheck(headZ, used3);
      if (iLenChk1 != 0)
      {
         if (iLenChk1 == -1)
         {
            cout << "ListZ node-count error ... too few" << endl;
            cout << "test_case - ListX: ";
            ShowArray(intArr1, used1);
            cout << "            ListY: ";
            ShowArray(intArr2, used2);
            cout << "#expected: " << used3 << endl;
            cout << "#returned: " << FindListLength(headZ) << endl;
         }
         else
         {
            cout << "ListZ node-count error ... too many (circular list?)" << endl;
            cout << "test_case - ListX: ";
            ShowArray(intArr1, used1);
            cout << "            ListY: ";
            ShowArray(intArr2, used2);
            cout << "#expected: " << used3 << endl;
            cout << "returned # is higher (may be infinite)" << endl;
         }
         exit(EXIT_FAILURE);
      }

      if ( !match(headZ, intArr3, used3) )
      {
         cout << "List Z Contents error ... mismatch found in value or order" << endl;
         cout << "initial X: ";
         ShowArray(intArr1, used1);
         cout << "initial Y: ";
         ShowArray(intArr2, used2);
         cout << "ought2b Z: ";
         ShowArray(intArr3, used3);
         cout << "outcome Z: ";
         ShowAll(cout, headZ);
         exit(EXIT_FAILURE);
      }

      if (testCasesDone <= 5 || testCasesDone % 45000 == 0)
      {
         cout << "================================" << endl;
         clog << "testing case " << testCasesDone
              << " of " << testCasesToDo << endl;
         clog << "================================" << endl;
         cout << "test case " << testCasesDone
              << " of " << testCasesToDo << endl;
         cout << "initial X: ";
         ShowArray(intArr1, used1);
         cout << "initial Y: ";
         ShowArray(intArr2, used2);
         cout << "ought2b Z: ";
         ShowArray(intArr3, used3);
         cout << "outcome Z: ";
         ShowAll(cout, headZ);
      }

      ListClear(headX, 1); // in case not empty
      ListClear(headY, 1); // in case not empty
      ListClear(headZ, 1);
      delete [] intArr1;
      delete [] intArr2;
      delete [] intArr3;
      intArr1 = intArr2 = intArr3 = 0;
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
                   const int caseValues1[], int caseSize1,
                   const int caseValues2[], int caseSize2)
{
      cout << "test case " << whichCase
           << " of " << totalCasesToDo << endl;
      cout << "given X: ";
      ShowArray(caseValues1, caseSize1);
      cout << "given Y: ";
      ShowArray(caseValues2, caseSize2);
}

void InsertSortedNonDec(int array[], int& used, int newValue)
{
   int probeIndex = used;
   while (probeIndex > 0 && array[probeIndex - 1] > newValue)
   {
      array[probeIndex] = array[probeIndex - 1];
      --probeIndex;
   }
   array[probeIndex] = newValue;
   ++used;
}

void CombineSortedNonDec(const int array1[], const int array2[], int array3[],
                         int used1, int used2)
{
   int array1Index = 0, array2Index = 0, array3Index = 0;
   while (array1Index < used1 && array2Index < used2)
   {
      if (array1[array1Index] < array2[array2Index])
         array3[array3Index++] = array1[array1Index++];
      else
         array3[array3Index++] = array2[array2Index++];
   }
   while (array1Index < used1)
      array3[array3Index++] = array1[array1Index++];
   while (array2Index < used2)
      array3[array3Index++] = array2[array2Index++];
}
