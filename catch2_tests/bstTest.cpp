/// \file bstTest.cpp
/// \authors Enzo Allemano et Adrien Pegiueron
/// \date 08.06.2020
///
/// \brief \b Laboratoire \b 11
/// \brief Contient la série de test des fonctions de manipulations d'un arbre binaire.
///
/// Remarque(s) :
///
/// Compilateur :  MinGW-g++ 6.3.0
#include "catch.hpp"
#include "../bst.h"

#include <sstream>
#include <string>
using namespace std;

ostringstream oss_visit_in_order; //Requis pour le test de visit in order

template<typename T>
string to_string(T const& t) {
    ostringstream oss;
    oss << t;
    return oss.str();
}

template<typename Key>
void affichage(Key k) {
    oss_visit_in_order << k << " ";
}

TEST_CASE( "operator<<", "[bst]") {

    bst<int> tree;
    bst<double> dTree;

    SECTION( "Tree from ASD1 slides" ) {
        for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
            tree.insert(i);
        REQUIRE( to_string(tree) == "8(4(1(.,2(.,3)),6(5,7)),11(10,12))" );
    }

    SECTION("arbre double") {
        for (double i : {8.1, 4.2, 1.3, 2.4, 3.5, 6.6, 5.7, 7.8, 11.9, 10.1, 12.2})
            dTree.insert(i);

        REQUIRE(to_string(dTree) == "8.1(4.2(1.3(.,2.4(.,3.5)),6.6(5.7,7.8)),11.9(10.1,12.2))");

    }

    SECTION( "Empty tree" ) {
        REQUIRE( to_string(tree).empty() );
    }
}

TEST_CASE( "operateur de copie", "[bst]") {

    bst<int> tree;
    bst<double> dTree;

    SECTION( "Test de copie" ) {
        for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
            tree.insert(i);

        bst<int> tree2(tree);
        REQUIRE( to_string(tree2) == "8(4(1(.,2(.,3)),6(5,7)),11(10,12))" );
    }

    SECTION("copier arbre double"){
        for (double i : {8.1, 4.2, 1.3, 2.4, 3.5, 6.6, 5.7, 7.8, 11.9, 10.1, 12.2})
            dTree.insert(i);

        bst<double> dTree2(dTree);
        REQUIRE(to_string(dTree2) == "8.1(4.2(1.3(.,2.4(.,3.5)),6.6(5.7,7.8)),11.9(10.1,12.2))");
    }

    SECTION( "copier arbre vide" ) {
        bst<int> tree2(tree);
        REQUIRE( to_string(tree2).empty() );
    }
}

TEST_CASE( "operateur d'affectation", "[bst]") {

    bst<int> tree;
    bst<double> dTree;

    SECTION( "Test d'affectation'" ) {
        for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
            tree.insert(i);

        bst<int> tree2 = tree;
        REQUIRE( to_string(tree2) == "8(4(1(.,2(.,3)),6(5,7)),11(10,12))" );
    }

    SECTION("affectation arbre double") {
        for (double i : {8.1, 4.2, 1.3, 2.4, 3.5, 6.6, 5.7, 7.8, 11.9, 10.1, 12.2})
            dTree.insert(i);

        bst<double> dTree2 = dTree;
        REQUIRE(to_string(dTree2) == "8.1(4.2(1.3(.,2.4(.,3.5)),6.6(5.7,7.8)),11.9(10.1,12.2))");

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
    bst<double> dTree;

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

    SECTION( "Arbre double" ) {
        for (double i : {8.1, 4.2, 1.3, 2.4, 3.5, 6.6, 5.7, 7.8, 11.9, 10.1, 12.2})
            dTree.insert(i);

        ostringstream oss;
        dTree.display_indented(oss);
        REQUIRE( oss.str() == "8.100000\n"
                              "|_ 4.200000\n"
                              "|  |_ 1.300000\n"
                              "|  |  |_ .\n"
                              "|  |  |_ 2.400000\n"
                              "|  |     |_ .\n"
                              "|  |     |_ 3.500000\n"
                              "|  |_ 6.600000\n"
                              "|     |_ 5.700000\n"
                              "|     |_ 7.800000\n"
                              "|_ 11.900000\n"
                              "   |_ 10.100000\n"
                              "   |_ 12.200000\n" );
    }

}

TEST_CASE( "contains", "[bst]") {

    bst<int> tree;
    bst<double> dTree;

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

    SECTION( "contient tous les éléments en double" ) {
        for (double i : {8.1, 4.2, 1.3, 2.4, 3.5, 6.6, 5.7, 7.8, 11.9, 10.1, 12.2})
            dTree.insert(i);
        for (double i : {8.1, 4.2, 1.3, 2.4, 3.5, 6.6, 5.7, 7.8, 11.9, 10.1, 12.2})
            REQUIRE(dTree.contains(i));
    }

    SECTION("contenu d'un arbre vide"){
        REQUIRE(!tree.contains(3));
    }
}

TEST_CASE( "destructeur", "[bst]") {

    bst<int> tree1;
    bst<int> tree2;
    bst<double> dTree;


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

    SECTION("destruction arbre double") {
        for (double i : {8.1, 4.2, 1.3, 2.4, 3.5, 6.6, 5.7, 7.8, 11.9, 10.1, 12.2})
            dTree.insert(i);

        dTree.~bst();
        REQUIRE(to_string(dTree).empty());

    }

}

TEST_CASE( "Min", "[bst]") {

    bst<int> tree;
    bst<double> dTree;

    SECTION( "Chercher le min" ) {
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            tree.insert(i);
        REQUIRE(tree.min() == 1);
    }

    SECTION( "Chercher le min" ) {
        for (int i : {-8, -4, -1, -2, -3, -6, -5, -7, -11, -10, -12})
            tree.insert(i);
        REQUIRE(tree.min() == -12);
    }

    SECTION( "Chercher le min (lève une exception)" ) {
        REQUIRE_THROWS_AS(tree.min(),std::exception);
    }

    SECTION("Chercher le min d'un arbre double"){
        for (double i : {8.1, 4.2, 1.3, 2.4, 3.5, 6.6, 5.7, 7.8, 11.9, 10.1, 12.2})
            dTree.insert(i);
        REQUIRE(dTree.min() == 1.3);
    }
}

TEST_CASE( "Max", "[bst]") {

    bst<int> tree;
    bst<double> dTree;

    SECTION( "Chercher le max" ) {
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            tree.insert(i);
        REQUIRE(tree.max() == 12);
    }

    SECTION( "Chercher le max" ) {
        for (int i : {-8, -4, -1, -2, -3, -6, -5, -7, -11, -10, -12})
            tree.insert(i);
        REQUIRE(tree.max() == -1);
    }

    SECTION( "Chercher le max (lève une exception)" ) {
        REQUIRE_THROWS_AS(tree.max(),std::exception);
    }

    SECTION("Chercher le max d'un arbre double"){
        for (double i : {8.1, 4.2, 1.3, 2.4, 3.5, 6.6, 5.7, 7.8, 11.9, 10.1, 12.2})
            dTree.insert(i);
        REQUIRE(dTree.max() == 12.2);
    }
}

TEST_CASE( "erase", "[bst]") {

    bst<int> tree;
    bst<double> dTree;

    SECTION( "suppression d'un élément" ) {
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            tree.insert(i);

        tree.erase(7);
        REQUIRE(!tree.contains(7));
    }

    SECTION( "suppression d'un élément double" ) {
        for (double i : {8.1, 4.2, 1.3, 2.4, 3.5, 6.6, 5.7, 7.8, 11.9, 10.1, 12.2})
            dTree.insert(i);

        dTree.erase(11.9);
        REQUIRE(!dTree.contains(11.9));
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

    bst<int> tree;
    bst<double> dTree;

    SECTION( "supprimer le max" ) {
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            tree.insert(i);
        tree.erase_max();
        REQUIRE(!tree.contains(12));
    }
    SECTION( "supprimer le max" ) {
        for (int i : {-8, -4, -1, -2, -3, -6, -5, -7, -11, -10, -12})
            tree.insert(i);
        tree.erase_max();
        REQUIRE(!tree.contains(-1));
    }
    SECTION( "supprimer 3 fois le max" ) {
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            tree.insert(i);
        tree.erase_max();
        tree.erase_max();
        tree.erase_max();
        REQUIRE(!tree.contains(10));
        REQUIRE(!tree.contains(11));
        REQUIRE(!tree.contains(12));
    }
    SECTION( "supprimer le max (lève une exception)" ) {
        REQUIRE_THROWS_AS(tree.erase_max(),std::exception);
    }
    SECTION("supprimer le max d'un arbre double"){
        for (double i : {8.1, 4.2, 1.3, 2.4, 3.5, 6.6, 5.7, 7.8, 11.9, 10.1, 12.2})
            dTree.insert(i);
        dTree.erase_max();
        REQUIRE(!dTree.contains(12.2));
    }
}

TEST_CASE( "erase_min", "[bst]") {

    bst<int> tree;
    bst<double> dTree;

    SECTION( "supprimer le min" ) {
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            tree.insert(i);
        tree.erase_min();
        REQUIRE(!tree.contains(1));
    }
    SECTION( "supprimer le min" ) {
        for (int i : {-8, -4, -1, -2, -3, -6, -5, -7, -11, -10, -12})
            tree.insert(i);
        tree.erase_min();
        REQUIRE(!tree.contains(-12));
    }
    SECTION( "supprimer 3 fois le min" ) {
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            tree.insert(i);
        tree.erase_min();
        tree.erase_min();
        tree.erase_min();
        REQUIRE(!tree.contains(1));
        REQUIRE(!tree.contains(2));
        REQUIRE(!tree.contains(3));
    }
    SECTION( "supprimer le min (lève une exception)" ) {
        REQUIRE_THROWS_AS(tree.erase_min(),std::exception);
    }
    SECTION("supprimer le min d'un arbre double"){
        for (double i : {8.1, 4.2, 1.3, 2.4, 3.5, 6.6, 5.7, 7.8, 11.9, 10.1, 12.2})
            dTree.insert(i);
        dTree.erase_min();
        REQUIRE(!dTree.contains(1.3));
    }
}

TEST_CASE("linearize", "[bst]") {
    bst<int> tree;
    bst<double> dTree;

    SECTION("linéarisation d'un arbre binaire gauche") {
        for (int i : {8, 4, 1, 2, 3})
            tree.insert(i);

        tree.linearize();
        ostringstream oss;
        tree.display_indented(oss);
        REQUIRE(oss.str() == "1\n"
                             "|_ .\n"
                             "|_ 2\n"
                             "   |_ .\n"
                             "   |_ 3\n"
                             "      |_ .\n"
                             "      |_ 4\n"
                             "         |_ .\n"
                             "         |_ 8\n");
    }

    SECTION("linéarisation d'un arbre binaire gauche double") {
        for (double i : {8.1, 4.2, 1.3, 2.4, 3.5})
            dTree.insert(i);

        dTree.linearize();
        ostringstream oss;
        dTree.display_indented(oss);
        REQUIRE(oss.str() == "1.300000\n"
                             "|_ .\n"
                             "|_ 2.400000\n"
                             "   |_ .\n"
                             "   |_ 3.500000\n"
                             "      |_ .\n"
                             "      |_ 4.200000\n"
                             "         |_ .\n"
                             "         |_ 8.100000\n");
    }

    SECTION("double linéarisation") {
        for (int i : {8, 4, 1, 2, 3})
            tree.insert(i);

        tree.linearize();
        tree.linearize();
        ostringstream oss;
        tree.display_indented(oss);
        REQUIRE(oss.str() == "1\n"
                             "|_ .\n"
                             "|_ 2\n"
                             "   |_ .\n"
                             "   |_ 3\n"
                             "      |_ .\n"
                             "      |_ 4\n"
                             "         |_ .\n"
                             "         |_ 8\n");
    }

    SECTION("arbre des slides d'asd"){
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            tree.insert(i);

        tree.linearize();
        ostringstream oss;
        tree.display_indented(oss);
        REQUIRE(oss.str() == "1\n"
                             "|_ .\n"
                             "|_ 2\n"
                             "   |_ .\n"
                             "   |_ 3\n"
                             "      |_ .\n"
                             "      |_ 4\n"
                             "         |_ .\n"
                             "         |_ 5\n"
                             "            |_ .\n"
                             "            |_ 6\n"
                             "               |_ .\n"
                             "               |_ 7\n"
                             "                  |_ .\n"
                             "                  |_ 8\n"
                             "                     |_ .\n"
                             "                     |_ 10\n"
                             "                        |_ .\n"
                             "                        |_ 11\n"
                             "                           |_ .\n"
                             "                           |_ 12\n");
    }
}

TEST_CASE("balance", "[bst]") {
    bst<int> tree;
    bst<double> dTree;

    SECTION("balance d'un arbre binaire gauche") {
        for (int i : {8, 4, 1, 2, 3})
            tree.insert(i);
        tree.balance();
        ostringstream oss;
        tree.display_indented(oss);
        REQUIRE(oss.str() == "3\n"
                             "|_ 1\n"
                             "|  |_ .\n"
                             "|  |_ 2\n"
                             "|_ 4\n"
                             "   |_ .\n"
                             "   |_ 8\n");
    }

    SECTION("balance d'un arbre binaire gauche double") {
        for (double i : {8.1, 4.2, 1.3, 2.4, 3.5})
            dTree.insert(i);
        dTree.balance();
        ostringstream oss;
        dTree.display_indented(oss);
        REQUIRE(oss.str() == "3.500000\n"
                             "|_ 1.300000\n"
                             "|  |_ .\n"
                             "|  |_ 2.400000\n"
                             "|_ 4.200000\n"
                             "   |_ .\n"
                             "   |_ 8.100000\n");
    }

    SECTION("arbre de la vidéo 5.14") {
        for (int i = 1; i <= 8; i++)
            tree.insert(i);
        tree.balance();
        ostringstream oss;
        tree.display_indented(oss);
        REQUIRE(oss.str() == "4\n"
                             "|_ 2\n"
                             "|  |_ 1\n"
                             "|  |_ 3\n"
                             "|_ 6\n"
                             "   |_ 5\n"
                             "   |_ 7\n"
                             "      |_ .\n"
                             "      |_ 8\n");
    }

    SECTION("deux balance consécutives") {
        for (int i = 1; i <= 8; i++)
            tree.insert(i);
        tree.balance();
        tree.balance();
        ostringstream oss;
        tree.display_indented(oss);
        REQUIRE(oss.str() == "4\n"
                             "|_ 2\n"
                             "|  |_ 1\n"
                             "|  |_ 3\n"
                             "|_ 6\n"
                             "   |_ 5\n"
                             "   |_ 7\n"
                             "      |_ .\n"
                             "      |_ 8\n");
    }

    SECTION("balance d'un arbre vide") {
        tree.balance();
        ostringstream oss;
        tree.display_indented(oss);
        REQUIRE(oss.str().empty());
    }
}

TEST_CASE( "visit in order", "[bst]") {

    bst<int> tree;
    bst<double> dTree;

    SECTION("Utilisation d'affichage'") {
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            tree.insert(i);
        tree.visit_in_order(affichage<int>);

        REQUIRE(oss_visit_in_order.str() == "1 2 3 4 5 6 7 8 10 11 12 ");
    }

    oss_visit_in_order.str("");

    SECTION("Utilisation d'affichage en double") {
        for (double i : {8.1, 4.2, 1.3, 2.4, 3.5, 6.6, 5.7, 7.8, 11.9, 10.1, 12.2})
            dTree.insert(i);
        dTree.visit_in_order(affichage<double>);

        REQUIRE(oss_visit_in_order.str() == "1.3 2.4 3.5 4.2 5.7 6.6 7.8 8.1 10.1 11.9 12.2 ");
    }
}