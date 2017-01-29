#include "store.h"

namespace Cache
{
  namespace Actions
  {
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
      map_t &lookup = *(store->lookup);
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
