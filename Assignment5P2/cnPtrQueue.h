#ifndef CN_PTR_QUEUE_H
#define CN_PTR_QUEUE_H

#include <cstdlib>        // for size_t
#include <stack>          // for STL stack template
#include "nodes_LLoLL.h"  // for CNode

namespace CS3358_ssII2018_A5P2
{
   class cnPtrQueue
   {
   public:
      typedef std::size_t size_type;
      cnPtrQueue();
      bool empty() const;
      size_type size() const; // returns # of items in queue
      CNode* front();
      void push(CNode* cnPtr);
      void pop();
   private:
      std::stack<CNode*> inStack;
      std::stack<CNode*> outStack;
      size_type numItems;     // # of items in queue
   };
}

#endif
