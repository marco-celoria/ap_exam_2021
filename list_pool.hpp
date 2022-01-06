#pragma once
#include <vector>
#include <iostream>
#include <cassert>
// TODO: pass the exam :)

template <typename node_t, typename T, typename N>
class _iterator {
  
public:
  using value_type = T;
  using list_type = N;
  using reference = value_type&;
  using pointer = value_type*;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;
  using size_type = typename std::vector<node_t>::size_type;
  
  _iterator(std::vector<node_t> * ptr, list_type x) noexcept : ptr_pool{ptr}, current{x} {}
  // We do not acquire any resources
  
  reference operator*() const  {
    check(current, "dereference past end");
    return (*ptr_pool)[current-1].value;
  }
  
  pointer operator->() const  { // delegate the real work to the dereference operator
    return & this->operator*();
  }
  
  _iterator& operator++()  {  // pre-increment
    check(current, "increment past end");
    current = (*ptr_pool)[current-1].next;
    return *this;
  }
  
  _iterator operator++(int)  {  // post-increment
    auto tmp = *this;
    ++(*this);
    return tmp;
  }
  
  friend bool operator==(const _iterator& x, const _iterator& y) noexcept {
    return x.current == y.current;
  }
  
  friend bool operator!=(const _iterator& x, const _iterator& y) noexcept {
    return !(x == y);
  }
  
private:
  std::vector<node_t> * ptr_pool ;
  N current;
  
  void check(list_type i, const std::string &msg) const {
      if (size_type(i) < 1 || size_type(i) > ptr_pool->size())
	throw std::out_of_range(msg);
  }
};

template <typename T, typename N = std::size_t>
class list_pool {
  
  struct node_t {
    node_t() noexcept = default;
    node_t(const T v, const N n) : value{v}, next{n} {}
    // Question: When I move/move-assign nodes, I am moving also the T value object.
    // What if the T object is complicated, and it has a move constructor that throws an error?
    // Maybe it is better to mark it as potentially-throwing...
    T value;
    N next;
    };
  
  using list_type = N;
  using value_type = T;
  using size_type = typename std::vector<node_t>::size_type;
    
  std::vector<node_t> pool;
  list_type free_node_list{0}; // at the beginning, it is empty
  
  node_t& node(list_type x) noexcept { return pool[x-1]; }
  const node_t& node(list_type x) const noexcept { return pool[x-1]; }
  
  template <typename X>
  list_type _push_front(X&& val, list_type head)
  {
    if (free_node_list) {
      auto new_head = free_node_list;
      free_node_list=next(free_node_list);
      value(new_head)=val;
      if (is_empty(head)) next(new_head)=end();
      else next(new_head)=head;
      return new_head;
    }
    else {
      if (is_empty(head)) pool.emplace_back(val, end());
      else pool.emplace_back(val, head);
      return pool.size();
    }
  }
  
  template <typename X>
  list_type _push_back(X&& val, list_type head) {
    if (is_empty(head)) return push_front(val, head);
        // find last node
    list_type it = head;
    while(next(it)!= end()) it=next(it);
    if (free_node_list) {
      auto new_tail = free_node_list;
      free_node_list=next(free_node_list);
      value(new_tail)=val;
      next(new_tail)=end();
      next(it)=new_tail;
    }
    else {
      pool.emplace_back(val, end());
      next(it)=pool.size();
    }
    return head;
  }

  /*
  void _print(list_type it) const noexcept {  // This makes sense only if value is ``printable''
    while(it!= end()) {
      std::cout << value(it) << " " ;         // Maybe it is better to comment this function
      it=next(it);                            // We cannot std::cout << std::vector(..) ..
    }
    std::cout << std::endl;
  }
  */
  
public:
  
  list_pool() noexcept = default ;
  explicit list_pool(size_type n) {  pool.reserve(n); } // reserve n nodes in the pool
  
  using iterator =  _iterator<node_t, T, N>;
  using const_iterator =  _iterator<node_t, const T,  N>;
  
  iterator begin(list_type head) noexcept { return iterator{ &pool, head }; }
  iterator end(list_type ) noexcept { return iterator{ &pool, list_type (0) }; } // this is not a typo
  
  const_iterator begin(list_type head) const noexcept { return const_iterator{ &pool, head }; }
  const_iterator end(list_type ) const noexcept { return const_iterator{ &pool, list_type(0) };  }
  
  const_iterator cbegin(list_type head) const noexcept { return const_iterator{ const_cast<std::vector<node_t> *>(&pool), head }; }
  const_iterator cend(list_type ) const noexcept { return const_iterator{const_cast<std::vector<node_t> *>(&pool), list_type(0) }; }
  
  list_type new_list()  { reserve(8); return list_type(0); } // return an empty list
  
  void reserve(size_type n) { pool.reserve(n); } // reserve n nodes in the pool
  
  size_type capacity() const noexcept { return pool.capacity(); } // the capacity of the pool
  
  bool is_empty(list_type x) const noexcept { return x==end(); }
  
  list_type end() const noexcept { return list_type(0); }
  
  T& value(list_type x) noexcept { return node(x).value; }
  
  const T& value(list_type x) const noexcept { return node(x).value; }
  
  list_type& next(list_type x) noexcept { return node(x).next; }
  
  const list_type& next(list_type x) const noexcept { return node(x).next; }
  
  list_type push_front(const T& val, list_type head) { return _push_front(val,head); }
  list_type push_front(T&& val, list_type head)      { return _push_front(std::move(val), head); }
  list_type push_back(const T& val, list_type head)  { return _push_back(val,head); }
  list_type push_back(T&& val, list_type head)       { return _push_back(std::move(val), head); }
  
  list_type free(list_type x) noexcept { // delete first node
    if(is_empty(x)) { std::cout << "The list is already empty" << std::endl; return x;}
    auto tmp = next(x);
    next(x) = free_node_list;
    free_node_list = x;
    return tmp;
  }
  
  list_type free_list(list_type x) noexcept { // free entire list
    if(is_empty(x)) { std::cout <<"The list is already empty" << std::endl; return x; }
    while(x!= end())
      x=free(x);
    return x;
  }
  
  size_type list_size(list_type head) const noexcept {
    size_type cnt = 0;
    while(head!= end()) {
      ++cnt;
      head=next(head);
    }
    return cnt;
  }
  /*
  void print_list(const list_type head) const noexcept {
    _print(head);
  }
  
  void print_free_list() const noexcept {
    _print(free_node_list);
  }
  
  void print_pool() const noexcept {
    if(pool.size()==0) { std::cout << "pool is empty" << std::endl; return; }
    for(size_type i = 0; i < pool.size() ; ++i)
      std::cout << "(pool[" << i << "].value = " << pool[i].value
		<< ", pool[" << i << "].next= " << pool[i].next << " )" << std::endl;
  }
  */
};
