#ifndef ASD1_LABS_2020_BST_IMPL_H
#define ASD1_LABS_2020_BST_IMPL_H

// fonctions récursives n'ayant pas à connaitre root

#include "bst.h"
#include <stdexcept>

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
    if (root){
        rDetruire(root);
        root = nullptr;
    }
}

template<typename Key>
void bst<Key>::rDetruire(Node<Key> *racine){
    if(racine->left)
        rDetruire(racine->left);

    if(racine->right)
        rDetruire(racine->right);

    delete racine;
}

template<typename Key>
void bst<Key>::insert(Key const& k) {
    insert(root, k);
}

template<typename Key>
void bst<Key>::display_indented(std::ostream &s) const noexcept {
    if(root) {
        s << std::to_string(root->key) << "\n";
        rIndenter(root->left, "|", s, false);
        rIndenter(root->right, "|", s, true);
    }
}

template <typename Key>
std::ostream& operator<<(std::ostream& s, bst<Key> const& t)
{
    bst<Key>::to_stream(t.root, s);
    return s;
}

template<typename Key>
template<typename Fn>
void bst<Key>::croissant(Fn f, Node<Key> *racine) const{
    if (racine){
        croissant(f, racine->left);
        f(racine->key);
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

template<typename Key>
void bst<Key>::rIndenter(Node<Key> *racine, std::string prefixe, std::ostream &s, bool droite) const{

    if (racine) {

        s << prefixe << "_ " << std::to_string(racine->key) << "\n";

        if (droite){
            prefixe.replace(prefixe.end()-1, prefixe.end(), " ");
        }

        prefixe += "  |";

        if(racine->left){
            rIndenter(racine->left, prefixe, s, false);

            if(!racine->right){
                s << prefixe << "_ .\n";
            } else {
                rIndenter(racine->right, prefixe, s, true);
            }
        } else if(racine->right){
            s << prefixe << "_ .\n";
            rIndenter(racine->right, prefixe, s, true);
        }
    } else{
        s << prefixe << "_ .\n";
    }

}

template<typename Key>
Key const &bst<Key>::min() const {

    if(root){
        return racineMin(root)->key;
    }else{
        throw std::exception();
    }
}

template<typename Key>
Node<Key>* bst<Key>::racineMin(Node<Key>* racine) const{
    if (racine->left){
        racineMin(racine->left);
    } else{
        return racine;
    }
}

template<typename Key>
Key const &bst<Key>::max() const {

    if(root){
        return racineMax(root)->key;
    }else{
        throw std::exception();
    }
}

template<typename Key>
Node<Key>* bst<Key>::racineMax(Node<Key>* racine) const{
    if (racine->right){
        racineMax(racine->right);
    } else{
        return racine;
    }
}

template<typename Key>
void bst<Key>::erase_min() {
    if(root) {
        erase(racineMin(root)->key);
    }
    else{
        throw std::exception();
    }
}

template<typename Key>
void bst<Key>::erase_max() {
    if(root) {
        erase(racineMax(root)->key);
    }
    else{
        throw std::exception();
    }
}

template<typename Key>
void bst<Key>::erase(const Key &k) noexcept {
    rEffacer(root, k);
}

template<typename Key>
void bst<Key>::rEffacer(Node<Key> *&racine, const Key &k) noexcept {
    if(!racine){
        return; // k n'est pas là
    } else if(racine->key > k){ // k est sur la gauche de l'arbre
        rEffacer(racine->left, k);
    } else if(racine->key < k){ //k est sur la droite de l'arbre
        rEffacer(racine->right, k);
    } else{ // k est trouvé
        Node<Key>* tmp = racine;
        if (!racine->left){
            racine = racine->right;
        } else if (!racine->right){
            racine = racine->left;
        }
        else{
            Node<Key>* m = sortir_min(racine->right);
            m->right = racine->right;
            m->left = racine->left;
            racine = m;
        }
        delete tmp;
    }
}

template <typename Key>
Node<Key>* bst<Key>::sortir_min(Node<Key>* &racine){
    if (racine->left){
        return sortir_min(racine->left);
    }
    else{
        Node<Key>* tmp = racine;
        racine = racine->right;
        return tmp;
    }
}

template<typename Key>
void bst<Key>::balance() noexcept {
    Node<Key>* L = nullptr;
    size_t n = 0;
    rLineariser(root, L, n);
    root = rArboriser(L, n);
}

template<typename Key>
Node<Key> *bst<Key>::rArboriser(Node<Key> *&racine, size_t n) {
    if (n){
        Node<Key>* rg = rArboriser(racine, (n - 1) / 2);
        Node<Key>* r = racine;
        r->left = rg;
        racine = racine->right;
        r->right = rArboriser(racine, n/2);
        return r;
    }
    return nullptr;
}

template<typename Key>
void bst<Key>::linearize() noexcept {
    Node<Key>* L = nullptr;
    size_t n = 0;
    Node<Key>* tmp = racineMin(root);
    rLineariser(root, L, n);
    root = tmp;
}

template<typename Key>
void bst<Key>::rLineariser(Node<Key>* &racine, Node<Key>* &L, size_t &n) {
    if (racine){
        rLineariser(racine->right,L,n);
        racine->right = L;
        L = racine;
        n++;

        rLineariser(racine->left,L,n);
        racine->left = nullptr;
    }
}

#endif //ASD1_LABS_2020_BST_IMPL_H
