/*

bj9328 열쇠

주어진 지도에서 최대한 훔칠 수 있는 문서의 수를 구하기.

접근: 구현


*/

#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#define cpp_fast_io() \
  std::cin.tie(0);    \
  std::ios_base::sync_with_stdio(false)

struct vec2 {
  int x, y;
};

const vec2 adjacents[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

vec2 operator+(const vec2 a, const vec2 b) {
  return vec2{a.x + b.x, a.y + b.y};
}

class finder {
 public:
  finder(std::vector<std::vector<char>>& map, std::set<char> keys)
      : map{map},
        search_stack{},
        locked_door{},
        document_num{0},
        keys{keys},
        w{static_cast<int>(map.size())},
        h{static_cast<int>(map[0].size())},
        visited(w, std::vector<bool>(h, false)) {}
  int search() {
    // init
    for (int i = 0; i < w; ++i) {
      search_stack.push_back(vec2{i, 0});
      search_stack.push_back(vec2{i, h - 1});
    }
    for (int j = 1; j < h - 1; ++j) {
      search_stack.push_back(vec2{0, j});
      search_stack.push_back(vec2{w - 1, j});
    }

    while (search_stack.size()) _search();

    return document_num;
  }
  bool is_in_map(vec2 v) { return 0 <= v.x && v.x < w && 0 <= v.y && v.y < h; }
  bool is_visited(vec2 v) { return visited[v.x][v.y]; }
  void set_visited(vec2 v) { visited[v.x][v.y] = true; }
  char get_map_component(vec2 v) { return map[v.x][v.y]; }

 private:
  std::vector<std::vector<char>>& map;
  const int w, h;
  std::vector<std::vector<bool>> visited;
  std::vector<vec2> search_stack;
  std::multimap<char, vec2> locked_door;
  std::set<char> keys;
  int document_num;
  void _search() {
    if (search_stack.empty()) return;
    vec2 v = search_stack.back();
    search_stack.pop_back();
    if (is_visited(v)) return;
    char map_component = get_map_component(v);
    if (is_key(map_component)) {
      keys.insert(map_component);
      auto [b, e] = locked_door.equal_range(map_component);
      for (auto i = b; i != e; ++i) {
        search_stack.push_back(i->second);
      }
      locked_door.erase(b, e);
    } else if (char c; c = is_door(map_component)) {
      if (!keys.contains(c)) {
        locked_door.insert({c, v});
        return;
      }
    } else if (map_component == '$') {
      ++document_num;
    }

    set_visited(v);

    if (map_component == '*') return;

    // empty space, find adjacent space in map
    for (int i = 0; i < 4; ++i) {
      vec2 next = v + adjacents[i];
      if (!is_in_map(next)) continue;
      search_stack.push_back(next);
    }
  }
  char is_key(char c) {
    if ('a' <= c && c <= 'z')
      return c;
    else
      return 0;
  }
  char is_door(char c) {
    if ('A' <= c && c <= 'Z')
      return std::tolower(c);
    else
      return 0;
  }
};

std::vector<std::vector<char>> map_read(std::istream& is) {
  int w, h;
  is >> w >> h;
  std::vector<std::vector<char>> map(w, std::vector<char>(h));

  auto ff = is.flags();
  is >> std::skipws;
  for (int i = 0; i < w; ++i) {
    for (int j = 0; j < h; ++j) {
      is >> map[i][j];
    }
  }
  is.flags(ff);
  return map;  // move semantic is applied for stl containers
}

std::set<char> key_read(std::istream& is) {
  std::string keys;
  std::getline(is >> std::ws, keys);
  return std::set<char>{keys.begin(), keys.end()};
}

int main(void) {
  cpp_fast_io();

  int test_case;
  std::cin >> test_case;

  for (int i = 0; i < test_case; ++i) {
    auto map = map_read(std::cin);
    finder f{map, key_read(std::cin)};
    std::cout << f.search() << '\n';
  }
}
