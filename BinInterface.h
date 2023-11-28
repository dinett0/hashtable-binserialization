#pragma once

#include "Binary.h"
#include "Hash.h"

class BinInterface
{
    HashTable* HT;
    string fileName;

public:
    BinInterface(HashTable* HT, string fileName) {
        this->HT = HT;
        this->fileName = fileName;
    }

    void binToHash() {
        fstream move(fileName, ios::binary | ios::out | ios::in);
        if (!move.good()) {
            cout << "Cant open the file\n";
        }

        LibraryTicket x;
        int i = 0;

        while (move.read((char*)&x, sizeof(LibraryTicket)))
        {
            HT->insert(x.number, i);
            i++;
        }
    }

    int erase(int key) {
        int check = HT->erase(key);
        if (check < 0)
        {
            return 1;
        }

        removeBinRecord(check, fileName);
        return 0;
    }

    int getRecord(int key, LibraryTicket& x) {
        Ticket* p = HT->get(key);
        if (p == nullptr) {//if record doesnt exist return false
            return 1;
        }
        else
        {
            randomAccess(p->fileIndex, fileName, x);
            return 0;
        }
    }

    void testBin() {
        HashTable HT;
        BinInterface Interface(&HT, "bank.bin");
        LibraryTicket x;
        Interface.binToHash();

        clock_t point1 = clock();
        Interface.getRecord(86665, x);
        cout << x;
        clock_t point2 = clock();
        cout << "Elapsed time for accessing first record: " << fixed << setprecision(10) << double(point2 - point1) / CLOCKS_PER_SEC << '\n';

        point1 = clock();
        Interface.getRecord(61459, x);
        cout << x;
        point2 = clock();
        cout << "Elapsed time for accessing last record: " << fixed << setprecision(10) << double(point2 - point1) / CLOCKS_PER_SEC << '\n';

        point1 = clock();
        Interface.getRecord(18405, x);
        cout << x;
        point2 = clock();
        cout << "Elapsed time for accessing middle record: " << fixed << setprecision(10) << double(point2 - point1) / CLOCKS_PER_SEC << '\n';
    }
};