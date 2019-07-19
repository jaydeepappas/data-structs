#include "nodes_LLoLL.h"
#include <cstdlib>
using namespace std;
using namespace CS3358_ssII2018_A5P2;

void Build_cList(int argc, CNode*& cListHead);
void Build_pList(int argc, PNode*& pListHead);

int main(int argc, char* argv[])
{
   PNode* head_LLoLL = 0;
   char reply;
   do
   {
      Build_pList(argc, head_LLoLL);
      ShowAll_DF(head_LLoLL, cout);
      cout << endl;
      ShowAll_BF(head_LLoLL, cout);
      cout << endl;
      Destroy_pList(head_LLoLL);
      if (argc < 2)
         cout << "Another? (n = no, others = yes) ";
      cin >> reply;
   }
   while (reply != 'n' && reply != 'N');

   return EXIT_SUCCESS;
}

void Build_cList(int argc, CNode*& cListHead)
{
   int oneInt;
   char reply;
   CNode* cListTail = cListHead;
   if (argc < 2)
      cout << "Add cList data? (n = no, others = yes) ";
   cin >> reply;
   while (reply != 'n' && reply != 'N')
   {
      if (argc < 2)
         cout << "Enter cList data (int): ";
      cin >> oneInt;
      CNode* cNodePtr = new CNode;
      cNodePtr->data = oneInt;
      cNodePtr->link = 0;
      if (cListTail == 0)
         cListHead = cListTail = cNodePtr;
      else
      {
         cListTail->link = cNodePtr;
         cListTail = cNodePtr;
      }
      if (argc < 2)
         cout << "Add more cList data? (n = no, others = yes) ";
      cin >> reply;
   }
}

void Build_pList(int argc, PNode*& pListHead)
{
   char reply;
   PNode* pListTail = pListHead;
   if (argc < 2)
      cout << "Add cList to pList? (n = no, others = yes) ";
   cin >> reply;
   while (reply != 'n' && reply != 'N')
   {
      CNode* cListHead = 0;
      Build_cList(argc, cListHead);
      PNode* pNodePtr = new PNode;
      pNodePtr->data = cListHead;
      pNodePtr->link = 0;
      if (pListTail == 0)
         pListHead = pListTail = pNodePtr;
      else
      {
         pListTail->link = pNodePtr;
         pListTail = pNodePtr;
      }
      if (argc < 2)
         cout << "Add more cList to pList? (n = no, others = yes) ";
      cin >> reply;
   }
}
