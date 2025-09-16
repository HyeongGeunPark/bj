/**
 * @file skiplist.hpp
 * @brief my own implementation of skiplist
 * @author HyeongGeun Park
 * @date 24-07-10
 */
#pragma once

#ifndef _SKIPLIST_HPP
#define _SKIPLIST_HPP

#ifndef RELEASE
#include <iostream>
#endif

#include <random>
#include <vector>

/**
 * @brief
 * @tparam keytype strict weak ordering with operator<()
 * @tparam datatype value semantics, which offers operator=() as deep copy
 */
template <typename keytype, typename datatype>
class SkipList {
 public:
  // subclass
  class Node {
   public:
    keytype key;    // key
    datatype data;  // data
    std::vector<Node*> forward;
    Node(keytype key, datatype data, int level)
        : key{key}, data{data}, forward(level + 1, nullptr) {}
    int level() { return forward.size() - 1; }
  };

  // constructor
  SkipList(int maxlevel = 32, double p = 0.5)
      : maxlevel{maxlevel},
        p{p},
        head{keytype{}, datatype{}, 0},
        rd{},
        gen{rd()},
        dis(1, p),
        sz{0} {}

  // interfaces

  /**
   * @brief insert a new node with given key
   * @param key key for the new node
   * @return true for success, false for failure
   */
  Node* insert(keytype key, datatype data) {
    Node* current = &head;
    std::vector<Node*> update(level() + 1, nullptr);

    for (int i = level(); i >= 0; --i) {
      while (current->forward[i] != nullptr && current->forward[i]->key < key)
        current = current->forward[i];
      update[i] = current;
    }

    // after this, current becomes the point where the new node
    // should be inserted
    current = current->forward[0];

    // 1. current could be nullptr, so it should be checked
    // before referencing.
    // 2. if current == nullptr, new node should be inserted
    // 3. if current != nullptr, new node should be inserted
    // only if current->key != key,
    // to do not accept duplicate key
    if (current == nullptr || current->key != key) {
      int newlevel = randomlevel();
      Node* newnode = new Node{key, data, newlevel};

      for (int i = 0; i <= newlevel; ++i) {
        if (i > level()) {
          head.forward.push_back(newnode);
        } else {
          newnode->forward[i] = update[i]->forward[i];
          update[i]->forward[i] = newnode;
        }
      }
      // successfully inserted a key
      return newnode;
    }
    // could not insert a key
    return nullptr;
  }

  /**
   * @brief erase a node with given key
   * @param key key for finding the node to delete
   * @return true on success, false on failure(e.g. there is no Node with given
   * key)
   */
  bool erase(int key) {
    Node* current = &head;

    std::vector<Node*> update(level() + 1, nullptr);

    for (int i = level(); i >= 0; --i) {
      while (current->forward[i] != nullptr && current->forward[i]->key < key)
        current = current->forward[i];
      update[i] = current;
    }

    current = current->forward[0];

    // key found
    if (current != nullptr && current->key == key) {
      for (int i = 0; i <= level(); ++i) {
        if (update[i]->forward[i] != current) break;
        update[i]->forward[i] = current->forward[i];
      }
      while (level() != 0 && head.forward.back() == nullptr) {
        head.forward.pop_back();
      }
      delete current;
      return true;
    }

    // key not found
    return false;
  }

  /**
   * @brief find a node with given key
   * @param key key for finding the node
   * @return true on success, false on failure
   */
  Node* find(int key) const {
    const Node* current = &head;

    for (int i = level(); i >= 0; --i) {
      while (current->forward[i] != nullptr && current->forward[i]->key < key)
        current = current->forward[i];
    }

    current = current->forward[0];
    if (current != nullptr && current->key == key) {
      return current;
    }
    return nullptr;
  }

  /**
   * @brief destructor
   * deallocates all nodes
   */
  ~SkipList() {
    Node* current = head.forward[0];
    while (current) {
      Node* next = current->forward[0];
      delete current;
      current = next;
    }
  }

  // debug output function
#ifndef RELEASE
  /**
   * @brief print all nodes in a skip list, layer by layer
   */
  void print() const {
    std::cout << "total levels: " << level() << '\n';
    for (int i = level(); i >= 0; --i) {
      std::cout << "level " << i << ": head";
      for (Node* cur = head.forward[i]; cur; cur = cur->forward[i]) {
        std::cout << " -> ( " << cur->key << " : " << cur->data << " )";
      }
      std::cout << " -> NIL\n";
    }
  }

  /**
   * @brief internal function randp() test
   * @param testnum total test number
   */
  void randptest(int testnum) {
    int result_true = 0;
    int result_false = 0;
    for (int i = 0; i < testnum; ++i) {
      if (randp())
        ++result_true;
      else
        ++result_false;
    }
    std::cout << "true: " << result_true << "false: " << result_false;
  }

  /**
   * @brief internal function randomlevel() test
   * @param testnum total test number
   */
  void randomleveltest(int testnum) {
    std::vector<int> result(maxlevel + 1, 0);
    while (testnum--) {
      result[randomlevel()]++;
    }
    for (int i = 0; i <= maxlevel; ++i) {
      std::cout << "level " << i << " : " << result[i] << '\n';
    }
  }
#endif

 private:
  /**
   * @brief allow maximum level of skiplist
   */
  int maxlevel;
  /**
   * @brief probability that a node could have an upper layer node
   */
  double p;
  /**
   * @brief  current level of skip list(which have a node)
   */
  int level() const { return head.forward.size() - 1; }
  /**
   * @brief head node for skip list
   */
  Node head;
  /**
   * @brief total number of Nodes in the skip list
   */
  size_t sz;

  // random number generator;
  std::random_device rd;
  std::mt19937 gen;
  std::binomial_distribution<int> dis;

  /**
   * @brief wrapper for random number generator
   * @return return 1 with the probability of p
   */
  bool randp() { return dis(gen); }

  /**
   * @brief  determine the level for newly inserted Node
   * @return number of consecutive success with probability p,
   * but maximum value is maxlevel.
   */
  int randomlevel() {
    int level = 0;
    while (level < maxlevel && randp()) {
      ++level;
    }
    return level;
  }
};

/*
int main(void) {
  SkipList<int, std::string> s;
  for (char c = 'A'; c <= 'Z'; ++c) {
    s.insert(static_cast<int>(c), "test");
  }
  s.print();
  for (char c = 'A'; c <= 'Z'; ++c) {
    s.erase(static_cast<int>(c));
  }
  s.print();

}
*/
#endif
