#include "catch.hpp"
#include "../bst.h"

#include <sstream>
#include <string>
using namespace std;

template<typename T>
string to_string(T const& t) {
    ostringstream oss;
    oss << t;
    return oss.str();
}

TEST_CASE( "operator<<", "[bst]") {

    bst<int> tree;

    SECTION( "Tree from ASD1 slides" ) {
        for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
            tree.insert(i);
        REQUIRE( to_string(tree) == "8(4(1(.,2(.,3)),6(5,7)),11(10,12))" );
    }

    SECTION( "Empty tree" ) {
        REQUIRE( to_string(tree) == "" );
    }
}

TEST_CASE( "operateur de copie", "[bst]") {

    bst<int> tree;

    SECTION( "Test de copie" ) {
        for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
            tree.insert(i);

        bst<int> tree2(tree);
        REQUIRE( to_string(tree2) == "8(4(1(.,2(.,3)),6(5,7)),11(10,12))" );
    }

    SECTION( "copier arbre vide" ) {
        bst<int> tree2(tree);
        REQUIRE( to_string(tree2) == "" );
    }
}

TEST_CASE( "operateur d'affectation", "[bst]") {

    bst<int> tree;

    SECTION( "Test d'affectation'" ) {
        for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
            tree.insert(i);

        bst<int> tree2 = tree;
        REQUIRE( to_string(tree2) == "8(4(1(.,2(.,3)),6(5,7)),11(10,12))" );
    }

    SECTION( "copier arbre vide" ) {
        bst<int> tree2 = tree;
        REQUIRE( to_string(tree2) == "" );
    }
}

TEST_CASE( "insert", "[bst]") {

    bst<int> tree;

    SECTION( "Insert 42" ) {
        tree.insert(42);
        REQUIRE( to_string(tree) == "42" );
    }

    SECTION( "Insert smaller to the left" ) {
        tree.insert(3);
        tree.insert(2);
        REQUIRE( to_string(tree) == "3(2,.)" );
    }

    SECTION( "Insert larger to the right" ) {
        tree.insert(3);
        tree.insert(4);
        REQUIRE( to_string(tree) == "3(.,4)" );
    }

    SECTION( "Insert twice has no effect" ) {
        tree.insert(3);
        tree.insert(4);
        tree.insert(4);
        REQUIRE( to_string(tree) == "3(.,4)" );
    }
}

TEST_CASE("display_indented", "[bst]") {
    bst<int> tree;

    SECTION( "Tree from ASD1 slides" ) {
        for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
            tree.insert(i);

        ostringstream oss;
        tree.display_indented(oss);
        REQUIRE( oss.str() == "8\n"
                              "|_ 4\n"
                              "|  |_ 1\n"
                              "|  |  |_ .\n"
                              "|  |  |_ 2\n"
                              "|  |     |_ .\n"
                              "|  |     |_ 3\n"
                              "|  |_ 6\n"
                              "|     |_ 5\n"
                              "|     |_ 7\n"
                              "|_ 11\n"
                              "   |_ 10\n"
                              "   |_ 12\n" );
    }
}

TEST_CASE( "contains", "[bst]") {

    bst<int> tree;

    SECTION( "contient tous les éléments" ) {
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            tree.insert(i);
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            REQUIRE(tree.contains(i));
    }
    SECTION( "ne contient pas les éléments" ) {
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            tree.insert(i);
        for (int i : {9, 13, 0, -7, 1500, 99, 14, 15, -11, 27, 120})
            REQUIRE(!tree.contains(i));
    }
}

TEST_CASE( "destructeur", "[bst]") {

    bst<int> tree;

    for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
        tree.insert(i);

    SECTION( "arbre à détruire" ) {
        tree.~bst();
        REQUIRE(to_string(tree) == "");
    }

}

TEST_CASE( "Min", "[bst]") {

    bst<int> tree1;
    bst<int> tree2;
    bst<int> tree3;

    for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
        tree1.insert(i);
    for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
        tree2.insert(i);

    SECTION( "Chercher le min" ) {
        REQUIRE(to_string(tree1.min()) == "");
    }
    SECTION( "Chercher le min" ) {
        REQUIRE(to_string(tree1.min()) == "");
    }
    SECTION( "Chercher le min (lève une exception)" ) {
        REQUIRE(to_string(tree1.min()) == "");
    }
}

TEST_CASE( "Max", "[bst]") {

    bst<int> tree1;
    bst<int> tree2;
    bst<int> tree3;

    for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
        tree1.insert(i);
    for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
        tree2.insert(i);

    SECTION( "Chercher le max" ) {
        REQUIRE(to_string(tree1.min()) == "");
    }
    SECTION( "Chercher le max" ) {
        REQUIRE(to_string(tree1.min()) == "");
    }
    SECTION( "Chercher le max (lève une exception)" ) {
        REQUIRE(to_string(tree1.min()) == "");
    }
}