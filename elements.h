#ifndef ELEMENTS_H_INCLUDED
#define ELEMENTS_H_INCLUDED

#include <ctime>
#include <string>

namespace Cache
{
  struct Element
  {
    Element *next;
    Element *prev;
    std::string key;
    std::string val;
    std::time_t accessed_at;
  };

  namespace Elements
  {
    std::string* read(Element *elem);
    void touch(Element *elem);
    void swap(Element *elem_a, Element *elem_b);
    void remove(Element *elem);
    void add(Element *elem, Element *head);
  }
}


#endif // ELEMENTS_H_INCLUDED
