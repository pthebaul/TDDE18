#include <algorithm>
#include <iostream>

template <typename Data>
void List<Data>::insert(Data const& d)
{
  first = new Link(d, first);
}

//-----------------------------------------------------//
// Important copy and assignment stuff
template <typename Data>
typename List<Data>::Link* List<Data>::Link::clone(Link const* dolly)
{
  if ( dolly != nullptr )
    return new Link(dolly->data, clone(dolly->next));
  else
    return nullptr;
}

template <typename Data>
List<Data>::List() : first(nullptr)
{
  std::clog << "***Default construction" << std::endl;
}

template <typename Data>
List<Data>::List(List const& l)
{
  std::clog << "***Copy construction" << std::endl;
  first = Link::clone(l.first);
}

template <typename Data>
List<Data>::List(List&& l)
{
  std::clog << "***Move construction" << std::endl;
  first = l.first;
  l.first = nullptr;
}

template <typename Data>
List<Data>& List<Data>::operator=(List const& rhs)
{
  std::clog << "***Copy assignment" << std::endl;
  if (&rhs != this)
  {
    List copy(rhs);
    std::swap(first, copy.first);
  }
  return *this;
}

template <typename Data>
List<Data>& List<Data>::operator=(List&& rhs)
{
  std::clog << "***Move assignment" << std::endl;
  if (&rhs != this)
  {
    std::swap(first, rhs.first);
  }
  return *this;
}

//-----------------------------------------------------//
// Iterator implementation

template <typename Data>
List<Data>::Iterator::Iterator(typename List<Data>::Link* ptr) : ptr{ptr} {}

template <typename Data>
typename List<Data>::Iterator List<Data>::begin() const
{
    return Iterator(first);
}

template <typename Data>
typename List<Data>::Iterator List<Data>::end() const
{
    return Iterator(nullptr);
}

template <typename Data>
bool List<Data>::Iterator::operator!=(typename List<Data>::Iterator const& other) const
{
    return ptr != other.ptr;
}

template <typename Data>
Data List<Data>::Iterator::operator*() const
{
    return ptr->data;
}

template <typename Data>
typename List<Data>::Iterator& List<Data>::Iterator::operator++()
{
    ptr = ptr->next;
    return *this;
}

template <typename Data>
std::ostream& operator<<(std::ostream& os, List<Data> const& list)
{
    for ( auto elt : list )
    {
	os << elt << " ";
    }
    os << std::endl;
    return os;
}
