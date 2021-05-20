#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <cstring> // for memset
#include <cmath> // for std::size_t
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <iostream>

using std::size_t;
using std::vector;

template <typename Comparable>
class SkipList{
    private:
        size_t maxLevel;
        float fraction; // max level can only
        size_t size; // keeps track of the elements at all levels

        struct Node{
            Comparable data; 
            vector<Node*> next; // each level represents next node. vector size will always be size of maxLevel
            size_t level; // indicates its position in the hierarchy (i.e. incldued in vector<level>)

            Node(size_t vecSize, Comparable value = 0, size_t level=0){ // default constructor
                this->data = value;
                for(size_t x = 0; x < vecSize; x++){
                    next.push_back(nullptr);
                }
                this->level = level;
            }
        };

        Node* head;
        
        size_t randomLevel(){ // randomLevel function taken from references
            float r = (float)rand()/RAND_MAX;
            int lvl = 0;
            while (r < fraction && lvl < maxLevel){
                lvl++;
                r = (float)rand()/RAND_MAX;
            }
            return lvl;
        }

    public:
        SkipList(){
            size = 0;
            maxLevel = 3;
            fraction = 0.5;
            head = new Node(maxLevel);
            for(size_t x = 0; x < maxLevel; x++){
                head->next[x] = nullptr; // initializing all the "levels"
            }
        }

        explicit SkipList(size_t top, float probability=0.5){
            maxLevel = top;
            fraction = probability;
            head = new Node(maxLevel);
            size = 0;
            for(size_t x = 0; x < maxLevel; x++){
                head->next[x] = nullptr; // initializing all the "levels"
            }
        }

        SkipList(const SkipList& toCopy){
            if(this == &toCopy){
                size = 0;
                maxLevel = 3;
                fraction = 0.5;
                head = new Node(maxLevel);
                for(size_t x = 0; x < maxLevel; x++){
                    head->next[x] = nullptr; // initializing all the "levels"
                }
            }else{
                size = 0;
                maxLevel = toCopy.maxLevel;
                fraction = toCopy.fraction;
                head = new Node(maxLevel);
                for(size_t x = 0; x < maxLevel; x++){
                    head->next[x] = nullptr; // initializing all the "levels"
                }
                Node* temp = toCopy.head;
                while(temp->next[0] != nullptr){
                    this->insert(temp->next[0]->data);
                    temp = temp->next[0];
                }
            }
        }

        SkipList& operator=(const SkipList& toCopy){
            if(this == &toCopy){
                size = 0;
                maxLevel = 3;
                fraction = 0.5;
                head = new Node(maxLevel);
                for(size_t x = 0; x < maxLevel; x++){
                    head->next[x] = nullptr; // initializing all the "levels"
                }
            }else{
                Node* temp1 = head->next[0];
                while(temp1 != nullptr){
                    Node* toDelete = temp1;
                    temp1 = temp1->next[0];
                    delete toDelete;
                }
                delete head;
                size = 0;
                maxLevel = toCopy.maxLevel;
                fraction = toCopy.fraction;
                head = new Node(maxLevel);
                for(size_t x = 0; x < maxLevel; x++){
                    head->next[x] = nullptr; // initializing all the "levels"
                }
                Node* temp2 = toCopy.head;
                while(temp2->next[0] != nullptr){
                    this->insert(temp2->next[0]->data);
                    temp2 = temp2->next[0];
                }
            }
            return *this;
        }

        ~SkipList(){
            Node* temp = head->next[0];
            while(temp != nullptr){
                Node* toDelete = temp;
                temp = temp->next[0];
                delete toDelete;
            }
            delete head;
        }

        void printLayer(size_t x, std::ostream& os=std::cout){ // utility function used for debugging
            Node* temp = head;
            while(temp->next[x] != nullptr){
                os << temp->next[x]->data << " -> ";
                temp = temp->next[x];
            }
            std::cout << "tail\n";
        }

        /*
            Explanation of insert logic:
            curLevel starts off at the max level, and the linked list is iterated through as normal.
            Insert operates under assumption that the list is sorted. 
        */
        bool insert(Comparable value){
            Node* temp = head;
            vector<Node*> updates;
            for(size_t x = 0; x < maxLevel; x++){
                updates.push_back(nullptr);
            }
            size_t curlevel = maxLevel - 1;
            size_t randLevel = randomLevel();
            if(randLevel >= maxLevel){
                randLevel = maxLevel - 1;
            }
            while(curlevel > 0){ // first while loop navigates to the 0th layer skipping as many nodes as possible
                if(temp->next[curlevel] == nullptr){updates[curlevel] = temp; curlevel--;}
                else if(temp->next[curlevel]->data > value){updates[curlevel] = temp; curlevel--;}
                else temp=temp->next[curlevel];
            }
            bool reachedEnd = false;
            while(!reachedEnd){ // second while loop actually traverses to desired location
                if(temp->next[curlevel] == nullptr){updates[curlevel] = temp; reachedEnd = true;}
                else if(temp->next[curlevel]->data >= value){updates[curlevel] = temp; reachedEnd = true;}
                else temp = temp->next[curlevel];
            }
            Node* toInsert = new Node(maxLevel, value, randLevel);

            if(temp->next[curlevel] != nullptr){
                if(temp->next[curlevel]->data == value){
                    return false;
                }
            }

            for(size_t x = 0; x < maxLevel; x++){
                if(x <= randLevel){
                    toInsert->next[x] = updates[x]->next[x];
                    updates[x]->next[x] = toInsert;
                }else{
                    toInsert->next[x] = updates[x]->next[x];
                }
            }
            size++;
            return true;
        }
        
        bool remove(Comparable value){ // remove operates very similar to insert
            Node* temp = head;
            vector<Node*> updates;
            for(size_t x = 0; x < maxLevel; x++){
                updates.push_back(nullptr);
            }
            size_t curlevel = maxLevel - 1;
            while(curlevel > 0){
                if(temp->next[curlevel] == nullptr) curlevel--;
                else if(temp->next[curlevel]->data > value) curlevel--;
                else if(temp->next[curlevel]->data == value) {updates[curlevel] = temp; curlevel--;}
                else temp = temp->next[curlevel];
            }
            bool reachedEnd = false;
            while(!reachedEnd){
                if(temp->next[curlevel] == nullptr) return false;
                else if(temp->next[curlevel]->data > value) return false;
                else if(temp->next[curlevel]->data == value) {updates[curlevel] = temp; reachedEnd = true;}
                else temp = temp->next[curlevel];
            }
            size_t theLevel = temp->next[curlevel]->level;
            Node* toDelete = temp->next[curlevel];
            if(theLevel == maxLevel){
                theLevel--;
            }
            for(size_t x = 0; x <= theLevel; x++){
                    updates[x]->next[x] = toDelete->next[x];
            }
            delete toDelete;
            size--;
            return true;
        }
        
        size_t elements(){
            return size;
        }

        bool contains(Comparable value){
            Node* temp = head;
            size_t curlevel = maxLevel -1;
            while(curlevel > 0){
                if(temp->next[curlevel] == nullptr) curlevel--;
                else if(temp->next[curlevel]->data == value) return true;
                else if(temp->next[curlevel]->data > value) curlevel--;
                else temp = temp->next[curlevel];
            }
            while(temp->next[curlevel] != nullptr){
                if (temp->next[curlevel]->data > value) return false;
                else if(temp->next[curlevel]->data == value) return true;
                else temp = temp->next[curlevel];
            }

            return false;
        }
        
        void printElements(std::ostream& os=std::cout){
            for(size_t x = 0; x < maxLevel; x++){
                std::cout << "LAYER " << x << ": ";
                this->printLayer(x, os);
            }
        }
};

#endif

/*
REFERENCES:
https://www.ics.uci.edu/~pattis/ICS-23/lectures/notes/Skip%20Lists.pdf 
https://www.geeksforgeeks.org/skip-list/
*/
