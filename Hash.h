#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include "Binary.h"
using namespace std;

struct Ticket
{
    int key;
    int fileIndex;
    bool openAddress;
    bool deleted;

    Ticket() {
        key = -1;
        fileIndex = -1;
        openAddress = true;
        deleted = true;
    }
};

ostream& operator<<(ostream& os, const Ticket& v)
{
    os << setw(10) << v.key << '|' << setw(3) << v.fileIndex << '|' << v.openAddress << '|' << v.deleted << '\n';
    return os;
}

class HashTable
{
private:
    Ticket* arr;//dynamic array Tickets
    int capacity;//how much can table contain
    int size;//how much is there present
    const double DEFAULT_LOAD_FACTOR = 0.75;//size / capacity

    int hashFunction(int key) { // maps from key's space to hash space
        return key/* * (key + 3)*/ % capacity;
    }

    void rehash() {
        cout << "\n ***Rehashing Started***\n" << endl;
        //this->display();
        Ticket* buff = arr;//assigning old table to temporary holder

        capacity *= 2;
        size = 0;

        this->arr = new Ticket[capacity];//creating resized table and initializing it with defaults
        for (int i = 0; i < capacity / 2; i++) {//finding occupied buckets and rehashing them
            if (!buff[i].deleted) {
                this->insert(buff[i].key, buff[i].fileIndex);
            }
        }
        cout << "\n ***Rehashing Completed***\n" << endl;
        cout << "After rehashing...\n";
        this->display();
        cout << "Loadfactor: " << (1.0 * size) / capacity << '\n';

        delete[] buff;
    }

public:
    HashTable() {
        capacity = 841459;
        size = 0;
        arr = new Ticket[capacity];
    }

    void insert(int key, int fileIndex) {
        int hash = hashFunction(key);

        while (!arr[hash].deleted) { //while the place is held and we didnt reach starting point
            if (arr[hash].key == key)
            {
                arr[hash].fileIndex = fileIndex;
                return;
            }
            /*cout << "   Collision on the position " << hash << "!" << '\n';*/
            hash++;                  //-> loop across the table
            hash %= capacity; //meaure to prevent crossing table boundaries
        }

        arr[hash].key = key;
        arr[hash].fileIndex = fileIndex;
        arr[hash].openAddress = false;
        arr[hash].deleted = false;
        size++;

        /*cout <<  key << " Inserted on the position " << hash << '\n';*/

        double loadFactor = (1.0 * size) / capacity;
        //cout << loadFactor << '\n';
        if (loadFactor > DEFAULT_LOAD_FACTOR) {
            this->display();
            cout << "LoadFactor: " << loadFactor << '\n';
            rehash();
        }
    }

    Ticket* get(int key)
    {
        int hash = hashFunction(key);

        while (!arr[hash].openAddress)
        {
            if (!arr[hash].deleted && arr[hash].key == key) {
                return &arr[hash];
            }
            hash++;
            hash %= capacity;
        }
        return nullptr;
    }

    int erase(int key) {//returns -1 in case of failure, else returns value
        Ticket* p = get(key);

        if (p == nullptr)
        {
            return -1;
        }
        else
        {
            p->deleted = true;
            //p->key = -1;
            //p->fileIndex = -1;
            size--;
            return p->fileIndex;
        }
    }

    void display() {
        for (size_t i = 0; i < capacity; i++)
        {
            cout << setw(5) << i << '\t' << arr[i];
        }
        cout << '\n';
    }

    void testHeshT() {
        cout << "Inserting 48919...";
        this->insert(48919, 0);
        cout << '\n';
        this->display();
        //
        cout << "Inserting 68979...";
        this->insert(68979, 1);
        cout << '\n';
        this->display();
        //
        cout << "Before rehashing...\n";
        for (size_t i = 2; i < 9; i++)
        {
            this->insert(11110 + i * 2, i);
        }
        cout << '\n';
        this->display();
        //
        cout << "Deleting element with key: 11120\n";
        this->erase(11120);
        this->display();
        //
        cout << "Accessing element with key: 48919\n";
        Ticket* p = this->get(48919);
        cout << *p;
    }
};