#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <istream>
using namespace std;

struct LibraryTicket
{
	int number = 0;
	char FIO[30] = "";
	char adress[30] = "";

	LibraryTicket& operator=(const LibraryTicket& b)
	{
		number = b.number;
		strcpy_s(FIO, sizeof(FIO), b.FIO);
		strcpy_s(adress, sizeof(adress), b.adress);
		return *this;
	}
};

ostream& operator<<(ostream& os, const LibraryTicket& v)
{
	os << v.number << '|' << v.FIO << '|' << v.adress << '\n';
	return os;
}

int countRecords(string nameBin) {
	fstream in_file(nameBin, ios::in | ios::binary);
	in_file.seekg(0, ios::end);
	return ((int)in_file.tellg()) / sizeof(LibraryTicket);
}

void createBinary(string name, string nameBin)
{
	ifstream read(name, ios::in);
	if (!read) {
		cout << "Error\n";
		return;
	}
	ofstream write(nameBin, ios::out | ios::binary);
	if (!write) {
		cout << "Error\n";
		return;
	}
	LibraryTicket x;
	while (read >> x.number)
	{
		read.ignore();
		read.getline(x.FIO, 30);
		read.getline(x.adress, 30);
		//cout << x.number << ' ' << x.FIO << ' ' << x.adress << '\n';
		write.write((char*)&x, sizeof(LibraryTicket));
	}
	read.close();
	write.close();
	cout << "Successful\n";
}

void binaryToText(string name, string nameBin) {
	ifstream read(nameBin, ios::in | ios::binary);
	if (!read) {
		cout << "Error1\n";
		return;
	}
	ofstream write(name, ios::out);
	if (!write) {
		cout << "Error2\n";
		return;
	}
	LibraryTicket x;
	while (read.read((char*)&x, sizeof(LibraryTicket)))
	{
		write << x.number << '\n' << x.FIO << '\n' << x.adress << '\n';
	}
	read.close();
	write.close();
	cout << "Successful\n";
}

void showBinary(string name)
{
	ifstream fb(name, ios::in | ios::binary);
	if (!fb.good())
	{
		cout << "Error\n";
		return;
	}
	LibraryTicket x;

	while (fb.read((char*)&x, sizeof(LibraryTicket)))
	{
		cout << x.number << ' ' << x.FIO << ' ' << x.adress << '\n';
	}
	fb.close();
}

//LibraryTicket* randomAccess(int key, string name) {
//	fstream move(name, ios::binary | ios::out | ios::in);
//	LibraryTicket *ptrRecord = new LibraryTicket;
//
//	if (key >= countRecords(name)) {
//		//cout << "No such record\n";
//		return nullptr;
//	}
//
//	move.seekg((key) * sizeof(LibraryTicket), ios::beg);
//	move.read((char*)&*(ptrRecord), sizeof LibraryTicket);
//	return ptrRecord;
//}

int randomAccess(int key, string name, LibraryTicket& placeHolder) {
	fstream move(name, ios::binary | ios::out | ios::in);
	if (!move.good())
	{
		return 1;
	}

	if (key >= countRecords(name)) {
		cout << "No such record to access\n";
		return 1;
	}

	move.seekg((key) * sizeof(LibraryTicket), ios::beg);
	move.read((char*)&placeHolder, sizeof LibraryTicket);
	return 0;
}

//int removeRecord(int key, string name) {
//	fstream move(name, ios::binary | ios::out | ios::in);
//	LibraryTicket r;
//	if (key > countRecords(name) && key) {
//		cout << "No such record\n";
//		return 0;
//	}
//	move.seekg((-1 * sizeof(r)), ios::end);
//	move.read((char*)&r, sizeof(r));
//	move.seekg(sizeof(r) * (key - 1), ios::beg);
//	move.write((char*)&r, sizeof(r));
//	return 1;
//}

int removeBinRecord(int index, string name)
{
	int counter = 0;

	if (index >= countRecords(name) || index < 0) {//record should be in index range and positive
		cout << "Cannot remove non-existent record\n";
		return 1;
	}
	LibraryTicket buffer;

	ifstream read(name, ios::in | ios::binary);//stream to get the original contains
	if (!read.good())
	{
		cout << "Input stream error while trying to remove record\n";
		return 1;
	}
	string buff = name + "copy.bin";
	ofstream write(buff, ios::out | ios::binary);//stream to put the original contains
	if (!write.good())
	{
		cout << "Output stream error while trying to remove record\n";
		return 1;
	}

	while (read.read((char*)&buffer, sizeof(buffer))) {//continuous while there is something to read
		if ((counter == index) && (counter == countRecords(name) - 1))//if target record is at the end
		{
			break;
		}
		else if (counter == index)//else
		{
			read.read((char*)&buffer, sizeof(buffer));
		}
		write.write((char*)&buffer, sizeof(buffer));
		counter++;
	}

	write.close();
	read.close();

	remove(name.c_str());//removing old one
	if (rename(buff.c_str(), name.c_str())) {//giving a new one original name
		std::perror("Error renaming");
		return 1;
	}
	return 0;
}
