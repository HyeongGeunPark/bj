/*
bj18221

접근: 시뮬레이션
문제에서 요구하는 대로 그냥 만들면 된다.

N:지도의 크기:[7,1000]

* prefix sum을 사용할 수는 있지만, 시간적 이득은 별로 없다.
*/

#include <iostream>
#include <vector>
#include <cmath>

int main(void){
  // c++ fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);

  // input
  int n;
  std::cin>>n;

  std::vector<std::vector<int>> map(n, std::vector<int>(n));

  std::pair<int,int> sung_gyu, professor;

  for(int i=0;i<n;++i){
    for(int j=0;j<n;++j){
      std::cin>>map[i][j];
      if(map[i][j] == 2){
        sung_gyu.first = i;
        sung_gyu.second = j;
      }
      else if(map[i][j] == 5){
        professor.first = i;
        professor.second = j;
      }
    }
  }

  // distance condition
  if((std::pow(sung_gyu.first - professor.first, 2)
    + std::pow(sung_gyu.second - professor.second, 2)) < 25)
  {
    std::cout << 0;
    return 0;
  }


  // other students condition
  int other_students = 0;

  if(sung_gyu.first > professor.first){
    std::swap(sung_gyu.first, professor.first);
  }
  if(sung_gyu.second > professor.second){
    std::swap(sung_gyu.second, professor.second);
  }

  for(int i=sung_gyu.first; i<=professor.first; ++i){
    for(int j=sung_gyu.second; j<=professor.second; ++j){
      if(map[i][j] == 1){
        ++other_students;
      }
    }
  }

  std::cout << (other_students >= 3 ? 1 : 0);
  return 0;
}
