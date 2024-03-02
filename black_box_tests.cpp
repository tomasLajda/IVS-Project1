//======= Copyright (c) 2024, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2024-02-14
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author JMENO PRIJMENI
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
  EXPECT_TRUE(insertedNode.first) << "Key: 1 wasn't inserted";
  EXPECT_EQ(insertedNode.second->key, 1);
  
  insertedNode = emptyTree.InsertNode(1);
  EXPECT_FALSE(insertedNode.first) << "Key: 1 was suppossed to be already inserted";
  
  insertedNode = emptyTree.InsertNode(2);
  EXPECT_TRUE(insertedNode.first) << "Key: 2 wasn't inserted";
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
/*** Konec souboru black_box_tests.cpp ***/
