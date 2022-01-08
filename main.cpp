//#include "list_pool.hpp"
#include "list_pool_instrumented.hpp"
#include <cassert>
#include <algorithm>
#include <vector>
#include <chrono>
#include <forward_list>
#include <list>
template <typename T,typename S > void boo_const (const list_pool<T> & x, S l)
{
  auto it = x.begin(l);
  std::cout << "const front element = " << *it << std::endl;
  // *it = 77;
}

template <typename T,typename S > void boo ( list_pool<T> & x, S l)
{
  auto it = x.begin(l);
  *it= 77;
  std::cout << "front element = " << *it << std::endl;
}

class foo
{
  friend std::ostream &operator<<(std::ostream &os, const foo &item) {
    os << item.msg;
    return os;
  }
  
public:
  foo() noexcept = default;
  foo(const std::string & message) noexcept : msg{message} {}
  foo(foo&&that) noexcept:  msg{std::move(that.msg)} {std::cout << "foo move constructor" << std::endl;}
  foo& operator=(foo&&that) noexcept { if (this != &that){msg=std::move(that.msg) ;} std::cout << "foo move assignment" << std::endl; return *this;}
  foo(const foo& that) noexcept: msg{that.msg} {std::cout << "foo copy constructor" << std::endl;}
  foo& operator=(const foo& that) noexcept {if (this != &that)
      {msg=that.msg ;} std::cout << "foo copy assignment" << std::endl; return *this;}
  ~foo() {std::cout << "foo default destructor" << std::endl;}
  std::string msg;
};

int main()
{
  std::cout << "Check empty list:" << std::endl;
  list_pool<int> empty_pool{};
  auto empty = empty_pool.new_list();
  long unsigned int cnt = 0;
  for(auto it = empty_pool.cbegin(empty); it !=  empty_pool.cend(empty); ++it )
    {
      std::cout << *it << std::endl;
      ++cnt;
    }
  if(empty_pool.list_size(empty)==cnt) std::cout << "OK the list is empty as expected" << std::endl;
  std::cout << "==============================="   << std::endl;
  std::cout << "Check push front, cbegin, cend, max element, min element:" << std::endl;
  list_pool<int> pool{};
  auto l1 = pool.new_list();
  cnt = 0;
  l1 = pool.push_front(11, l1);
  l1 = pool.push_front(10, l1);
  l1 = pool.push_front(9, l1);
  l1 = pool.push_front(8, l1);
  l1 = pool.push_front(7, l1);
  l1 = pool.push_front(6, l1);
  l1 = pool.push_front(5, l1);
  l1 = pool.push_front(4, l1);
  l1 = pool.push_front(3, l1);
  l1 = pool.push_front(2, l1);
  l1 = pool.push_front(1, l1);
  for(auto it = pool.cbegin(l1); it !=  pool.cend(l1); ++it )
    {
      std::cout << *it << " ";
      ++cnt;
    }
  std::cout << std::endl;
  auto M = std::max_element(pool.cbegin(l1), pool.cend(l1));
  std::cout << "*M=" << *M << std::endl;
  assert(*M == 11);
  
  auto m = std::min_element(pool.cbegin(l1), pool.cend(l1));
  assert(*m == 1);
  std::cout << "*m=" << *m << std::endl;
  std::cout << "==============================="   << std::endl;
  std::cout << "Check free list, push back, free:" << std::endl;
  for(auto it = pool.cbegin(l1); it !=  pool.cend(l1); ++it )
      std::cout << *it << " ";
  std::cout << std::endl;
  std::cout << "We now free_list" << std::endl;
  l1=pool.free_list(l1);
  for(auto it = pool.cbegin(l1); it !=  pool.cend(l1); ++it )
      std::cout << *it << " ";
  std::cout << std::endl;
  std::cout << "We now push_front 10 elements:" << std::endl;
  l1 = pool.push_back(1, l1);
  l1 = pool.push_back(2, l1);
  l1 = pool.push_back(3, l1);
  l1 = pool.push_back(4, l1);
  l1 = pool.push_back(5, l1);
  l1 = pool.push_back(6, l1);
  l1 = pool.push_back(7, l1);
  l1 = pool.push_back(8, l1);
  l1 = pool.push_back(9, l1);
  l1 = pool.push_back(10, l1);
  for(auto it = pool.cbegin(l1); it !=  pool.cend(l1); ++it )
      std::cout << *it << " ";
  std::cout << std::endl;
  std::cout << "We now free one element at time" << std::endl;
  l1 = pool.free(l1);
  for(auto it = pool.cbegin(l1); it !=  pool.cend(l1); ++it )
      std::cout << *it << " ";
  std::cout << std::endl;
  l1 = pool.free(l1);
  for(auto it = pool.cbegin(l1); it !=  pool.cend(l1); ++it )
      std::cout << *it << " ";
  std::cout << std::endl;
  l1 = pool.free(l1);
  for(auto it = pool.cbegin(l1); it !=  pool.cend(l1); ++it )
      std::cout << *it << " ";
  std::cout << std::endl;
  l1 = pool.free(l1);
  for(auto it = pool.cbegin(l1); it !=  pool.cend(l1); ++it )
      std::cout << *it << " ";
  std::cout << std::endl;
  l1 = pool.free(l1);
  for(auto it = pool.cbegin(l1); it !=  pool.cend(l1); ++it )
      std::cout << *it << " ";
  std::cout << std::endl;
  l1 = pool.free(l1);
  for(auto it = pool.cbegin(l1); it !=  pool.cend(l1); ++it )
      std::cout << *it << " ";
  std::cout << std::endl;
  l1 = pool.free(l1);
  for(auto it = pool.cbegin(l1); it !=  pool.cend(l1); ++it )
      std::cout << *it << " ";
  std::cout << std::endl;
  l1 = pool.free(l1);
  for(auto it = pool.cbegin(l1); it !=  pool.cend(l1); ++it )
      std::cout << *it << " ";
  std::cout << std::endl;
  l1 = pool.free(l1);
  for(auto it = pool.cbegin(l1); it !=  pool.cend(l1); ++it )
      std::cout << *it << " ";
  std::cout << std::endl;
  l1 = pool.free(l1);
  for(auto it = pool.cbegin(l1); it !=  pool.cend(l1); ++it )
      std::cout << *it << std::endl;
  l1 = pool.free(l1);
  for(auto it = pool.cbegin(l1); it !=  pool.cend(l1); ++it )
      std::cout << *it << " ";
  std::cout << std::endl;
  l1 = pool.free(l1);
  for(auto it = pool.cbegin(l1); it !=  pool.cend(l1); ++it )
      std::cout << *it << " ";
  std::cout << std::endl;
  l1 = pool.free(l1);
  for(auto it = pool.cbegin(l1); it !=  pool.cend(l1); ++it )
      std::cout << *it << " ";
  std::cout << std::endl;
  std::cout << "==============================="   << std::endl;
  std::cout << "Check find, cbegin, cend, push front:" << std::endl;
  std::cout << "Start from the following list:" << std::endl;
  l1 = pool.push_front(3, l1);
  l1 = pool.push_front(2, l1);
  l1 = pool.push_front(1, l1);
  for(auto it = pool.cbegin(l1); it !=  pool.cend(l1); ++it )
    std::cout << *it << " ";
  std::cout << std::endl;
  std::cout << "Let's see if find std::find(pool.cbegin(l1), pool.cend(l1), 2) is different from the cend" << std::endl;
  auto N = std::find(pool.cbegin(l1), pool.cend(l1), 2);
  if(N!=pool.cend(l1)) std::cout << "This is not the cend, my only friend"<< std::endl;
  std::cout << "=============================" << std::endl;
  std::cout << "Check two lists in a pool:" << std::endl;
  std::cout << "pool has a list l1 with the following elements" << std::endl;
  for(auto it = pool.cbegin(l1) ; it != pool.cend(l1); ++it )
    std::cout << *it << " " ;
  std::cout<< std::endl;
  std::cout << "We define a new list l2 in pool and push back 10 elements" << std::endl;
  auto l2 = pool.new_list();
  l2 = pool.push_front(10, l2);
  l2 = pool.push_front(9, l2);
  l2 = pool.push_front(8, l2);
  l2 = pool.push_front(7, l2);
  l2 = pool.push_front(6, l2);
  l2 = pool.push_front(5, l2);
  l2 = pool.push_front(4, l2);
  l2 = pool.push_front(3, l2);
  l2 = pool.push_front(2, l2);
  l2 = pool.push_front(1, l2);
  for(auto it = pool.cbegin(l2) ; it != pool.cend(l2); ++it )
    std::cout << *it << " " ;
  std::cout<< std::endl;
  std::cout << "We free one element from l1 and one element from l2" << std::endl;
  l1=pool.free(l1);
  l2=pool.free(l2);
  std::cout << "We get:" << std::endl;
  for(auto it = pool.cbegin(l1) ; it != pool.cend(l1); ++it )
    std::cout << *it << " " ;
  std::cout<< std::endl;
  for(auto it = pool.cbegin(l2) ; it != pool.cend(l2); ++it )
    std::cout << *it << " " ;
  std::cout<< std::endl;
  std::cout << "=============================" << std::endl;
  std::cout << "Check begin, end:" << std::endl;
  std::cout << "Let's start with:" << std::endl;
  for(auto it = pool.cbegin(l2); it != pool.cend(l2); ++it)
    std::cout << *it << " " ;
  std::cout << std::endl;
 std::cout << "Increment all elements by one " << std::endl;
  for(auto it = pool.begin(l2); it != pool.end(l2); ++it)
      ++*it ;
  std::cout << "We get:" << std::endl;
  for(auto it = pool.cbegin(l2); it != pool.cend(l2); ++it)
    std::cout << *it << " " ;
  std::cout << std::endl;
  std::cout << "=============================" << std::endl;
  std::cout << "Check begin, end in const / non const functions: (need to use the list_pool ``instrumented iterators'')" << std::endl;
  boo(pool, l2);
  boo_const(pool, l2);
  std::cout << "=============================" << std::endl;
  std::cout << "Check reserve and capacity 1" << std::endl;
  list_pool<int> pool_cap_1{22};
  std::cout << "capacity (= 22)? "<< pool_cap_1.capacity() << std::endl;
  auto lcap1 = pool_cap_1.new_list();
  std::cout << "size (= 0)? " << pool_cap_1.list_size(lcap1)<< std::endl;
  std::cout << "capacity (= 22)? "<< pool_cap_1.capacity() << std::endl;
  pool_cap_1.reserve(4);
  std::cout << "size (= 0)? " << pool_cap_1.list_size(lcap1)<< std::endl;
  std::cout << "capacity (= 22)? "<< pool_cap_1.capacity() << std::endl;
  std::cout << "Check reserve and capacity 2" << std::endl;
  list_pool<int> pool_cap_2{1};
  std::cout << "capacity (= 1)? "<< pool_cap_2.capacity() << std::endl;
  auto lcap2 = pool_cap_2.new_list();
  std::cout << "size (= 0)? " << pool_cap_1.list_size(lcap2)<< std::endl;
  std::cout << "capacity (= 8)? "<< pool_cap_2.capacity() << std::endl;
  pool_cap_2.reserve(23);
  std::cout << "size (= 0)? " << pool_cap_1.list_size(lcap2) << std::endl;
  std::cout << "capacity (= 23)? "<< pool_cap_2.capacity() << std::endl;
  std::cout << "=============================" << std::endl;
  std::cout << "Check constructors (need to use the list_pool ``instrumented constructors'')" << std::endl;
  std::cout << "Two list_pool default constructor?" << std::endl;
  list_pool<foo> pool_A{};
  list_pool<foo> pool_B{};
  std::cout << "Defining two new_list and push_front 5 elements in the first and 2 elements in the second:" << std::endl;
  auto lA = pool_A.new_list();
  auto lB = pool_A.new_list();  
  lA = pool_A.push_front(foo{"5"}, lA);
  lA = pool_A.push_front(foo{"4"}, lA);
  lA = pool_A.push_front(foo{"3"}, lA);
  lA = pool_A.push_front(foo{"2"}, lA);
  lA = pool_A.push_front(foo{"1"}, lA);
  lB = pool_A.push_front(foo{"101"}, lB);
  lB = pool_A.push_front(foo{"100"}, lB);
  std::cout << "list_pool copy constructor?" << std::endl;
  list_pool<foo> pool_copy{pool_A};
  std::cout << "list_pool copy assignment?" << std::endl;
  pool_B=pool_copy;
  std::cout << "list_pool move constructor?" << std::endl;
  {
    list_pool<foo> pool_move{std::move(pool_B)};
    std::cout << "Preparing for move assignment.." << std::endl;
    lA=pool_A.free_list(lA);
    lA=pool_A.push_back(foo{"11"},lA);
    std::cout << "list_pool move assignment?" << std::endl;
    pool_move=std::move(pool_A);
    std::cout << "list_pool default destructor?" << std::endl;
  }
  
  std::cout << "=============================" << std::endl;
  std::cout << "List with foo" << std::endl;
  list_pool<foo> pool_foo;
  auto lf = pool_foo.new_list();
  
  foo msg1{"I've just had my third dose of vaccine."};
  foo msg2{"What I write is..."};
  foo msg3{"unpredictable."};
  std::cout <<"Do you see 3 foo copy constructor? " << std::endl;
  lf=pool_foo.push_back(msg1,lf);
  lf=pool_foo.push_back(msg2,lf);
  lf=pool_foo.push_back(msg3,lf);
  std::cout <<"size (=3)? "<<  pool_foo.list_size(lf) << std::endl;
  for(auto it = pool_foo.cbegin(lf); it !=  pool_foo.cend(lf); ++it )
    std::cout << it->msg << " ";
  std::cout << std::endl;
  lf=pool_foo.free_list(lf);
  std::cout <<"Do you see 3 foo move assignment? "<< std::endl;
  lf=pool_foo.push_back(foo{"1"},lf);
  lf=pool_foo.push_back(foo{"2"},lf);
  lf=pool_foo.push_back(foo{"3"},lf);
  std::cout <<"size (=3)? "<<  pool_foo.list_size(lf) << std::endl;
  std::cout <<"Do you see 1 foo move constructor? " << std::endl;
  lf=pool_foo.push_back(foo{"4"},lf);
  std::cout <<"size (=4)? "<<  pool_foo.list_size(lf) << std::endl;
  std::cout << "=============================" << std::endl;
  std::cout << "Copy vs Move:" << std::endl;
  list_pool<foo> new_pool;
  auto lcp = new_pool.new_list();
  std::cout << "Pushing 5 foo elements with messages A,B,C,D,E" << std::endl;
  lcp=new_pool.push_front(foo{"E"},lcp);
  lcp=new_pool.push_front(foo{"D"},lcp);
  lcp=new_pool.push_front(foo{"C"},lcp);
  lcp=new_pool.push_front(foo{"B"},lcp);
  lcp=new_pool.push_front(foo{"A"},lcp);
  std::cout << "Here we default construct two list_pool<foo>" << std::endl;
  list_pool<foo> pool_ma;
  list_pool<foo> pool_ca;
  std::cout << "Here we copy:" << std::endl;
  list_pool<foo> pool_c{new_pool};
  for(auto it = new_pool.cbegin(lcp); it != new_pool.cend(lcp); ++it)
    std::cout << *it << " ";
  std::cout << std::endl;
  for(auto it = pool_c.cbegin(lcp); it != pool_c.cend(lcp); ++it)
    std::cout << *it << " ";
  std::cout << std::endl;
  std::cout << "Here we move:" << std::endl;
  list_pool<foo> pool_m{std::move(new_pool)};
  for(auto it = pool_m.cbegin(lcp); it != pool_m.cend(lcp); ++it)
    std::cout << *it << " ";
  std::cout << std::endl;
  std::cout << "Here we copy assign:" << std::endl;
  pool_ca = pool_m;
  for(auto it = pool_m.cbegin(lcp); it != pool_m.cend(lcp); ++it)
    std::cout << *it << " ";
  std::cout << std::endl;
  for(auto it = pool_ca.cbegin(lcp); it != pool_ca.cend(lcp); ++it)
    std::cout << *it << " ";
  std::cout << std::endl;
  std::cout << "Here we move assign:" << std::endl;
  pool_ma = std::move(pool_m);
  for(auto it = pool_ma.cbegin(lcp); it != pool_ma.cend(lcp); ++it)
    std::cout << *it << " ";
  std::cout << std::endl;
  std::cout << "=============================" << std::endl;
  std::cout << "Pool list vs vector (rvalue reference):" << std::endl;
  {
    list_pool<foo> pool_vec;
    auto lv = new_pool.new_list();
    std::cout << "---" << std::endl;
    lv=pool_vec.push_front(foo{"bye"}, lv);
    std::cout << "---" << std::endl;
    lv=pool_vec.push_front(foo{"hi"}, lv);
    std::cout << "---" << std::endl;
    lv=pool_vec.free(lv);
    std::cout << "---" << std::endl;
    lv=pool_vec.push_front(foo{"hi"}, lv);
    std::cout << "---" << std::endl;
  }
  std::cout << "--------------------" << std::endl;
  {
    std::list<foo> vec;
    std::cout << "---" << std::endl;
    vec.push_back(foo{"hi"});
    std::cout << "---" << std::endl;
    vec.push_back(foo{"bye"});
    std::cout << "---" << std::endl;
    vec.pop_back();
    std::cout << "---" << std::endl;
    vec.push_back(foo{"bye"});
    std::cout << "---" << std::endl;
  }
  std::cout << "--------------------" << std::endl;
  {
    std::vector<foo> vec;
    std::cout << "---" << std::endl;
    vec.emplace_back("hi");
    std::cout << "---" << std::endl;
    vec.emplace_back("bye");
    std::cout << "---" << std::endl;
    vec.pop_back();
    std::cout << "---" << std::endl;
    vec.emplace_back("bye");
    std::cout << "---" << std::endl;
  }
  std::cout << "=============================" << std::endl;
  std::cout << "Pool list vs vector (lvalue reference):" << std::endl;
  foo first{"bye"};
  foo second{"hi"};
  {
    list_pool<foo> pool_vec;
    auto lv = new_pool.new_list();
    std::cout << "---" << std::endl;
    lv=pool_vec.push_front(first, lv);
    std::cout << "---" << std::endl;
    lv=pool_vec.push_front(second, lv);
    std::cout << "---" << std::endl;
    lv=pool_vec.free(lv);
    std::cout << "---" << std::endl;
    lv=pool_vec.push_front(second, lv);
    std::cout << "---" << std::endl;
  }
  std::cout << "--------------------" << std::endl;
  {
    std::list<foo> vec;
    std::cout << "---" << std::endl;
    vec.push_back(second);
    std::cout << "---" << std::endl;
    vec.push_back(first);
    std::cout << "---" << std::endl;
    vec.pop_back();
    std::cout << "---" << std::endl;
    vec.push_back(first);
    std::cout << "---" << std::endl;
  }
  std::cout << "--------------------" << std::endl;
  {
    std::vector<foo> vec;
    std::cout << "---" << std::endl;
    vec.emplace_back(second);
    std::cout << "---" << std::endl;
    vec.emplace_back(first);
    std::cout << "---" << std::endl;
    vec.pop_back();
    std::cout << "---" << std::endl;
    vec.emplace_back(first);
    std::cout << "---" << std::endl;
  }
  std::cout << "=============================" << std::endl;
  std::cout << "Let's see how fast we are!" << std::endl;
  std::cout << "How many cycles? Use large number for standard version (e.g. 10000000), small for instrumented (e.g. 10)" << std::endl;
  int iterations;	       
  std::cin >> iterations;
  auto ta0 = std::chrono::high_resolution_clock::now();
  {
    std::vector<int> fl_1;
    std::vector<int> fl_2;
    for(auto i = 0; i < iterations; ++i)
      {
	fl_1.push_back(i);
	fl_2.push_back(i);
      }
    fl_1.clear();
    fl_2.clear();
    for(auto i = 0; i < iterations; ++i)
      {
	fl_1.push_back(i);
	fl_2.push_back(i);
      }
  }
  auto ta1 = std::chrono::high_resolution_clock::now();
  auto ta = std::chrono::duration_cast<std::chrono::milliseconds>(ta1 - ta0);
  std::cout << ta.count() << std::endl;
  std::cout << "--------------------" << std::endl;
  auto tb0 = std::chrono::high_resolution_clock::now();
  {
    list_pool<int, int> speed_test;
    auto st_1 = speed_test.new_list();
    auto st_2 = speed_test.new_list();
    for(auto i = 0; i < iterations; ++i)
      {
	st_1=speed_test.push_front(i,st_1);
	st_2=speed_test.push_front(i,st_2);
      }
    st_1=speed_test.free_list(st_1);
    st_2=speed_test.free_list(st_2);
    for(auto i = 0; i < iterations; ++i)
      {
	st_1=speed_test.push_front(i,st_1);
	st_2=speed_test.push_front(i,st_2);
      }
  }
  auto tb1 = std::chrono::high_resolution_clock::now();
  auto tb = std::chrono::duration_cast<std::chrono::milliseconds>(tb1 - tb0);
  std::cout << tb.count() << std::endl;
  std::cout << "Well, not so good..." << std::endl;
  std::cout << "=============================" << std::endl;
  std::cout << "Throw check:" << std::endl;
  std::cout << "This shall NOT throw error:" << std::endl;
  std::cout << *(pool_foo.cbegin(lf)) << std::endl; 
  //for(auto it = pool_foo.cbegin(lf); it !=  pool_foo.cend(lf);  )
  //  std::cout << (it++)->msg << " "<< std::endl;
  std::cout << std::endl;
  std::cout << "--------------------" << std::endl;
  std::cout << "This shall throw error:" << std::endl;
  //try { // I have memory leak when I run leaks -atExit -- ./main.x, so I comment out the catches. But it is a problem of leaks -atExit -- I suppose
  std::cout << *(pool_foo.cend(lf)) << std::endl; 
  //}
  //catch (const std::out_of_range& oor) {
  //std::cerr << "Out of Range error: " << oor.what() << '\n';
  //}
  //for(auto it = pool_foo.cbegin(lf); it !=  pool_foo.cend(lf);  )
  //  std::cout << (++it)->msg << " " << std::endl;
  /*
    try {
    std::cout << *(pool_foo.cend(lf)) << std::endl;
    }
    catch (const out_of_range& s) {
    std::cerr << s.message << std::endl;
    return 1;
    } 
  */
  std::cout << std::endl;
  
  return 0;
}
