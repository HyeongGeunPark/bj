/*

bj17387 ���� ���� 2

2���� ��ǥ��� ���� �� ������ �Է¹޾� �� ������ �����ϴ��� Ȯ���Ѵ�.
�� ������ �� ���� �ٸ� �����̳� �� �� ���� �ִ� �͵� �����ϴ� ���̴�.

���ٹ�: CCW �˰���
      v3
      |
      | 
v1-----------v2
      |
      v4
1. ccw �˰����� �̿��� v1, v2, v3�� v1, v2, v4�� ���⼺�� Ȯ���Ѵ�. (�ð�, ������, �ݽð�)
2. ���������� v3, v4, v1�� v3, v4, v2�� ���⼺�� Ȯ���Ѵ�.
3. ��츦 ������.
    i) 1���� ���� �� ���⼺�� ���� ���� && 2���� ���� �� ���⼺�� ���� ���� -> ������
    ii) ���⼺ �� �� �ϳ��� 0, �ٸ� �ϳ��� ���� -> ������(�� ������ ���� �ٸ� ���� ���� ����)
    iii) ���⼺ �� �� �� ��� 0 -> �� ���� �� ���� ���� ����, Ȥ�� �� ������ ������ �� �ϳ��� ��ġġ
        -> �� ���п��� �� ���� ���� ���� ��ġ ���谡 ��� �Ǵ��� �ľ��Ѵ�.
        v1, v2�� ����, v3, v4�� �����Ѵ�.
           v1--------v2
              v3 <----
            ----> v4
            ���� ���� �Ǿ�� �����Ѵ�. (v3<=v2 && v1<=v4);

*/

#include<iostream>
using ll = long long;

struct vec2 {
    ll x, y;
};

vec2 operator-(const vec2 a, const vec2 b) {
    return vec2{ a.x - b.x, a.y - b.y };
}

bool operator>(const vec2 a, const vec2 b) {
    if (a.x > b.x) return true;
    else if (a.x == b.x) return a.y > b.y;
    else return false;
}

bool operator==(const vec2 a, const vec2 b) {
    return a.x == b.x && a.y == b.y;
}

bool operator<=(const vec2 a, const vec2 b) {
    return !(a > b);
}

ll cross(vec2 a, vec2 b) {
    ll result = a.x * b.y - a.y * b.x;
    return result;
}

ll dot(vec2 a, vec2 b) {
    ll result = a.x * b.x + a.y * b.y;
    return result;
}

int ccw(vec2 a, vec2 b, vec2 c) {
    ll x = cross(b - a, c - b);
    if (x > 0) return 1;
    else if (x == 0) return 0;
    else return -1;
}

int intersect(vec2 v1, vec2 v2, vec2 v3, vec2 v4) {
    int ccwp1 = ccw(v1, v2, v3) * ccw(v1, v2, v4);
    int ccwp2 = ccw(v3, v4, v1) * ccw(v3, v4, v2);

    if (ccwp1 == 0 && ccwp2 == 0) {
        if (v1 > v2) std::swap(v1, v2);
        if (v3 > v4) std::swap(v3, v4);
        if (v3 <= v2 && v1 <= v4) return 1;
        else return 0;
    }
    else if (ccwp1 <= 0 && ccwp2 <= 0) {
        return 1;
    }
    else return 0;
}



int main(void) {

    vec2 v[5];
    
    for (int i = 1; i <= 4; ++i) {
        std::cin >> v[i].x;
        std::cin >> v[i].y;
    }


    std::cout << intersect(v[1], v[2], v[3], v[4]); 
}