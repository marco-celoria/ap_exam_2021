#pragma once
#include <vector>
#include <iostream>
#include <cassert>
#include <stdexcept>      // std::out_of_range
// TODO: pass the exam :)

struct out_of_range {
  std::string message;
  out_of_range(std::string s) : message{std::move(s)} {}
};

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
  
  _iterator(std::vector<node_t> * ptr, list_type x) noexcept : ptr_pool{ptr}, current{x} {} // We do not acquire any resources
  
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
      // throw out_of_range(msg);
      throw std::out_of_range(msg);
  }
};

template <typename T, typename N = std::size_t>
class list_pool {
  
  struct node_t {
    node_t() noexcept = default;                                             // I hope that the default constructor of T does not throw error...
    node_t(const T &v, const N n) noexcept: value{v}, next{n} {}             // To be noexcept, or not to be noexcept, that is the question.
    node_t( T &&v, const N n)     noexcept: value{std::move(v)}, next{n} {}  // To be noexcept, or not to be noexcept, that is the question.
    node_t(node_t&&) noexcept = default;
    node_t& operator=(node_t&&) noexcept = default;
    node_t(const node_t& ) = default;
    node_t& operator=(const node_t& ) = default;
    ~node_t() = default;  // noexcept by default, right?
    
    //node_t() {std::cout << "note_t default constructor" << std::endl;}
    
    //node_t(node_t&& that) noexcept : value{std::move(that.value)}, next{std::move(that.next)} {std::cout << "note_t move constructor" << std::endl;}
    
    //node_t& operator=(node_t&&that) noexcept {
    //    if (this != &that){value=std::move(that.value); next= std::move(that.next);}
    //    std::cout << "note_t move assignment" << std::endl; return *this;
    //}
    
    //node_t& operator=(node_t&&) noexcept = default;
    //node_t(const node_t& that ) : value{that.value}, next{that.next}  {std::cout << "note_t copy constructor" << std::endl;}
    //node_t& operator=(const node_t& that) {
    //    if (this != &that){value=that.value; next=that.next;} std::cout << "note_t copy assignment" << std::endl; return *this;
    //}
    
    // //~node_t() {std::cout << "note_t default destructor" << std::endl;}
    
    // Question: When I move/move-assign nodes, I am moving also the T value object. Right?
    // What if the T object is complicated, and it has a move constructor that throws an error?
    // Maybe it is better to mark it as potentially-throwing...
    // May std::move_if_noexcept(g); be a good idea to suggest std::vector<node_t> to use move semantics for Non-throwing nodes ?
    // Or maybe something like
    // C& operator=(C&& c) noexcept(alloc_traits::propagate_on_container_move_assignment{} || alloc_traits::is_always_equal{});
    // Final decision: we adopt risky NOT Strong exception safety policy, we are HPC and we opt for noexpect moves
    
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
      value(new_head)=std::forward<X>(val);
      if (is_empty(head)) next(new_head)=end();
      else next(new_head)=head;
      return new_head;
    }
    else {
      if (is_empty(head)) {pool.emplace_back(std::forward<X>(val), end());}
      else  {pool.emplace_back(std::forward<X>(val), head);}
      return pool.size();
    }
  }
  
  template <typename X>
  list_type _push_back(X&& val, list_type head) {
    if (is_empty(head)) return _push_front(std::forward<X>(val), head);
    // find last node
    list_type it = head;
    while(next(it)!= end()) it=next(it);
    if (free_node_list) {
      auto new_tail = free_node_list;
      free_node_list=next(free_node_list);
      value(new_tail)=std::forward<X>(val);
      next(new_tail)=end();
      next(it)=new_tail;
    }
    else {
      pool.emplace_back(std::forward<X>(val), end());
      next(it)=pool.size();
    }
    return head;
  }
  
  /*
    void _print(list_type it) const noexcept {  // This makes sense only if value is ``printable'' (it has a << operator overloaded)
    while(it!= end()) {
    std::cout << value(it) << " " ;           // Maybe it is better to comment this function (although might be useful for debugging)
    it=next(it);                              // Actually, we cannot std::cout << std::vector(..) ..
    }
    std::cout << std::endl;
    }
  */
  
public:
  
  list_pool() noexcept = default ;
  
  explicit list_pool(size_type n) {  pool.reserve(n); }   // reserve n nodes in the pool

  list_pool(list_pool&& x) noexcept = default;            
  
  list_pool& operator=(list_pool&& x) noexcept = default; 
  
  list_pool(const list_pool& that) = default;
  
  list_pool& operator=(const list_pool& x) = default;
  
  ~list_pool() = default; // noexcept by default, right?
  
  //list_pool() noexcept {std::cout << "list_pool default constructor" << std::endl;}
  
  //list_pool(list_pool&& that) noexcept : pool{std::move(that.pool)}, free_node_list{std::move(that.free_node_list)}
  // {std::cout << "list_pool move constructor" << std::endl;}
  
  //list_pool& operator=(list_pool&& that) noexcept {
  //    if (this != &that){pool=std::move(that.pool); free_node_list=std::move(that.free_node_list);}
  //    std::cout << "list_pool move assignment" << std::endl;  return *this;
  //}
  
  //list_pool(const list_pool& that) : pool{that.pool}, free_node_list{that.free_node_list} {std::cout << "list_pool copy constructor" << std::endl;}
  
  //list_pool& operator=(const list_pool& that) {
  //    if (this != &that){pool=that.pool; free_node_list=that.free_node_list;}
  //    std::cout << "list_pool copy assignment" << std::endl; return *this;
  //}
  
  //~list_pool()  {std::cout << "list_pool default destructor" << std::endl;}
  
  using iterator =  _iterator<node_t, T, N>;
  using const_iterator =  _iterator<node_t, const T,  N>;
  
  iterator begin(list_type head) noexcept {
    //  std::cout << "[Ab]" << std::endl;
    return iterator{ &pool, head };
  }
  iterator end(list_type ) noexcept { // this is not a typo
    //  std::cout << "[Ae]" << std::endl;
    return iterator{ &pool, list_type (0) };
  } 
  
  const_iterator begin(list_type head) const noexcept {
    //  std::cout << "[Bb]" << std::endl;
    return const_iterator{const_cast<std::vector<node_t>*>(&pool), head};
  }
  const_iterator end(list_type ) const noexcept {
    //  std::cout << "[Be]" << std::endl;
    return const_iterator{const_cast<std::vector<node_t>*>(&pool), list_type(0)};
  }
  
  const_iterator cbegin(list_type head) const noexcept {
    //  std::cout << "[Cb]" << std::endl;
    return const_iterator{const_cast<std::vector<node_t>*>(&pool), head};
  }
  const_iterator cend(list_type ) const noexcept {
    //  std::cout << "[Ce]" << std::endl;
    return const_iterator{const_cast<std::vector<node_t>*>(&pool), list_type(0)};
  }
  
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
    if(is_empty(x)) { std::cout << "The list is already empty" << std::endl; return x;} // This is not the best, but other possibilities give weird behaviors
    auto tmp = next(x);
    next(x) = free_node_list;
    free_node_list = x;
    return tmp;
  }
  
  list_type free_list(list_type x) noexcept { // free entire list
    if(is_empty(x)) { std::cout << "The list is already empty" << std::endl; return x; }
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
