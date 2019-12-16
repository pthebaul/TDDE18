#ifndef _LIST_H_
#define _LIST_H_

#include <iostream>
#include <string>

template <typename Data>
class List
{
public:
  List();
  ~List() { delete first; }

  void insert(Data const& d);
  
  List(List const&);
  List(List&&);
  List& operator=(List const&);
  List& operator=(List&&);

  class Iterator
  {
  public:
      Iterator(typename List<Data>::Link*);
      Iterator& operator++();
      Data operator*() const;
      bool operator!=(Iterator const&) const;
  private:
      typename List<Data>::Link* ptr;
  };

  Iterator begin() const;
  Iterator end() const;
    
private:

  class Link
  {
  public:
    Link(Data const& d, Link* n)
      : data(d), next(n) {}
    ~Link() { delete next; }
    
    friend class List;

    static Link* clone(Link const*);
    
  private:
    
    Data data;
    Link* next;
  };
  
  Link* first;
  
public:

  using value_type = Data;

  // Suitable place to add things...
  
};

template <typename Data>
std::ostream& operator<<(std::ostream&, List<Data> const&);

#include "list.tcc"
#endif
