#pragma once

#include <iterator>

#include <utility/link_stack.hpp>

#include "bst_node.hpp"

namespace rtcpp {

template <typename Node>
class node_stack {
  public:
  typedef typename Node::value_type* pointer;
  typedef const typename Node::value_type* const_pointer;
  typedef Node node_type;
  typedef Node* node_pointer;
  typedef Node value_type;
  typedef std::size_t size_type;
  private:
  node_pointer avail;
  public:
  node_stack(node_pointer p) noexcept : avail(p) {}
  node_stack() noexcept : avail(0) {}
  node_pointer allocate(size_type) noexcept;
  void deallocate(node_pointer p, size_type) noexcept;
};

template <typename T>
typename node_stack<T>::node_pointer node_stack<T>::allocate(size_type) noexcept
{
  node_pointer q = avail;
  if (avail)
    avail = avail->llink;
  return q;
}

template <typename T>
void node_stack<T>::deallocate(typename node_stack<T>::node_pointer p, size_type) noexcept
{
  if (!p)
    return;

  p->rlink = 0;
  p->llink = avail;
  avail = p;
}

}
