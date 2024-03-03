//======= Copyright (c) 2024, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - test suite
//
// $NoKeywords: $ivs_project_1 $white_box_tests.cpp
// $Author:     Tomáš Lajda <xlajdat00@stud.fit.vutbr.cz>
// $Date:       $2024-02-14
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Tomáš Lajda
 * 
 * @brief Implementace testu hasovaci tabulky.
 */

#include <vector>

#include "gtest/gtest.h"

#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy hasovaci tabulky, testujte nasledujici:
// 1. Verejne rozhrani hasovaci tabulky
//     - Vsechny funkce z white_box_code.h
//     - Chovani techto metod testuje pro prazdnou i neprazdnou tabulku.
// 2. Chovani tabulky v hranicnich pripadech
//     - Otestujte chovani pri kolizich ruznych klicu se stejnym hashem 
//     - Otestujte chovani pri kolizich hashu namapovane na stejne misto v 
//       indexu
//============================================================================//
class HashTable : public testing::Test {
  protected:
    hash_map* hashTable = hash_map_ctor();

  void SetUp() override {
    ASSERT_NE(hashTable, nullptr);

    for(size_t i = 0; i < HASH_MAP_INIT_SIZE; i++) {
      std::ostringstream keyStream;
      keyStream << "Key " << i;
      std::string key = keyStream.str();
      
      EXPECT_EQ(hash_map_put(hashTable, key.c_str(), i), OK);
    }
  }

  void TearDown() override {
    hash_map_dtor(hashTable);
    ASSERT_EQ(hashTable->allocated, 0);
  }
};

TEST_F(HashTable, PutAddedValue) {
  EXPECT_EQ(hash_map_put(hashTable, "Key 1", 1), KEY_ALREADY_EXISTS);
}

TEST_F(HashTable, HashMapGetValues) {
  int value;

  for(size_t i = 0; i < HASH_MAP_INIT_SIZE; i++) {
    std::ostringstream keyStream;
    keyStream << "Key " << i;
    std::string key = keyStream.str();

    hash_map_get(hashTable, key.c_str(), &value);
    EXPECT_EQ(value, i);
  }
}

TEST_F(HashTable, GetNotExistingKey) {
  int value;
  EXPECT_EQ(hash_map_get(hashTable, "Key 100", &value), KEY_ERROR);
}

TEST_F(HashTable, HashMapSize){
  ASSERT_EQ(hash_map_size(hashTable), HASH_MAP_INIT_SIZE);
}

TEST_F(HashTable, HashMapCapacity){
  EXPECT_EQ(hash_map_capacity(hashTable), HASH_MAP_INIT_SIZE * 2);
}

TEST_F(HashTable, PuttingMoreThanCapacity) {
  for(size_t i = HASH_MAP_INIT_SIZE; i < HASH_MAP_INIT_SIZE * 2 + 1; i++) {
      std::ostringstream keyStream;
      keyStream << "Key " << i;
      std::string key = keyStream.str();

      EXPECT_EQ(hash_map_put(hashTable, key.c_str(), i), OK);
    }

  EXPECT_EQ(hash_map_capacity(hashTable), HASH_MAP_INIT_SIZE * 4);
}

TEST_F(HashTable, HashMapRemoveFirst) {
  EXPECT_EQ(hash_map_remove(hashTable, "Key 0"), OK);
}

TEST_F(HashTable, HashMapRemoveNonExisting) {
  EXPECT_EQ(hash_map_remove(hashTable, "Key 1"), OK);
  EXPECT_EQ(hash_map_remove(hashTable, "Key 1"), KEY_ERROR);
}

TEST_F(HashTable, HashMapRemoveNotLastNotFirst) {
  EXPECT_EQ(hash_map_remove(hashTable, "Key 6"), OK);
}

TEST_F(HashTable, HashMapRemoveLast) {
  EXPECT_EQ(hash_map_remove(hashTable, "Key 7"), OK);
}

TEST_F(HashTable, HashMapContains) {
  EXPECT_TRUE(hash_map_contains(hashTable, "Key 1"));
}

TEST_F(HashTable, HashMapDoesntContains) {
  EXPECT_FALSE(hash_map_contains(hashTable, "Key 10"));
}

TEST_F(HashTable, ReserveMore) {
  EXPECT_EQ(hash_map_reserve(hashTable, 32), OK);
  EXPECT_EQ(hash_map_capacity(hashTable), 32);
}

TEST_F(HashTable, ReserveLess) {
  EXPECT_EQ(hash_map_reserve(hashTable, 1), VALUE_ERROR);
  EXPECT_NE(hash_map_capacity(hashTable), 1);
}

TEST_F(HashTable, ReserveSame) {
  EXPECT_EQ(hash_map_reserve(hashTable, 16), OK);
  EXPECT_EQ(hash_map_capacity(hashTable), 16);
}

/*** Konec souboru white_box_tests.cpp ***/
