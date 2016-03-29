#ifndef SKIP_SET_H_INCLUDED
#define SKIP_SET_H_INCLUDED

#include <iostream>
#include <ctime>
#include <cstdlib>

template<typename T, int maxlevel>
struct node {
    T value;
    node *nextNode[maxlevel]  = {nullptr};
}; // node

template<typename T, const int MAXLEVEL=32>
class skip_set {
    private:
        int curLevelSize;
        node <T, MAXLEVEL> *levelNode;
    public:
        // constructor of the class
        skip_set() {
            curLevelSize = 0;
            levelNode = new node <T, MAXLEVEL>;
            std::cout << levelNode->value << " created"<< std::endl;
        } // constructor

        // destrucotor of the class
        ~skip_set() {
            // deletes all levels and nodes
            std::cout << "destructor called" << std::endl;
            node <T, MAXLEVEL> *tempNode = levelNode;
            while (levelNode != nullptr) {
                tempNode = levelNode->nextNode[0];
                std::cout << levelNode->value << " deleted"<< std::endl;
                delete levelNode;
                levelNode = tempNode;
            } // while
        } // destructor

        // returns the size of the skip_set
        int size() const {
            node <T, MAXLEVEL> *countNode = levelNode->nextNode[0];
            int counter = 0;
            while (countNode != nullptr) {
                std::cout << countNode->value << " counted" << std::endl;
                counter++;
                countNode = countNode->nextNode[0];
            } // while
            return counter;
        } // size


        // search a value in the skip_set and
        // return if the value was found
        bool find(T value) {
            // goes through all levels and nodes
            node <T, MAXLEVEL> *findPlace = levelNode;

            for (int i = curLevelSize; i >= 0; i--) {
                while ((findPlace->nextNode[i] != nullptr)         &&
                        (findPlace->nextNode[i]->value < value))   {
                    findPlace = findPlace->nextNode[i];
                } // while
            } // for
            findPlace = findPlace->nextNode[0];
            if (findPlace != nullptr && findPlace->value == value) {
                return true;
            } else {
                return false;
            } // if;
        } // find


        // creates a random level
        // return the level size
        int randomLevel(int maxlevel) {
            int lvl = 0;
            while ((rand()%100 < 80) && (lvl <= maxlevel)) {
                lvl++;
            } // while
            return lvl;
        } // randomLevel


        // insert a value in the skip_set
        void insert(T value) {
            static node <T, MAXLEVEL> *update[MAXLEVEL];
            node <T, MAXLEVEL> *findPlace = levelNode;

            for (int i = curLevelSize; i >= 0; i--) {
                while ((findPlace->nextNode[i] != nullptr)         &&
                        (findPlace->nextNode[i]->value < value))   {
                    findPlace = findPlace->nextNode[i];
                } // while
                update[i] = findPlace;
            } // for
            findPlace = findPlace->nextNode[0];
            if (findPlace != nullptr && findPlace->value == value) {
                findPlace->value = value;
            } else {
                int lvl = randomLevel(MAXLEVEL);
                if (lvl > curLevelSize) {
                    for (int i = curLevelSize + 1; i <= lvl; i++) {
                        update[i] = levelNode;
                    } // for
                    curLevelSize = lvl;
                } // if
                node <T, MAXLEVEL> *newNode = new node <T, MAXLEVEL>;
                newNode->value = value;
                for (int i = 0; i <= curLevelSize; i++) {
                    std::cout << i << " lvl, " << newNode->value << " created"<< std::endl;
                    newNode->nextNode[i] = update[i]->nextNode[i];
                    update[i]->nextNode[i] = newNode;
                } // for
            } // if
        } // insert


        // delete a value in the skip_set and
        // return if it is deleted
        bool erase(T value) {
            static node <T, MAXLEVEL> *update[MAXLEVEL];
            node <T, MAXLEVEL> *findPlace = levelNode;

            for (int i = curLevelSize; i >= 0; i--) {
                while ((findPlace->nextNode[i] != nullptr)       &&
                        (findPlace->nextNode[i]->value < value)) {
                    findPlace = findPlace->nextNode[i];
                } // while
                update[i] = findPlace;
            } // for
            findPlace = findPlace->nextNode[0];
            if (findPlace != nullptr && findPlace->value == value) {
                for (int i = 0; i <= curLevelSize; i++) {
                    if (update[i]->nextNode[i] != findPlace) {
                        break;
                    } // if
                    update[i]->nextNode[i] = findPlace->nextNode[i];
                    std::cout << i << " lvl, " << findPlace->value << " deleted"<< std::endl;
                } // for
                delete findPlace;
                while ((curLevelSize > 0) && (levelNode->nextNode[curLevelSize] = nullptr)) {
                    curLevelSize--;
                } // while
                return true; // value found and deleted
            } // if
            return false; // value not found
        } // erase

}; // skip_set

#endif // SKIP_SET_H_INCLUDED
