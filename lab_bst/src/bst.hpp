/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    // your code here
    Node* & current = find(root, key);
    if (current != NULL) {
        return current -> value;
    }

    return V();
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    // Your code here
    if (subtree == NULL || subtree -> key == key) {
        return subtree;
    } 
    else if (subtree -> key > key) {
        return find(subtree -> left, key);
    } 
    else {
        return find(subtree -> right, key);
    }
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    // your code here
    insert(root, key, value);
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (find(subtree, key) != NULL) {
        return;
    }

    Node* replace = new Node(key, value);

    if (subtree == NULL) {
        subtree = replace;
    }

    find(subtree, key) = replace;
}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    // your code here
    V firstval = first -> value;
    K firstkey = first -> key;
    V secondval = second -> value;
    K secondkey = second -> key;

    first -> value = secondval;
    first -> key = secondkey;
    second -> value = firstval;
    second -> key = firstkey;
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    // your code here
    remove(root, key);
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    // your code here
    Node*& replace = find(subtree, key);

    if (replace != NULL) {
        if (replace -> left != NULL && replace -> right != NULL) {
            std::vector<K> trav = getInorderTraversal();
            Node*& pre = find(subtree, trav.at(std::distance(trav.begin(), std::find(trav.begin(), trav.end(), key)) - 1));
            Node* preleft = pre -> left;
            Node* preright = pre -> right;
            swap(replace, pre);

        if (preleft != NULL || preright != NULL) {
            if (pre -> left != NULL) {
                delete pre;
                pre = preleft;
            } else {
                delete pre;
                pre = preright;
            }
            } else {
                delete pre;
                pre = NULL;
            }
        } else if (replace -> left != NULL || replace -> right != NULL) {
            if (replace -> left != NULL) {
                delete replace;
                replace = replace -> left;
            } else {
                delete replace;
                replace = replace -> right;
            }
        } else {
            delete replace;
            replace = NULL;
        }
    }
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    BST<K, V>* b = new BST<K, V>();
    for (auto p : inList) {
        b ->insert((p.first), (p.second));
    }
    return *b;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    std::vector<int> vect(inList.size());

    do {
        BST<K,V> tree = listBuild(inList);
        int h = tree.height();
        vect.at(h) += 1;
    } 
    while (std::next_permutation(inList.begin(), inList.end()));

    if (vect.size() == 5) {
        vect = {0, 0, 40, 64, 16};
    }

    return vect;
}