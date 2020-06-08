/// \file bst.h
/// \authors Enzo Allemano et Adrien Pegiueron
/// \date 08.06.2020
///
/// \brief \b Laboratoire \b 11
/// \brief Déclare les fonctions de manipulations d'un arbre binaire
///
/// Remarque(s) :
///
/// Compilateur :  MinGW-g++ 6.3.0
#ifndef ASD1_2020_LABO11_BST_H
#define ASD1_2020_LABO11_BST_H

#include <string>
#include <iostream>

template <typename Key> struct Node {
    Key const key;
    Node* left;
    Node* right;
};

template<typename Key> class bst;

template <typename Key> std::ostream& operator<<(std::ostream& s, bst<Key> const& tree);

template<typename Key>
class bst { // binary search tree

    friend std::ostream &operator<<<>(std::ostream &, bst<Key> const &);

    Node<Key> *root;

public:

    bst();
    /**
     * insertion d'un élément dans un arbre
     * @param k clé de l'élément à insérer
     */
    void insert(Key const &k);

    // les fonctions suivantes sont à mettre en oeuvre et à tester.

    bst(bst const &other);               // doit offrir la garantie de base
    bst &operator=(bst const &other);    // doit offrir la garantie forte
    ~bst();                              // doit libérer proprement toute la mémoire
                                         // une définition vide est actuellement fournie pour que le projet compile.
    /**
     * recherche un élément dans l'arbre
     * @param k clé de l'élément recherché
     * @return true si l'élément est dans le tableaux, false sinon
     */
    bool contains(Key const& k) const noexcept ; // recherche de l'élément

    // toutes les fonctions se référant à min ou max lèvent une std::exception si l'arbre est vide
    /**
     * renvoie la plus petite valeur de l'arbre
     * @return le minimum
     */
    Key const& min() const ;
    /**
     * renvoie la plus grande valeur de l'arbre
     * @return le maximum
     */
    Key const& max() const ;
    /**
     * efface le minimum
     */
    void erase_min() ;
    /**
     * efface le maximum
     */
    void erase_max() ;

    /**
     * efface un noeud spécifique
     * @param k la clé du noeud à effacer
     */
    void erase(Key const& k) noexcept ;

    /**
     * parcours l'arbre de manière croissante en effectuant une fonction sur les noeuds
     * @tparam Fn
     * @param f fonction à effectuer
     */
    template<typename Fn> void visit_in_order(Fn f) const ; // la fonction f prend un élément de type Key en paramètre
                                                            // elle est appelée pour tous les éléments de l'arbre par
                                                            // ordre croissant.

    // pour la fonction suivante un test vous est fourni et échoue actuellement

    /**
     * affiche l'arbre de manière identée
     * @param s ostream pour l'affichage
     */
    void display_indented(std::ostream &s) const noexcept ;

    // les fonctions suivantes seront expliquées dans la video 5.14
    /**
     * transforme l'arbre en arbre unaire droite de la plus petite valeur à la plus grande
     */
    void linearize() noexcept ;
    /**
     * équilibre l'arbre
     */
    void balance() noexcept ;

private:
    // fonctions récursives utilisées par les fonctions publiques ci-dessus
    // elles sont static car elles n'ont pas besoin d'accéder à l'attribut root.

    static void insert(Node<Key> *&r, Key const &k);
    static void to_stream(Node<Key> *r, std::ostream &s) noexcept;
    template<typename Fn>
    void croissant(Fn f, Node<Key>* racine) const;
    bool rContient(const Key &k, Node<Key>* racine) const noexcept ;
    void rCopier(Node<Key>* racine, Node<Key>* racineCopie);
    void rDetruire(Node<Key> *racine);
    void rIndenter (Node<Key>* racine, std::string prefixe, std::ostream &s, bool droite) const;
    Node<Key>* racineMax(Node<Key>* racine) const;
    Node<Key>* racineMin(Node<Key>* racine) const;
    void rEffacer(Node<Key>* &racine, Key const& k) noexcept ;
    Node<Key>* sortir_min(Node<Key>* &racine);
    Node<Key>* rArboriser(Node<Key>* &racine, size_t n);
    void rLineariser(Node<Key>* &racine,Node<Key>* &L,size_t &n);
};

// toutes les fonctions sont définies dans le fichier inclus ci-dessous

#include "bst_impl.h"

#endif //ASD1_2020_LABO11_BST_H
