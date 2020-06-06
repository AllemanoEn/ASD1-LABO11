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
        REQUIRE( to_string(tree).empty() );
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
        REQUIRE( to_string(tree2).empty() );
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
        REQUIRE( to_string(tree2).empty() );
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

    SECTION( "Arbre unaire sur la droite" ) {
        for(int i : { 8, 4, 3, 2, 1})
            tree.insert(i);

        ostringstream oss;
        tree.display_indented(oss);
        REQUIRE( oss.str() == "8\n"
                              "|_ 4\n"
                              "|  |_ 3\n"
                              "|  |  |_ 2\n"
                              "|  |  |  |_ 1\n"
                              "|  |  |  |_ .\n"
                              "|  |  |_ .\n"
                              "|  |_ .\n"
                              "|_ .\n");
    }

    SECTION( "Arbre unaire sur la gauche" ) {
        for(int i : { 8, 9, 10, 11, 12})
            tree.insert(i);

        ostringstream oss;
        tree.display_indented(oss);
        REQUIRE( oss.str() == "8\n"
                              "|_ .\n"
                              "|_ 9\n"
                              "   |_ .\n"
                              "   |_ 10\n"
                              "      |_ .\n"
                              "      |_ 11\n"
                              "         |_ .\n"
                              "         |_ 12\n");
    }
    SECTION( "Arbre unaire sur la gauche" ) {
        for(int i : { 8, 9, 10, 11, 12})
            tree.insert(i);

        ostringstream oss;
        tree.display_indented(oss);
        REQUIRE( oss.str() == "8\n"
                              "|_ .\n"
                              "|_ 9\n"
                              "   |_ .\n"
                              "   |_ 10\n"
                              "      |_ .\n"
                              "      |_ 11\n"
                              "         |_ .\n"
                              "         |_ 12\n");
    }

    SECTION( "Arbre vide" ) {
        ostringstream oss;
        tree.display_indented(oss);
        REQUIRE( oss.str().empty());
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

    SECTION("Contient un élément"){
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            tree.insert(i);
        REQUIRE(tree.contains(11));
    }
}

TEST_CASE( "destructeur", "[bst]") {

    bst<int> tree1;
    bst<int> tree2;

    for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
        tree1.insert(i);

    SECTION( "arbre à détruire" ) {
        tree1.~bst();
        REQUIRE(to_string(tree1).empty());
    }

    SECTION( "arbre vide à détruire" ) {
        tree2.~bst();
        REQUIRE(to_string(tree2).empty());
    }

}

TEST_CASE( "Min", "[bst]") {

    bst<int> tree1;
    bst<int> tree2;
    bst<int> tree3;

    for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
        tree1.insert(i);
    for (int i : {-8, -4, -1, -2, -3, -6, -5, -7, -11, -10, -12})
        tree2.insert(i);

    SECTION( "Chercher le min" ) {
        REQUIRE(tree1.min() == 1);
    }
    SECTION( "Chercher le min" ) {
        REQUIRE(tree2.min() == -12);
    }
    SECTION( "Chercher le min (lève une exception)" ) {
        REQUIRE_THROWS_AS(tree3.min(),std::exception);
    }
}

TEST_CASE( "Max", "[bst]") {

    bst<int> tree1;
    bst<int> tree2;
    bst<int> tree3;

    for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
        tree1.insert(i);
    for (int i : {-8, -4, -1, -2, -3, -6, -5, -7, -11, -10, -12})
        tree2.insert(i);

    SECTION( "Chercher le max" ) {
        REQUIRE(tree1.max() == 12);
    }
    SECTION( "Chercher le max" ) {
        REQUIRE(tree2.max() == -1);
    }
    SECTION( "Chercher le max (lève une exception)" ) {
        REQUIRE_THROWS_AS(tree3.max(),std::exception);
    }
}

TEST_CASE( "erase", "[bst]") {

    bst<int> tree;

    SECTION( "suppression d'un élément" ) {
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            tree.insert(i);

        tree.erase(7);
        REQUIRE(!tree.contains(7));
    }

    SECTION( "suppression d'un élément non dans l'arbre" ) {
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            tree.insert(i);

        tree.erase(15);
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            REQUIRE(tree.contains(i));
    }

    SECTION( "suppression deux fois d'un élément" ) {
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            tree.insert(i);

        tree.erase(3);
        tree.erase(3);
        REQUIRE(!tree.contains(3));
    }

    SECTION( "suppression de la racine" ) {
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            tree.insert(i);

        tree.erase(8);
        ostringstream oss;
        tree.display_indented(oss);
        REQUIRE( oss.str() == "10\n"
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
                              "   |_ .\n"
                              "   |_ 12\n" );
    }

    SECTION( "suppression de l'arbre entier" ) {
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            tree.insert(i);

        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            tree.erase(i);

        ostringstream oss;
        tree.display_indented(oss);
        REQUIRE( oss.str().empty());
    }

}

TEST_CASE( "erase_max", "[bst]") {

    bst<int> tree1;
    bst<int> tree2;
    bst<int> tree3;

    for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
        tree1.insert(i);
    for (int i : {-8, -4, -1, -2, -3, -6, -5, -7, -11, -10, -12})
        tree2.insert(i);

    SECTION( "supprimer le max" ) {
        tree1.erase_max();
        REQUIRE(!tree1.contains(12));
    }
    SECTION( "supprimer le max" ) {
        tree2.erase_max();
        REQUIRE(!tree2.contains(-1));
    }
    SECTION( "supprimer 3 fois le max" ) {
        tree1.erase_max();
        tree1.erase_max();
        tree1.erase_max();
        REQUIRE(!tree1.contains(10));
        REQUIRE(!tree1.contains(11));
        REQUIRE(!tree1.contains(12));
    }
    SECTION( "supprimer le max (lève une exception)" ) {
        REQUIRE_THROWS_AS(tree3.erase_max(),std::exception);
    }
}

TEST_CASE( "erase_min", "[bst]") {

    bst<int> tree1;
    bst<int> tree2;
    bst<int> tree3;

    for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
        tree1.insert(i);
    for (int i : {-8, -4, -1, -2, -3, -6, -5, -7, -11, -10, -12})
        tree2.insert(i);

    SECTION( "supprimer le min" ) {
        tree1.erase_min();
        REQUIRE(!tree1.contains(1));
    }
    SECTION( "supprimer le min" ) {
        tree2.erase_min();
        REQUIRE(!tree2.contains(-12));
    }
    SECTION( "supprimer 3 fois le min" ) {
        tree1.erase_min();
        tree1.erase_min();
        tree1.erase_min();
        REQUIRE(!tree1.contains(1));
        REQUIRE(!tree1.contains(2));
        REQUIRE(!tree1.contains(3));
    }
    SECTION( "supprimer le min (lève une exception)" ) {
        REQUIRE_THROWS_AS(tree3.erase_min(),std::exception);
    }
}