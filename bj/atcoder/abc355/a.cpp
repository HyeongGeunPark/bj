#include<iostream>

int main(void){
  int a, b;
  std::cin>>a>>b;
  if(a==b){
    std::cout<<-1;
  }
  else{
    std::cout<<(6-a-b);
  }
}