#include "list_pool.hpp"
#include <cassert>
#include <algorithm>
#include<vector>
template <typename T,typename S > void boo_const (const list_pool<T> & x, S l)
{
  auto it = x.begin(l);
  std::cout << "const front element = " << *it << std::endl;
  //*it= 77;
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
  
  list_pool<int> pool{};
  auto l1 = pool.new_list();
  long unsigned int cnt = 0;
  for(auto it = pool.begin(l1); it !=  pool.end(l1); ++it )
    {
      std::cout << "*it= " << *it << std::endl;
      ++cnt;
    }
  if(pool.list_size(l1)==cnt) std::cout << "OK the list is empty as expected" << std::endl;
  cnt = 0;
  std::cout << "{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}"   << std::endl;
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
  for(auto it =pool.begin(l1); it !=  pool.end(l1); ++it )
    {
      std::cout << "*it= " << *it << std::endl;
      ++cnt;
    }
  auto M = std::max_element(pool.begin(l1), pool.end(l1));
  std::cout << "*M=" << *M << std::endl;
  assert(*M == 11);
  
  auto m = std::min_element(pool.cbegin(l1), pool.cend(l1));
  assert(*m == 1);
  
  l1=pool.free_list(l1);  
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
  
  std::cout << "++++++++++++++++" << std::endl;
  l1 = pool.free(l1);
  l1 = pool.free(l1);
  l1 = pool.free(l1);
  l1 = pool.free(l1);
  l1 = pool.free(l1);
  l1 = pool.free(l1);
  l1 = pool.free(l1);
  l1 = pool.free(l1);
  l1 = pool.free(l1);
  l1 = pool.free(l1);
  l1 = pool.free(l1);
  l1 = pool.free(l1);
  l1 = pool.free(l1);
  std::cout << "++++++++++++++++" << std::endl;
  l1 = pool.push_front(3, l1);
  l1 = pool.push_front(2, l1);
  l1 = pool.push_front(1, l1);
  for(auto it = pool.begin(l1); it !=  pool.end(l1); ++it )
    std::cout << *it << " ";
  std::cout << std::endl;
  auto N = std::find(pool.cbegin(l1), pool.cend(l1), 2);
  if(N!=pool.cend(l1)) std::cout << "This is not the end, my only friend: " << *N ;
  std::cout << std::endl;
  std::cout << "=============================" << std::endl;
  list_pool<int> pool2{22};
  auto l2 = pool2.new_list();
  l2 = pool2.push_front(11, l2);
  l2 = pool2.push_front(10, l2);
  l2 = pool2.push_front(9, l2);
  l2 = pool2.push_front(8, l2);
  l2 = pool2.push_front(7, l2);
  l2 = pool2.push_front(6, l2);
  l2 = pool2.push_front(5, l2);
  l2 = pool2.push_front(4, l2);
  l2 = pool2.push_front(3, l2);
  l2 = pool2.push_front(2, l2);
  l2 = pool2.push_front(1, l2);
  for(auto it = pool2.cbegin(l2) ; it != pool2.cend(l2); ++it )
    std::cout << *it << " " ;
  std::cout<< std::endl;
  l2=pool2.free_list(l2);
  for(auto it = pool2.cbegin(l2) ; it != pool2.cend(l2); ++it )
    std::cout << *it << " " ;
  std::cout<< std::endl;
  list_pool<int> pool3{};
  auto l3 = pool3.new_list();
  l3 = pool3.push_back(1, l3);
  l3 = pool3.push_back(2, l3);
  l3 = pool3.push_back(3, l3);
  l3 = pool3.push_back(4, l3);
  l3 = pool3.push_back(5, l3);
  l3 = pool3.push_back(6, l3);
  l3 = pool3.push_back(7, l3);
  l3 = pool3.push_back(8, l3);
  l3 = pool3.push_back(9, l3);
  l3 = pool3.push_back(10, l3);
  l3 = pool3.push_back(11, l3);
  std::cout << "++++++++++++++++" << std::endl;
  l3 = pool3.free(l3);
  l3 = pool3.free(l3);
  l3 = pool3.free(l3);
  l3 = pool3.free(l3);
  l3 = pool3.free(l3);
  l3 = pool3.free(l3);
  l3 = pool3.free(l3);
  l3 = pool3.free(l3);
  l3 = pool3.free(l3);
  l3 = pool3.free(l3);
  l3 = pool3.free(l3);
  l3 = pool3.free(l3);
  l3 = pool3.free(l3);
  l3 = pool.free(l3);
  std::cout << "++++++++++++++++" << std::endl;
  l3 = pool3.push_front(1, l3);
  l3 = pool3.push_back(2, l3);
  for(auto it = pool3.begin(l3); it != pool3.end(l3); ++it)
    std::cout << *it << " " ; 
  for(auto it = pool3.begin(l3); it != pool3.end(l3); ++it)
      ++*it ;
  std::cout << std::endl;
  for(auto it = pool3.cbegin(l3); it != pool3.cend(l3); ++it)
    std::cout << *it << " " ;
  std::cout << std::endl;
  std::cout << "=============================" << std::endl;
  boo(pool3, l3);
  boo_const(pool3, l3);
  std::cout << "=============================" << std::endl;
  list_pool<int> pool4{22};
  std::cout << "capacity = "<< pool4.capacity() << std::endl;
  auto l4 = pool4.new_list();
  std::cout << "capacity = "<< pool4.capacity() << std::endl;
  pool4.reserve(4);
  std::cout << "capacity = "<< pool4.capacity() << std::endl;
  l4=pool4.free_list(l4);
  l4 = pool4.push_back(1, l4);
  l4 = pool4.push_back(2, l4);
  l4 = pool4.push_back(3, l4);
  l4 = pool4.push_back(4, l4);
  l4 = pool4.push_back(5, l4);
  l4 = pool4.push_back(6, l4);
  l4 = pool4.push_back(7, l4);
  l4 = pool4.push_back(8, l4);
  l4 = pool4.push_back(9, l4);
  l4 = pool4.push_back(10, l4);
  l4 = pool4.push_back(11, l4);
  std::cout << "--------------------" << std::endl;
  std::cout << "default constructor?" << std::endl;
  list_pool<int> pool10{};
  std::cout << "Making two new_list and push_front 12 times" << std::endl;
  auto l10 = pool10.new_list();
  auto l11 = pool10.new_list();  
  l10 = pool10.push_front(11, l10);
  l10 = pool10.push_front(10, l10);
  l10 = pool10.push_front(9, l10);
  l10 = pool10.push_front(8, l10);
  l10 = pool10.push_front(7, l10);
  l10 = pool10.push_front(6, l10);
  l10 = pool10.push_front(5, l10);
  l10 = pool10.push_front(4, l10);
  l10 = pool10.push_front(3, l10);
  l10 = pool10.push_front(2, l10);
  l10 = pool10.push_front(1, l10);
  l11 = pool10.push_front(100, l11);
  std::cout << "copy constructor?" << std::endl;
  list_pool<int> pool_copy{pool10};
  std::cout << "copy assignment?" << std::endl;
  pool_copy=pool4;
  std::cout << "move constructor?" << std::endl;
  {
    list_pool<int> pool_move{std::move(pool10)};
    std::cout << "Preparing for move assignment" << std::endl;
    l4=pool4.free_list(l4);
    l4=pool4.push_back(8,l4);
    std::cout << "move assignment?" << std::endl;
    pool_move=std::move(pool4);
    std::cout << "default destructor?" << std::endl;
  }
  std::cout << "--------------------" << std::endl;
  std::cout << "reserve = 5 ?" << std::endl;
  list_pool<foo> pool_reserve{5};
  std::cout <<"capacity="<< pool_reserve.capacity() << std::endl;
  auto lres = pool_reserve.new_list();
  std::cout <<"capacity="<< pool_reserve.capacity() << std::endl;
  std::cout << "--------------------" << std::endl;
  foo msg1{"I've just had my third dose of vaccine."};
  foo msg2{"What I write is..."};
  foo msg3{"unpredictable."};
  lres=pool_reserve.push_back(msg1,lres);
  lres=pool_reserve.push_back(msg2,lres);
  lres=pool_reserve.push_back(msg3,lres);
  std::cout <<"size="<<  pool_reserve.list_size(lres) << std::endl;
  for(auto it = pool_reserve.cbegin(lres); it !=  pool_reserve.cend(lres); ++it )
    std::cout << it->msg << " ";
  std::cout << std::endl;
  lres=pool_reserve.free_list(lres);
  lres=pool_reserve.push_back(foo{"1"},lres);
  lres=pool_reserve.push_back(foo{"2"},lres);
  lres=pool_reserve.push_back(foo{"3"},lres);
  lres=pool_reserve.push_back(foo{"4"},lres);
  std::cout <<"size="<<  pool_reserve.list_size(lres) << std::endl;
  std::cout << "--------------------" << std::endl;
  std::cout << "Copy vs Move" << std::endl;
  list_pool<foo> new_pool{5};
  auto lcp = new_pool.new_list();
  std::cout << "Pushing" << std::endl;
  lcp=new_pool.push_front(std::move(foo{"A"}),lcp);
  std::cout << "--" << std::endl; 
  lcp=new_pool.push_front(std::move(foo{"B"}),lcp);
  lcp=new_pool.push_front(std::move(foo{"C"}),lcp);
  lcp=new_pool.push_front(std::move(foo{"D"}),lcp);
  lcp=new_pool.push_front(std::move(foo{"E"}),lcp);
  lcp=new_pool.push_front(std::move(foo{"F"}),lcp);
  lcp=new_pool.push_front(std::move(foo{"G"}),lcp);
  std::cout << "Here we construct:" << std::endl;
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
  std::cout << "====================" << std::endl;
  std::cout << "Pool list vs vector" << std::endl;
  {
    list_pool<foo> pool_vec;
    auto lv = new_pool.new_list();
    lv=pool_vec.push_front(foo{"bye"}, lv);
    lv=pool_vec.push_front(foo{"hi"}, lv);
    lv=pool_vec.free(lv);
    lv=pool_vec.push_front(foo{"hi"}, lv);
  }
  std::cout << "++++++++++" << std::endl;
  {
    std::vector<foo> vec;
    vec.push_back(foo{"hi"});
    vec.push_back(foo{"bye"});
    vec.pop_back();
    vec.push_back(foo{"bye"});
  }
  std::cout << "++++++++++" << std::endl;
  {
    std::vector<foo> vec;
    vec.emplace_back("hi");
    vec.emplace_back("bye");
    vec.pop_back();
    vec.emplace_back(foo{"bye"});
  }
  std::cout << "++++++++++" << std::endl;
  std::cout << "We are as fast as std::vector<T>::push_back, but still slower than std::vector<T>::emplace_back" << std::endl;
  std::cout << "--------------------" << std::endl;
  std::cout << "Throw check:" << std::endl;
  std::cout << "This shall NOT throw error:" << std::endl;
  for(auto it = pool_reserve.begin(lres); it !=  pool_reserve.end(lres);  )
      std::cout << (it++)->msg << " "<< std::endl;
  std::cout << std::endl;
  std::cout << "This shall throw error:" << std::endl;
  //try { // I have leaks when I leaks -atExit -- ./main.x, so I comment out the catches
  std::cout << *(pool_reserve.cend(lres)) << std::endl; 
  //}
  //catch (const std::out_of_range& oor) {
  //std::cerr << "Out of Range error: " << oor.what() << '\n';
  //}
  /*
    for(auto it = pool_reserve.begin(lres); it !=  pool_reserve.end(lres);  )
    {
    std::cout << (++it)->msg << " "<< std::endl;
    }
  */
  /*
    try {
    std::cout << *(pool_reserve.cend(lres)) << std::endl;
    }
    catch (const out_of_range& s) {
    std::cerr << s.message << std::endl;
    return 1;
    } 
  */
  std::cout << std::endl;
  
  return 0;
}
