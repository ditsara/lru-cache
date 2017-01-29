#ifndef STORE_H_INCLUDED
#define STORE_H_INCLUDED

#include <string>
#include <unordered_map>
#include "elements.h"

namespace Cache
{

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
    bool store(Store *store, const std::string &key, const std::string &val);
    bool replace(Store *store, const std::string &key, const std::string &val);
    std::string* retrieve(const Store &store, const std::string &key);
  }
}

#endif // STORE_H_INCLUDED
