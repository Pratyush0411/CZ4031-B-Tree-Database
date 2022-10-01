//
// Created by praty on 10/9/2022.
//
#include "vector"
#include <queue>
#include "../entities/storage.h"
#include "BTree.h"

using namespace std;


int Node::MAXSIZE = 3;

Node::Node(bool isLeaf) {
    this->isLeaf = isLeaf;
    key = new int[MAXSIZE];
    ptr = new Node *[MAXSIZE + 1];
    parent = NULL;
    size = 0;
}

BPTree::BPTree() {
    this->rootNode = NULL;
}

bool Node::hasCapacity() {
    if (this->size < MAXSIZE) {
        return true;
    } else
        return false;
}

void Node::insertIntoLeafNode(int x) {
    if (this->size < MAXSIZE) {
        cout << "Inserting into the leaf node" << endl;
        int i = 0;
        while (x > this->key[i] && i < this->size)
            i++;
        for (int j = this->size; j > i; j--) {
            this->key[j] = this->key[j - 1];
        }
        this->key[i] = x;
        this->size++;
        this->ptr[this->size] = this->ptr[this->size - 1];
        this->ptr[this->size - 1] = NULL;
    }
}

void Node::insertIntoInternal(int x, Node *child) {
    if (this->size < MAXSIZE) {
        cout << "Inserting into the internal node" << endl;

        int i = 0;
        while (x > this->key[i] && i < this->size)
            i++;
        for (int j = this->size; j > i; j--) {
            this->key[j] = this->key[j - 1];
        }
        for (int j = this->size + 1; j > i + 1; j--) {
            this->ptr[j] = this->ptr[j - 1];
        }
        this->key[i] = x;
        this->size++;
        this->ptr[i + 1] = child;
    }
}

bool Node::isLeaf1() const {
    return isLeaf;
}

void Node::setSize(int size) {
    this->size = size;
}

void Node::deleteKeyPtrNode(){
    delete[] this->key;
    delete[] this->ptr;
    delete this;
}

int Node::getKey(int i) const {
    return this->key[i];
}

void Node::setKey(int i, int x) {
    this->key[i] = x;
}

Node *Node::getPtr(int i) const {
    if(this->getSize() < i){
        return NULL;
    }
    return this->ptr[i];
}

void Node::setPtr(int i, Node *ptr) {
    this->ptr[i] = ptr;
}

Node *Node::getParent() const {
    return parent;
}

void Node::setParent(Node *parent) {
    this->parent = parent;
}

int Node::getSize() const {
    return this->size;
}

Node *Node::returnNextNode(int x) {
    if (!this->isLeaf) {
        for (int i = 0; i < this->size; i++) {
            if (x < this->key[i]) {
                return this->ptr[i];
            }
            if (i == this->size - 1) {
                return this->ptr[i + 1];
            }
        }
    }
}

void Node::display() {
    for (int i = 0; i < this->getSize(); i++) {
        cout << this->getKey(i) << " ";
    }
    cout<<"\t";
}

Node *BPTree::searchLeafNode(int x) {
    Node *cursor = this->rootNode;
    while (!cursor->isLeaf1()) {
        cursor = cursor->returnNextNode(x);
    }
    return cursor;
}

Node *BPTree::splitAndReturnNewLeaf(Node *orgNode, int x) {
    Node *newNode = new Node(true);
    int virtualNode[Node::MAXSIZE + 1];

    for (int i = 0; i < Node::MAXSIZE; i++) {
        virtualNode[i] = orgNode->getKey(i);
    }
    int i = 0;
    while (x > virtualNode[i] && i < Node::MAXSIZE)
        i++;
    for (int j = Node::MAXSIZE + 1; j > i; j--) {
        virtualNode[j] = virtualNode[j - 1];
    }
    // inserting x if Node was of size MAX+1
    virtualNode[i] = x;
//    for (int j =0; j <= Node::MAXSIZE; j++)
//        cout << virtualNode[j]<<"\t";
//    cout<<"\n";
    orgNode->setSize((Node::MAXSIZE + 1) / 2);
    newNode->setSize((Node::MAXSIZE + 1) - orgNode->getSize());

    // resetting pointers
    orgNode->setPtr(orgNode->getSize(), newNode);
    newNode->setPtr(newNode->getSize(), orgNode->getPtr(Node::MAXSIZE));
    orgNode->setPtr(Node::MAXSIZE, NULL);

    // changing original leaf keys
    for (i = 0; i < orgNode->getSize(); i++) {
        orgNode->setKey(i, virtualNode[i]);
    }

    int j;
    // changing keys in the new leaf
    for (i = 0, j = orgNode->getSize(); i < newNode->getSize(); i++, j++) {
        newNode->setKey(i, virtualNode[j]);
    }

    return newNode;
}

Node *BPTree::splitAndReturnNewInternal(Node *orgInternal, int x, Node *newChild) {
    Node *newInternal = new Node(false);
    int MAX = Node::MAXSIZE;
    int virtualKey[MAX + 1];
    Node *virtualPointer[MAX + 2];
    for (int i = 0; i < MAX; i++) {
        virtualKey[i] = orgInternal->getKey(i);
    }
    for (int i = 0; i < MAX + 1; i++) {
        virtualPointer[i] = orgInternal->getPtr(i);
    }
    int i, j;
    for (i = 0; i < MAX; i++) {
        if (x < virtualKey[i])
            break;
    }
    for (int j = MAX + 1; j > i; j--) {
        virtualKey[j] = virtualKey[j - 1];
    }
    virtualKey[i] = x;
    for (int j = MAX + 2; j > i + 1; j--) {
        virtualPointer[j] = virtualPointer[j - 1];
    }
    virtualPointer[i + 1] = newChild;
    orgInternal->setSize((MAX / 2));
    newInternal->setSize((MAX) - orgInternal->getSize());

    // orgInternal
    for (i = 0; i < orgInternal->getSize()+1; i++) {
        orgInternal->setKey(i, virtualKey[i]);
    }

    for (i = 0; i < orgInternal->getSize() + 1; i++) {
        orgInternal->setPtr(i, virtualPointer[i]);
    }

    // skipping one key
    j = orgInternal->getSize() + 1;
    for (i = 0; i < newInternal->getSize(); i++) {
        newInternal->setKey(i, virtualKey[j]);
        j++;
    }

    j = orgInternal->getSize() + 1;
    for (i = 0; i < newInternal->getSize() + 1; i++) {
        newInternal->setPtr(i, virtualPointer[j]);
        j++;
    }

    return newInternal;


}

void BPTree::createRootNode(Node *orgNode, Node *newNode, int smallestLB) {

    Node *newRoot = new Node(false);

    newRoot->setKey(0, smallestLB);
    newRoot->setPtr(0, orgNode);
    newRoot->setPtr(1, newNode);
    newRoot->setSize(1);
    orgNode->setParent(newRoot);
    newNode->setParent(newRoot);
    this->rootNode = newRoot;

}

int BPTree::findSmallestLB(Node* startNode){
    Node* cursor = startNode;
    while (!cursor->isLeaf1()) {
        cursor = cursor->getPtr(0);
    }
    return cursor->getKey(0);

}
void BPTree::changeInternalNode(int smallestLB, Node *parent, Node *newChild) {
    if (parent->hasCapacity()) {
        parent->insertIntoInternal(smallestLB, newChild);
        newChild->setParent(parent);
    } else {
        Node *newInternal = this->splitAndReturnNewInternal(parent, smallestLB, newChild);
        newChild->setParent(parent);
        for (int i = 0; i < newInternal->getSize() + 1; i++) {
            Node *child = newInternal->getPtr(i);
            if (child == newChild) {
                newChild->setParent(newInternal);
                break;
            }
        }
        //int smallestLB = parent->getKey(parent->getSize());
        int smallestLB = this->findSmallestLB(newInternal);
        if (this->rootNode == parent) {
            // smallestLb here is a big brain strat to remember
            // we retrieve the node which was skipped while splitting internal nodes
            this->createRootNode(parent, newInternal, smallestLB);

        } else {
            this->changeInternalNode(smallestLB, parent->getParent(), newInternal);
        }

    }
}

void BPTree::insert(int x) {

    if (this->rootNode == NULL) {
        this->rootNode = new Node(true);
        this->rootNode->insertIntoLeafNode(x);
    } else {
        // searching for leaf
        Node *leafNode = this->searchLeafNode(x);

        // if leaf has capacity then add to leaf
        if (leafNode->hasCapacity())
            leafNode->insertIntoLeafNode(x);
        else {
            cout<<"Splitting leaf node for "<< x<< endl;
            Node *newLeaf = this->splitAndReturnNewLeaf(leafNode, x);
            if (leafNode->getParent() == NULL) {
                // create new root
                this->createRootNode(leafNode, newLeaf, newLeaf->getKey(0));
            } else {
                this->changeInternalNode(newLeaf->getKey(0), leafNode->getParent(), newLeaf);
            }
        }

    }

}

/*
void BPTree::removeIntNode(Node* cursor){
    int MAX = Node::MAXSIZE;
    Node *parent = cursor->getParent();
    int keyToDel = this->findSmallestLB(cursor);
    int foo=0;
    for(foo=0;foo<=parent->getSize();foo++){
        if(parent->getKey(foo) == keyToDel){
            for(int bar=foo;bar<=parent->getSize();bar++){
                //shift keys
                //parent->setKey(bar)
            }
            return;
        }
    }
}
*/

void BPTree::removeFromInternal(int x, Node* parent, Node* child){
    //if node is root
    int MAX = Node::MAXSIZE;
    //cout<<"x is "<<x<<endl;
    if(this->rootNode == parent){
        if(parent->getSize() == 1){
            //need to move root.
            if(parent->getPtr(0) == child){
                this->rootNode = parent->getPtr(1);
            }
            else if(parent->getPtr(1) == child){
                this->rootNode = parent->getPtr(0);
            }
            parent->deleteKeyPtrNode();
            return;
        }
    }

    int num=0;
    for(num=0;num<=parent->getSize();num++){
        //cout<<"Num count "<<num<<endl;
        if(parent->getKey(num)==x){
            //cout<<"Delete this "<<num<<endl;
            break;
        }
        /*
        if(cursor->getKey(num) == x){
            cout<<"found"<<x<<endl;
            break;
        }
        */
    }

    //cout<<"for2"<<endl;
    //cout<<"size is "<<cursor->getSize()<<endl;
    //cout<<"key 0 is "<<cursor->getKey(0)<<endl;
    //Node* asdf = (cursor->getPtr(1));
    //cout<<"akjsdlfj "<<asdf->getKey(0);
    for(int i=num; i<=parent->getSize()-1; i++){
        //last one is to be removed
        //cout<<"shift key"<<endl;
        parent->setKey(i, parent->getKey(i+1));
        //cout<<i<<endl;
    }
    //cout<<"here"<<endl;
    //num=0;
    for(num=0; num<parent->getSize()+1; num++){
        if(parent->getPtr(num) == child){
            break;
        }
    }

    for(int i=num; i < parent->getSize()+1; i++){
        parent->setPtr(i, parent->getPtr(i+1));
    }
    parent->setSize(parent->getSize()-1);
    if(parent->getSize() >= (MAX/2)){
        return;
    }
    if(parent == this->rootNode){
        return;
    }
    //else, try borrow
    Node *nextParent = parent->getParent();
    int left,right;
    for(int i=0; i<nextParent->getSize()+1; i++){
        if(nextParent->getPtr(i) == parent){
            left = i-1;
            right = i+1;
            break;
        }
    }
    if(left>=0){
        Node *leftNode = nextParent->getPtr(left);
        if(leftNode->getSize()-1 >= (MAX/2)){
            //fit here
            //key
            for(int i=parent->getSize(); i>0; i--){
                parent->setKey(i, parent->getKey(i-1));
            }
            //cursor->setKey(0, parent->getKey(left));
            //parent->setKey(left, leftNode->getKey(leftNode->getSize()-1));
            //ptr
            for(int i=parent->getSize()+1; i>0; i--){
                parent->setPtr(i, parent->getPtr(i-1));
            }
            //settle parent keys/ptrs
            parent->setKey(0, nextParent->getKey(left));
            parent->setPtr(0, leftNode->getPtr(leftNode->getSize()));
            parent->setSize(parent->getSize()+1);
            nextParent->setKey(left, leftNode->getKey(leftNode->getSize()-1));
            leftNode->setSize(leftNode->getSize()-1);
            /*
            cursor->setPtr(0, leftNode->getPtr(leftNode->getSize()));
            cursor->setSize(cursor->getSize()+1);
            leftNode->setSize(leftNode->getSize()-1);
            */
            return;
        }
    }
    else if(right<=nextParent->getSize()){
        Node *rightNode = nextParent->getPtr(right);
        if(rightNode->getSize()-1 >= (MAX/2)){
            //fit here
            //key
            parent->setKey(parent->getSize(), nextParent->getKey(right-1));
            parent->setPtr(parent->getSize()+1, rightNode->getPtr(0));
            parent->setSize(parent->getSize()+1);
            nextParent->setKey(right-1,rightNode->getKey(0));

            for(int i=0; i<rightNode->getSize()-1; i++){
                rightNode->setKey(i, rightNode->getKey(i+1));
            }
            //ptr
            //cursor->setPtr(cursor->getSize()+1, rightNode->getPtr(0));
            //++i?
            for(int i=0; i<rightNode->getSize(); i++){
                rightNode->setPtr(i, rightNode->getPtr(i+1));
            }
            rightNode->setSize(rightNode->getSize()-1);
            return;
        }
    }
    //have to merge
    if(left>=0){
        Node *leftNode = nextParent->getPtr(left);
        leftNode->setKey(leftNode->getSize(), nextParent->getKey(left));
        for(int i=leftNode->getSize()+1, j=0; j<parent->getSize(); i++, j++){
            leftNode->setKey(i, parent->getKey(j));
        }
        for(int i=leftNode->getSize()+1, j=0; j<parent->getSize()+1; i++, j++){
            leftNode->setPtr(i, parent->getPtr(j));
            //cursor->setPtr(j, NULL);
        }
        leftNode->setSize(leftNode->getSize() + parent->getSize() + 1);
        //cursor->setSize(0);
        //recursion
        removeFromInternal(nextParent->getKey(left), nextParent, parent);
        parent->deleteKeyPtrNode();
    }
    else if(right<=nextParent->getSize()){
        Node *rightNode = nextParent->getPtr(right);
        //for key
        //cout<<"Cursor size "<<cursor->getSize()<<endl;
        //cursor->setKey(cursor->getSize(), parent->getKey(right)-1);

        //ensure integrity of rightside key
        //rightNode->setKey(0, findSmallestLB(rightNode));

        parent->setKey(parent->getSize(), nextParent->getKey(right-1));

        //for(int i=cursor->getSize()+1, j=0; j<rightNode->getSize(); j++)
        //cout<<"rightNode0 is "<<rightNode->getKey(0)<<endl;
        //cout<<"rightNode1 is "<<rightNode->getKey(1)<<endl;
        for(int i=parent->getSize()+1, j=0; j<rightNode->getSize(); i++, j++){
            parent->setKey(i, rightNode->getKey(j));
            //cout<<"set key "<<i<<" as "<<rightNode->getKey(j)<<endl;
        }
        //for ptr
        //for(int i=cursor->getSize()+1, j=0; j<rightNode->getSize()+1; j++)
        //cout<<"ptrs"<<endl;
        for(int i=parent->getSize()+1, j=0; j<rightNode->getSize()+1; i++, j++){
            //cout<<"setting ptr "<<i<<" as "<<rightNode->getKey(j)<<endl;
            parent->setPtr(i, rightNode->getPtr(j));
            //rightNode->setPtr(j, NULL);
        }
        parent->setSize(parent->getSize()+rightNode->getSize()+1);
        //rightNode->setSize(0);
        //recursively del.
        removeFromInternal(parent->getKey(right-1), nextParent, rightNode);
        rightNode->deleteKeyPtrNode();
    }
}


void BPTree::remove(int x){
    int MAX = Node::MAXSIZE;
    int deletedNodes =0;
    cout<<"\nRemoving "<< x <<endl;
    if(this->rootNode == NULL){
        //empty
        cout<<"Empty."<<endl;
        return;
    }

    //else,

    //find node
    Node *cursor = this->rootNode;
    Node *parent;
    int left, right;
    while(!cursor->isLeaf1()) {
        parent = cursor;
        for(int i =0; i< cursor->getSize(); i++){
            if(x < cursor->getKey(i)){
                left = i-1;
                right = i+1;
                cursor = cursor->getPtr(i);
                break;
            }
            if(i==(cursor->getSize()-1)){
                left = i;
                right = i+2;
                cursor = cursor->getPtr(i+1);
                break;
            }
        }
    }

    //find key position
    bool f = false;
    int position=0;
    for(position=0;position<cursor->getSize();position++){
        if(cursor->getKey(position) == x){
            f = true;
            break;
        }
    }
    if(!f || (cursor->getKey(position) != x)){
        //key doesn't exist
        cout<<"\nCannot find key"<<endl;
        return;
    }

    for(int i = position; i<cursor->getSize()-1; i++){
        cursor->setKey(i, cursor->getKey(i+1));
        cursor->setPtr(i, cursor->getPtr(i+1));
        //cout<<"key dropped"<<endl;
    }
    cursor->setSize( cursor->getSize() - 1 );
    //cout<<"size set"<<endl;

    if(this->rootNode == cursor){
        //empty tree
        if(cursor->getSize()==0){
            //free memory, key,ptr,root
            /*
            delete[] cursor->key;
            delete[] cursor->ptr;
            delete cursor;
            */
            cursor->deleteKeyPtrNode();
            this->rootNode = NULL;
            //rootNode = NULL;
        } else {
            return;
        }
    }
    //Non-root
    else if(cursor->getSize() >= (MAX+1)/2 ){
        // more than min. No further processing
        return;
    } else {
        // need to borrow
        if(left >= 0){
            //check left neighbour
            Node *leftNode = parent->getPtr(left);
            if(leftNode->getSize()-1 >= (MAX+1)/2){
                //borrow from left
                for(int i=cursor->getSize(); i>0; i--){
                    cursor->setKey(i, cursor->getKey(i-1));
                    cursor->setPtr(i, cursor->getPtr(i-1));
                }
                cursor->setKey(0, leftNode->getKey(leftNode->getSize()-1));
                cursor->setPtr(0, leftNode->getPtr(leftNode->getSize()-1));
                cursor->setSize(cursor->getSize()+1);
                leftNode->setSize(leftNode->getSize()-1);
                parent->setKey(left, cursor->getKey(0));
                return;
            }
        }
        else if(right <= parent->getSize()){
            //check right
            Node *rightNode = parent->getPtr(right);
            if(rightNode->getSize()-1 >= (MAX+1)/2){
                //borrow from right
                cursor->setKey(cursor->getSize(), rightNode->getKey(0));
                cursor->setPtr(cursor->getSize(), rightNode->getPtr(0));
                cursor->setSize(cursor->getSize()+1);
                for(int i=0; i<rightNode->getSize(); i++){
                    rightNode->setKey(i, rightNode->getKey(i+1));
                    rightNode->setPtr(i, rightNode->getPtr(i+1));
                }
                rightNode->setSize(rightNode->getSize()-1);
                parent->setKey(right-1, rightNode->getKey(0));
                return;
            }
        }
    }

    //can't borrow, have to merge
    if(left >= 0){
        //merge left
        Node *leftNode = parent->getPtr(left);
        for(int i=leftNode->getSize(), j=0; j<cursor->getSize(); i++, j++){
            leftNode->setKey(i, cursor->getKey(j));
            leftNode->setPtr(i, cursor->getPtr(j));
        }
        leftNode->setSize(leftNode->getSize() + cursor->getSize());
        leftNode->setPtr(MAX,cursor->getPtr(MAX));
        //leftNode->setParent(parent);
        //settle internal nodes
        removeFromInternal(parent->getKey(left), parent, cursor);
        cursor->deleteKeyPtrNode();
    }
    //node is leftmost alr.
    else if(right <= parent->getSize()){
        //merge right
        Node *rightNode = parent->getPtr(right);
        for(int i=cursor->getSize(), j=0; j<rightNode->getSize(); i++, j++){
            cursor->setKey(i, rightNode->getKey(j));
            cursor->setPtr(i, rightNode->getPtr(j));
        }
        cursor->setSize(cursor->getSize() + rightNode->getSize());
        cursor->setPtr(MAX, rightNode->getPtr(MAX));
        //rightNode->getPtr(MAX)? or (last key) aka getSize?
        //settle internal nodes
        removeFromInternal(parent->getKey(right-1), parent, rightNode);
        rightNode->deleteKeyPtrNode();
    }
}

/*
void BPTree::remove1(int x){
    cout<<"Deleting "<<x<<endl;
    int deletedNodes =0;

    //empty
    if(this->rootNode == NULL){
        return;
    } else {
        Node *cursor = this->rootNode;
        Node *parent;
        int left, right;

        //finding node
        while(!cursor->isLeaf1()){
            parent = cursor;
            for(int i=0; i<cursor->getSize(); i++){
                if (x < cursor->getKey(i)){
                    left = i-1;
                    right = i+1;
                    cursor = cursor->getPtr(i);
                    break;
                }
                if(i == cursor->getSize()-1){
                    left = i;
                    right = i+2;
                }
            }

        }
    }


}
*/

void BPTree::display() {

//    if (cursor != NULL) {
//        for (int i = 0; i < cursor->getSize(); i++) {
//            cout << cursor->getKey(i) << " ";
//        }
//        cout << "\n";
//        if (cursor->isLeaf1() != true) {
//            for (int i = 0; i < cursor->getSize() + 1; i++) {
//                display(cursor->getPtr(i));
//            }
//        }
//    }

// BFS printing the tree

    vector<Node *> q;
    q.push_back(rootNode);
    int level = 0;
    while (!q.empty()) {

        cout<<"Level "<<level<<":"<<" ";
        vector<Node*> cpy;
        for (Node *node: q) {
            node->display();
            cpy.push_back(node);
        }
        q.clear();
        for (Node* node:cpy){
            if (!node->isLeaf1()){
                for (int i = 0; i < node->getSize() + 1; i++) {
                    q.push_back(node->getPtr(i));
                }
            }
        }
        level ++;
        cout << "\n";
    }


}

Node *BPTree::search(float x, bool flag, bool printer)
{
    if (rootNode == NULL)
    {
        // Empty tree
        cout <<"Tree is empty\n";
    }
    else
    {
        Node* cursor = rootNode;
        while (cursor->isLeaf1() == false)
        {
            for(int i =0; i<cursor->getSize(); i++)
            {
                if(x < cursor->getKey(i))
                {
                    if(printer == true)
                    {
                        for (int j =0; j<cursor->getSize();j++)
                        {
                            cout << "1: ";
                            cout << cursor->getKey(j) <<" ";
                        }
                        cout << "\n";
                    }
                    cursor = cursor->getPtr(i);
                    break;
                }
                if(i == cursor->getSize()-1)
                {
                    if(printer == true)
                    {
                        for (int j =0; j<cursor->getSize();j++)
                        {
                            cout << "2: ";
                            cout << cursor->getKey(j) <<" ";
                        }
                        cout << "\n";
                    }
                    cursor = cursor->getPtr(i+1);
                    break;
                }
            }
        }
        if (printer == true)
        {
            for(int j = 0; j< cursor->getSize(); j++)
            {
                cout << "3: ";
                cout << cursor->getKey(j) << " ";
            }
            cout << "\n";
        }
        for (int i =0; i< cursor->getSize(); i++)
        {
            if(cursor->getKey(i) == x)
            {
                cout <<"Found key\n";
                cout << "Ptr: " <<cursor->getPtr(i) << "\n";
                cout << "Size:" <<cursor->getSize() << "\n";

            }
            return cursor;
        }
    }
    cout << "Not found\n";
    return nullptr;
}


