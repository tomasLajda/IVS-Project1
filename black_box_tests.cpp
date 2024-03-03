//======= Copyright (c) 2024, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Tomáš Lajda <xlajdat00@stud.fit.vutbr.cz>
// $Date:       $2024-02-14
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Tomáš Lajda
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

class EmptyTree : public testing::Test {
  protected:
    BinaryTree emptyTree = BinaryTree();
};

TEST_F(EmptyTree, InsertNode) {
  std::pair<bool, Node_t*> insertedNode = emptyTree.InsertNode(1);
  ASSERT_TRUE(insertedNode.first) << "Key: 1 wasn't inserted";
  EXPECT_EQ(insertedNode.second->key, 1);
  
  insertedNode = emptyTree.InsertNode(1);
  EXPECT_FALSE(insertedNode.first) << "Key: 1 was suppossed to be already inserted";
  
  insertedNode = emptyTree.InsertNode(2);
  ASSERT_TRUE(insertedNode.first) << "Key: 2 wasn't inserted";
  EXPECT_EQ(insertedNode.second->key, 2);
}

TEST_F(EmptyTree, DeleteNode) {
  EXPECT_FALSE(emptyTree.DeleteNode(0)) << "Key: 0 should not exist"; 

  EXPECT_FALSE(emptyTree.DeleteNode(1)) << "Key: 1 should not exist";
}

TEST_F(EmptyTree, FindNode) {
  EXPECT_FALSE(emptyTree.FindNode(0)) << "Key: 0 should not exist"; 

  EXPECT_FALSE(emptyTree.FindNode(1)) << "Key: 1 should not exist"; 
}

class NonEmptyTree : public testing::Test {
  protected:
    BinaryTree nonEmptyTree;

  void SetUp() override {
    int keys[] = {2, 8, 20, 6, 14, 60, 24, 52, 1, 7};
    for(int key : keys) {
      nonEmptyTree.InsertNode(key);
    }
  } 
};

TEST_F(NonEmptyTree, InsertNode) {
  std::pair<bool, Node_t*> insertedNode = nonEmptyTree.InsertNode(1);
  ASSERT_FALSE(insertedNode.first) << "Key: 1 was suppossed to be already inserted";
  EXPECT_EQ(insertedNode.second->key, 1);
  
  insertedNode = nonEmptyTree.InsertNode(10);
  ASSERT_TRUE(insertedNode.first) << "Key: 10 wasn't inserted";
  EXPECT_EQ(insertedNode.second->key, 10);

  insertedNode = nonEmptyTree.InsertNode(10);
  ASSERT_FALSE(insertedNode.first) << "Key: 1 was suppossed to be already inserted";
  EXPECT_EQ(insertedNode.second->key, 10);
}

TEST_F(NonEmptyTree, DeleteNode) {
  EXPECT_FALSE(nonEmptyTree.DeleteNode(0)) << "Key: 0 should not exist"; 

  EXPECT_TRUE(nonEmptyTree.DeleteNode(1)) << "Key: 1 should be deleted";
}

TEST_F(NonEmptyTree, FindNode) {
  EXPECT_FALSE(nonEmptyTree.FindNode(0)) << "Key: 0 should not exist"; 

  EXPECT_TRUE(nonEmptyTree.FindNode(1)) << "Key: 1 should be found"; 
}


class TreeAxioms : public testing::Test {
  protected:
    BinaryTree treeAxioms;

  void SetUp() override {
    int keys[] = {50, 25, 75, 10, 40, 60, 5, 3, 1};
    for(int key : keys) {
      treeAxioms.InsertNode(key);
    }
  } 
};

// All leaf nodes (nodes without children) are "black"
TEST_F(TreeAxioms, Axiom1) {
  std::vector<Node_t *> leafs;
  treeAxioms.GetLeafNodes(leafs);

  for(Node_t* leaf : leafs) {
    EXPECT_EQ(leaf->color, BinaryTree::BLACK) << "Leaf should be red";
  }
}

// If a node is "red", then both of its children are "black"
TEST_F(TreeAxioms, Axiom2) {
  std::vector<Node_t *> nonLeafs;
  treeAxioms.GetNonLeafNodes(nonLeafs);

  for(Node_t * nonLeaf : nonLeafs) {
    if(nonLeaf->color == BinaryTree::RED) {
      EXPECT_EQ(nonLeaf->pLeft->color, BinaryTree::BLACK) << "Red note should have a left black child";
      EXPECT_EQ(nonLeaf->pRight->color, BinaryTree::BLACK) << "Red note should have a right black child";
    }
  }
}

// Each path from each leaf node to the root contains the same number of "black" nodes
TEST_F(TreeAxioms, Axiom3) {
  std::vector<Node_t *> leafs;
  treeAxioms.GetLeafNodes(leafs);
  
  bool firstLeaf = true;
  size_t toRootBaselength = 0;

  for(Node_t* leaf : leafs) {
    bool foundRoot = false;
    Node_t* node = leaf->pParent;
    size_t toRootLength = 0;

    while(!foundRoot) {
      if(node->color == BinaryTree::BLACK) {
        toRootLength++;

        if(firstLeaf) {
          toRootBaselength++;
        }
      }

      if (node == treeAxioms.GetRoot()) {
        foundRoot = true;
        EXPECT_EQ(toRootBaselength, toRootLength);

        if(firstLeaf) {
          firstLeaf = false;
        }
      }
      else {
        node = node->pParent;
      }
    }
  }
}
/*** Konec souboru black_box_tests.cpp ***/
