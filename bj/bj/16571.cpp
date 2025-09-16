/*
bj16571 알파 틱택토

이미 어느 정도 진행된 틱택토 게임 상태를 입력받아서,
지금 둘 차례인 플레이어가 얻을 수 있는 최상의 결과를 출력.

각 플레이어는 이 이후로 최적의 선택을 한다.

이미 게임이 종료된 상태는 입력으로 주어지지 않는다.

접근: 백트래킹

*/

#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <span>
#include <unordered_map>

using game_state = std::array<std::array<uint8_t, 3>, 3>;

struct coord {
  uint8_t x, y;
};

enum class game_result { UNKNOWN = 0, LOSE = 1, DRAW = 2, WIN = 3 };

/**
 * @brief 누구의 차례인지?
 * PLAYER1 == X, PLAYER2 == O
 */
enum class game_turn { UNKNOWN = 0, PLAYER1 = 1, PLAYER2 = 2 };

inline uint8_t game_turn_2_uint8(game_turn turn) {
  if (turn == game_turn::PLAYER1)
    return 1;
  else if (turn == game_turn::PLAYER2)
    return 2;
}

game_turn whose_turn_tictactoe(game_state state) {
  int player_1_count = 0;
  int player_2_count = 0;

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      switch (state[i][j]) {
        case 1:
          ++player_1_count;
          break;
        case 2:
          ++player_2_count;
          break;
        default:
          /* do nothing */
          break;
      }
    }
  }

  /* 항상 X 플레이어 == PLAYER1이 먼저 둔다. */
  if (player_1_count == player_2_count) {
    return game_turn::PLAYER1;
  } else if (player_1_count > player_2_count) {
    return game_turn::PLAYER2;
  } else {
    /* 이와 같은 경우는 없어야 한다. */
    assert(false);
    return game_turn::UNKNOWN;
  }
}

/**
 * @brief 게임이 끝났는지를 체크하는 함수.
 * @param state 현재 게임 상태
 * @param pos 마지막으로 둔 위치
 * @return 게임이 어떻게 끝났는지?
 */
game_result check_if_game_ends(game_state state, coord pos,
                               int empty_spaces_count) {
  // game_result result = game_result::UNKNOWN;

  if (state[pos.x][0] == state[pos.x][1] &&
      state[pos.x][1] == state[pos.x][2]) {
    return game_result::WIN;
  }

  if (state[0][pos.y] == state[1][pos.y] &&
      state[1][pos.y] == state[2][pos.y]) {
    return game_result::WIN;
  }

  if (pos.x == pos.y) {
    if (state[0][0] == state[1][1] && state[1][1] == state[2][2]) {
      return game_result::WIN;
    }
  }

  if (pos.x + pos.y == 2) {
    if (state[2][0] == state[1][1] && state[1][1] == state[0][2]) {
      return game_result::WIN;
    }
  }

  if (empty_spaces_count == 0) {
    return game_result::DRAW;
  } else {
    return game_result::UNKNOWN;
  }
}

struct hash_game_state {
  static_assert(std::is_trivially_copyable_v<game_state>);

  std::size_t operator()(const game_state& key) const noexcept {
    auto bytes = std::as_bytes(std::span{&key, 1});
    auto p = reinterpret_cast<const char*>(bytes.data());
    return std::hash<std::string_view>{}(std::string_view{p, bytes.size()});
  }
};

/**
 * @brief 다음에 둘 플레이어가 얻을 수 있는 최상의 결과를 리턴한다.
 * @param state 현재 게임의 상태이다.
 * @return 최선의 게임 결과
 */
game_result solve_tictactoe(game_state state, game_turn turn) {
  // cache
  // static size_t cache_hit = 0;
  // static size_t cache_miss = 0;

  static std::unordered_map<game_state, game_result, hash_game_state> cache;

  // 누구 차례인지 구한다.
  if (turn == game_turn::UNKNOWN) {
    turn = whose_turn_tictactoe(state);
  }

  // 다음에 둘 수 있는 자리를 구한다.
  std::array<coord, 9> empty_spaces;
  size_t empty_spaces_count = 0;
  for (uint8_t i = 0; i < 3; ++i) {
    for (uint8_t j = 0; j < 3; ++j) {
      if (state[i][j] == 0) {
        empty_spaces[empty_spaces_count] = {i, j};
        ++empty_spaces_count;
      }
    }
  }

  game_result preferable_result = game_result::UNKNOWN;

  // 다음 자리를 두고 재귀 호출한다.
  for (int i = 0; i < empty_spaces_count; ++i) {
    coord& next_pos = empty_spaces[i];
    game_state next_state = state;
    next_state[next_pos.x][next_pos.y] = game_turn_2_uint8(turn);
    game_turn next_turn =
        (turn == game_turn::PLAYER1) ? game_turn::PLAYER2 : game_turn::PLAYER1;

    game_result result;

    if (cache.contains(next_state)) {
      result = cache[next_state];
      //++cache_hit;
    } else {
      //++cache_miss;
      result = check_if_game_ends(next_state, next_pos, empty_spaces_count - 1);

      // 이 자리를 두어서 결과가 나오지 않으면 재귀 호출이 필요하다.
      if (result == game_result::UNKNOWN) {
        game_result next_player_result = solve_tictactoe(next_state, next_turn);

        switch (next_player_result) {
          case game_result::LOSE:
            result = game_result::WIN;
            break;
          case game_result::DRAW:
            result = game_result::DRAW;
            break;
          case game_result::WIN:
            result = game_result::LOSE;
            break;
          case game_result::UNKNOWN:
          default:
            /* never happens */
            assert(false);
            break;
        }
      }
      // cache.insert({ next_state, result });
    }

    // 현재 수를 둘 때 최선의 결과를 구했다.
    // 이를 이용해 전체 "최선의 결과"를 업데이트한다.
    preferable_result = std::max(preferable_result, result);

    // 단, 이미 승리하는 경우를 찾았으면 더 이상 탐색을 할 필요가 없다.
    if (preferable_result == game_result::WIN) break;
  }

  return preferable_result;
}

int main(void) {
  game_state initial_state;

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      std::cin >> initial_state[i][j];
      initial_state[i][j] -= '0';
    }
  }

  game_result result = solve_tictactoe(initial_state, game_turn::UNKNOWN);

  // 결과 출력
  switch (result) {
    case game_result::LOSE:
      std::cout << "L\n";
      break;
    case game_result::DRAW:
      std::cout << "D\n";
      break;
    case game_result::WIN:
      std::cout << "W\n";
      break;
    case game_result::UNKNOWN:
    default:
      /* never happens */
      assert(false);
      break;
  }

  return 0;
}