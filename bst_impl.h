//
// Created by Olivier Cuisenaire on 23.05.20.
//

#ifndef ASD1_LABS_2020_BST_IMPL_H
#define ASD1_LABS_2020_BST_IMPL_H

// fonctions récursives n'ayant pas à connaitre root

#include "bst.h"

template<typename Key>
void bst<Key>::insert(Node<Key> *&r, Key const &k) {
        if (r == nullptr) {
            r = new Node<Key>{k, nullptr, nullptr};
        } else if (k == r->key) {
            // k already there : do nothing.
        } else if (k < r->key) {
            insert(r->left, k);
        } else { // k > r->key
            insert(r->right, k);
        }
    }

template<typename Key>
void bst<Key>::to_stream(Node<Key> *r, std::ostream &s) noexcept {
    if (r) {
        s << r->key;
        if (r->right or r->left) { // r has children
            s << "(";
            if (r->left) to_stream(r->left, s);
            else s << ".";

            s << ",";

            if (r->right) to_stream(r->right, s);
            else s << ".";

            s << ")";
        }
    }
}

// méthodes de la classe bst

template<typename Key>
bst<Key>::bst() : root(nullptr) {
}

template<typename Key>
bst<Key>::~bst() {
    rDetruire(root);
}

template<typename Key>
void bst<Key>::rDetruire(Node<Key> *racine){
    if (racine)
    {
        rDetruire(racine->left);
        rDetruire(racine->right);
        delete racine;
    }

}

template<typename Key>
void bst<Key>::insert(Key const& k) {
    insert(root, k);
}

template<typename Key>
void bst<Key>::display_indented(std::ostream &s) const noexcept {
    s << "does not work yet obviously";
}

template <typename Key>
std::ostream& operator<<(std::ostream& s, bst<Key> const& t)
{
    bst<Key>::to_stream(t.root, s);
    return s;
}

template<typename Key>
template<typename Fn>
void bst<Key>::croissant(Fn f, Node<Key> *racine) {
    if (racine){
        croissant(f, racine->left);
        f(racine);
        croissant(f, racine->right);
    }
}

template<typename Key>
template<typename Fn>
void bst<Key>::visit_in_order(Fn f) const {
    croissant(f, root);
}

template<typename Key>
bool bst<Key>::contains(const Key &k) const noexcept {
    rContient(k, root);
}

template<typename Key>
bool bst<Key>::rContient(const Key &k, Node<Key>* racine) const noexcept {
    if(!racine) {
        //pas de clé correspondante
        return false;
    } else if(racine->key == k){
        //la clé se trouve là
        return true;
    } else if (k < racine->key){
        //l'élément se trouve dans la partie gauche du sous-arbre
        rContient(k, racine->left);
    } else{
        //l'élément se trouve dans la partie droite du sous-arbre
        rContient(k, racine->right);
    }
}

template<typename Key>
bst<Key>::bst(bst const &other) {
    if(!other.root){
        root = nullptr;
        return;
    }
    root = new Node<Key>{other.root->key, nullptr, nullptr};
    rCopier(root, other.root);
}

template<typename Key>
void bst<Key>::rCopier(Node<Key> *racine, Node<Key> *racineCopie) {
    if(racineCopie->left){
        racine->left = new Node<Key>{racineCopie->left->key, nullptr, nullptr};
        rCopier(racine->left, racineCopie->left);
    }

    if(racineCopie->right){
        racine->right = new Node<Key>{racineCopie->right->key, nullptr, nullptr};
        rCopier(racine->right, racineCopie->right);
    }
}

template<typename Key>
bst<Key> &bst<Key>::operator=(bst const &other) {
    using std::swap;
    bst tmp(other);
    swap(root, tmp.root);
    return *this;
}

#endif //ASD1_LABS_2020_BST_IMPL_H
