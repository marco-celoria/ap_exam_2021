#include "list_pool.hpp"
#include <cassert>
#include <algorithm>

class foo
{
  friend std::ostream &operator<<(std::ostream &os, const foo &item) {
    os << item.msg;
    return os;
  }
  
public:
  foo() = default;
  foo(const std::string & message) : msg{message} {}
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
  
  auto M = std::max_element(pool.begin(l1), pool.end(l1));
  assert(*M == 11);

  auto m = std::min_element(pool.cbegin(l1), pool.cend(l1));
  assert(*m == 1);
  for(auto it =pool.begin(l1); it !=  pool.end(l1); ++it )
    {
      std::cout << "*it= " << *it << std::endl;
      ++cnt;
    }
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
  if(N!=pool.cend(l1)) std::cout << "This is not the end, my friend: " << *N << std::endl;
  std::cout << std::endl;
  std::cout << "=============================" << std::endl;
  
  list_pool<int> pool2{22};
  
  auto l2 = pool2.new_list();
  std::cout << "l2: ";
  std::cout << "free list: ";
  std::cout << "all elements list: \n";
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
  std::cout << "--------------------" << std::endl;
  l2=pool2.free_list(l2);
  
  std::cout << "!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
  
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
  std::cout << "1---------------" << std::endl;
  l3 = pool3.free(l3);
  std::cout << "2---------------" << std::endl;
  l3 = pool3.free(l3);
  std::cout << "3---------------" << std::endl;
  l3 = pool3.free(l3);
  std::cout << "4---------------" << std::endl;
  l3 = pool3.free(l3);
  std::cout << "5---------------" << std::endl;
  l3 = pool3.free(l3);
  std::cout << "6---------------" << std::endl;
  l3 = pool3.free(l3);
  std::cout << "7---------------" << std::endl;
  l3 = pool3.free(l3);
  std::cout << "8---------------" << std::endl;
  l3 = pool3.free(l3);
  std::cout << "9---------------" << std::endl;
  l3 = pool3.free(l3);
  std::cout << "10---------------" << std::endl;
  l3 = pool3.free(l3);
  std::cout << "11---------------" << std::endl;
  l3 = pool3.free(l3);
  std::cout << "12---------------" << std::endl;
  l3 = pool3.free(l3);
  std::cout << "13---------------" << std::endl;
  l3 = pool.free(l3);
  std::cout << "--------------------" << std::endl;  
  std::cout << "++++++++++++++++" << std::endl;
  l3 = pool3.push_front(1, l3);
  std::cout << "++++++++++++++++" << std::endl;
  l3 = pool3.push_back(2, l3);
  std::cout << "=============================" << std::endl;
  
  list_pool<int> pool4{22};
  auto l4 = pool4.new_list();
  l4=pool4.free_list(l4);
  std::cout << "--------------------" << std::endl;
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
  
  list_pool<int> pool10{};
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

  std::cout << "copy" << std::endl;
  list_pool<int> pool_copy{pool10};
  
  std::cout << "assignment" << std::endl;
  pool_copy=pool4;
  
  std::cout << "move" << std::endl;
  list_pool<int> pool_move{std::move(pool10)};
  std::cout << "move assignment" << std::endl;
  l4=pool4.free_list(l4);
  l4=pool4.push_back(8,l4);
  pool_move=std::move(pool4);

  std::cout << "reserve" << std::endl;
  list_pool<foo> pool_reserve{5};
  std::cout <<"capacity="<< pool_reserve.capacity() << std::endl;
  auto lres = pool_reserve.new_list();
  std::cout <<"capacity="<< pool_reserve.capacity() << std::endl;
  foo msg1{"I've just had my third dose of vaccine."};
  foo msg2{"What I write is..."};
  foo msg3{"unpredictable."};
  lres=pool_reserve.push_back(msg1,lres);
  lres=pool_reserve.push_back(msg2,lres);
  lres=pool_reserve.push_back(msg3,lres);
  std::cout <<"size="<<  pool_reserve.list_size(lres) << std::endl;
  for(auto it = pool_reserve.begin(lres); it !=  pool_reserve.end(lres); ++it )
    {
      std::cout << it->msg << " ";
    }
  std::cout << std::endl;
  lres=pool_reserve.free_list(lres);
  lres=pool_reserve.push_back(foo{"1"},lres);
  lres=pool_reserve.push_back(foo{"2"},lres);
  lres=pool_reserve.push_back(foo{"3"},lres);
  lres=pool_reserve.push_back(foo{"4"},lres);
  std::cout <<"size="<<  pool_reserve.list_size(lres) << std::endl;
  std::cout << "Throw check:" << std::endl;
  std::cout << "This shall NOT throw error:" << std::endl;
  for(auto it = pool_reserve.begin(lres); it !=  pool_reserve.end(lres);  )
    {
      std::cout << (it++)->msg << " "<< std::endl;
    }
  std::cout << std::endl;
  std::cout << "This shall throw error:" << std::endl;
  std::cout <<"*end="<< *(pool_reserve.end(lres)) << std::endl;
  // for(auto it = pool_reserve.begin(lres); it !=  pool_reserve.end(lres);  )
  //  {
  //    std::cout << (++it)->msg << " "<< std::endl;
  //  }
  std::cout << std::endl;
  return 0;
}
