#ifndef NODES_LLOLL_H
#define NODES_LLOLL_H

#include <iostream>    // for ostream

namespace CS3358_ssII2018_A5P2
{
   // child node
   struct CNode
   {
      int data;
      CNode* link;
   };

   // parent node
   struct PNode
   {
      CNode* data;
      PNode* link;
   };

   // toolkit functions for LLoLL based on above node definitions
   void Destroy_cList(CNode*& cListHead);
   void Destroy_pList(PNode*& pListHead);
   void ShowAll_DF(PNode* pListHead, std::ostream& outs);
   void ShowAll_BF(PNode* pListHead, std::ostream& outs);
}

#endif
