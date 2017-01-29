#include "elements.h"

namespace Cache
{
  namespace Elements
  {
  std::string* read(Element *elem)
    {
      touch(elem);
      std::string *str = &elem->val;
      return str;
    }

    void touch(Element *elem)
    {
      elem->accessed_at = std::time(nullptr);
    }

    void swap(Element *elem_a, Element *elem_b)
    {
      Element *before_elem(0);
      Element *after_elem(0);

      if (elem_a) before_elem = elem_a->prev;
      if (elem_b) after_elem = elem_b->next;

      if (elem_b)
      {
        elem_b->prev = before_elem;
        elem_b->next = elem_a;
      }
      if (elem_a)
      {
        elem_a->prev = elem_b;
        elem_a->next = after_elem;
      }
    }

    void remove(Element *elem)
    {
      Element *prev = elem->prev;
      Element *next = elem->next;
      if (prev) prev->next = next;
      if (next) next->prev = prev;
    }

    void add(Element *elem, Element *head)
    {
      elem->next = head;
      elem->prev = nullptr;
      if (head) head->prev = elem;
    }
  }
}
