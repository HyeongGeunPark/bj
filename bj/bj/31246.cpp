/*
bj31246 모바일 광고 입찰

광고 지면 수 : n
각 광고 지면 i에 대해 MOLOCO가 제시한 입찰 가격 Ai와 다른 입찰가 중 최고가 Bi가 주어진다.

MOLOCO가 모든 입찰가를 일괄적으로 X만큼 올렸을 떄,
K 이상의 지면을 낙찰받게 되는 가장 작은 음이 아닌 정수 X를 찾고자 한다.

단 같은 지면에 대해 MOLOCO의 입찰가와 다른 회사의 입찰가가 같을 경우
MOLOCO가 낙찰받는 것으로 한다.

1<=n<=100'000
1<=k<=n
1<=Ai,Bi<=1'000'000'000

접근: 정렬

1. Bi - Ai를 계산하여 정렬한다.
2. k번째 element가 무엇인지 확인한다.
3. 그 element의 값만큼 모든 입찰가를 일괄적으로 올리면, 최소 k개의 광고는 낙찰받을 수 있게 된다.
4. (예외)k번째 element가 0보다 작은 경우는 가격을 올릴 필요가 없으므로 0이 답이 된다.


*/

#include <iostream>
#include <vector>
#include <algorithm>

int main(void) {
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);

  int n, k;
  std::cin >> n >> k;

  std::vector<int> price_diff(n);

  for(int i=0;i<n;++i){
    int a,b;
    std::cin >> a >> b;
    price_diff[i] = b-a;
  }

  std::sort(price_diff.begin(),price_diff.end());

  if(price_diff[k-1]<=0){
    std::cout << 0;
  }else{
    std::cout << price_diff[k-1];
  }
  return 0;
}
