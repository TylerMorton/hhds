#include <iostream>
#include <random>
#include <vector>

#include "lhtree.hpp"
#include "tree.hpp"

// Utility function to generate a random int within a range
int generate_random_int(std::default_random_engine& generator, int min, int max) {
  std::uniform_int_distribution<int> distribution(min, max);
  return distribution(generator);
}

// Preorder traversal for hhds::tree (Use "const hhds::tree<int>& tree" to pass tree as a const reference)
void preorder_traversal_hhds(hhds::tree<int>& tree, std::vector<int>& result) {
  for (const auto& node : tree.pre_order()) {
    result.push_back(tree[node]);
  }
}

// Postorder traversal for hhds::tree (Use "const hhds::tree<int>& tree" to pass tree as a const reference)
void postorder_traversal_hhds(hhds::tree<int>& tree, std::vector<int>& result) {
  for (const auto& node : tree.post_order()) {
    result.push_back(tree[node]);
  }
}

// Preorder traversal for lh::tree
void preorder_traversal_lhtree(lh::tree<int>& tree, std::vector<int>& result) {
  auto                                                 root_index = lh::Tree_index(0, 0);
  typename lh::tree<int>::Tree_depth_preorder_iterator it(root_index, &tree);
  for (auto node_it = it.begin(); node_it != it.end(); ++node_it) {
    result.push_back(tree.get_data(*node_it));
  }
}

// Postorder traversal for lh::tree
void postorder_traversal_lhtree(lh::tree<int>& tree, std::vector<int>& result) {
  auto                                                  root_index = lh::Tree_index(0, 0);
  typename lh::tree<int>::Tree_depth_postorder_iterator it(root_index, &tree);
  for (auto node_it = it.begin(); node_it != it.end(); ++node_it) {
    result.push_back(tree.get_data(*node_it));
  }
}

// Utility function to compare two vectors
template <typename T>
bool compare_vectors(const std::vector<T>& vec1, const std::vector<T>& vec2) {
  return vec1 == vec2;
}

// Test 1: Very Deep Tree (Tens of Millions of Nodes)
void test_deep_tree() {
  std::default_random_engine generator(42);
  //int                        num_nodes = 10'000'000;  // Use a smaller number for testing
  int                        num_nodes = 10'000'000;  // Use a smaller number for testing

  hhds::tree<int> hhds_tree;
  lh::tree<int>   lh_tree;

  auto data_to_add = generate_random_int(generator, 1, 100);
  auto hhds_root   = hhds_tree.add_root(data_to_add);
  lh_tree.set_root(data_to_add);
  lh::Tree_index lh_current(0, 0);
  auto           hhds_current = hhds_root;

  for (int i = 0; i < num_nodes; ++i) {
    data_to_add  = generate_random_int(generator, 1, 100);
    hhds_current = hhds_tree.add_child(hhds_current, data_to_add);
    lh_current   = lh_tree.add_child(lh_current, data_to_add);
  }

  std::vector<int> hhds_preorder, lh_preorder, hhds_postorder, lh_postorder;
  preorder_traversal_hhds(hhds_tree, hhds_preorder);
  preorder_traversal_lhtree(lh_tree, lh_preorder);
  postorder_traversal_hhds(hhds_tree, hhds_postorder);
  postorder_traversal_lhtree(lh_tree, lh_postorder);

  if (!compare_vectors(hhds_preorder, lh_preorder)) {
    std::cout << "Preorder traversal mismatch in test_deep_tree" << std::endl;
  } else {
    std::cout << "Preorder traversal match!" << std::endl;
  }
  if (!compare_vectors(hhds_postorder, lh_postorder)) {
    std::cout << "Postorder traversal mismatch in test_deep_tree" << std::endl;
  } else {
    std::cout << "Postorder traversal match!" << std::endl;
  }
}

int main() {
  test_deep_tree();
  return 0;
}
