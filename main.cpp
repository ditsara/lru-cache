#include <iostream>
#include <string>
#include <ctime>
#include <unordered_map>

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

  typedef std::unordered_map<std::string, Element*> map_t;
  struct Store
  {
    Cache::Element *head;
    Cache::Element *tail;
    map_t *lookup;

    int mem_limit;
    int size;
  };

  namespace Actions
  {
    bool create(Store *store, const std::string &key, const std::string &val);

    bool store(Store *store, const std::string &key, const std::string &val)
    {
      map_t &lookup = *(store->lookup);
      bool status;

      if (lookup[key]) status = true;
      else status = create(store, key, val);

      return status;
    }

    bool replace(Store *store, const std::string &key, const std::string &val)
    {
      map_t &lookup = *(store->lookup);
      Element *elem = lookup[key];
      elem->val = val;
      return true;
    }

    bool create(Store *store, const std::string &key, const std::string &val)
    {
      Element *elem = new Cache::Element { nullptr, nullptr, key, val };
      if (!elem) return false; // request denied!

      Cache::Elements::add(elem, store->head);

      store->head = elem;
      map_t lookup = *(store->lookup);
      lookup[key] = elem;

      return true;
    }

    std::string* retrieve(const Store &store, const std::string &key)
    {
      map_t &lookup = *(store.lookup);
      Element *elem = lookup[key];
      std::string *str = &(elem->val);
      return str;
    }
  }

}


int main()
{
  std::cout << "Hello world!" << std::endl;
  return 0;
}

