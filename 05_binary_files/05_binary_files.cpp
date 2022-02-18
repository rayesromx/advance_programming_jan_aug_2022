// 05_binary_files.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int optionToRun = 10;

void (*functionToRunPtr)();
void createASampleFileUsingOFStream();
void readASampleFileUsingOFStream();
void usingDifferentModesWhenReadingOrWritingAFile();
void validatingIfFileIsOpen();
void writtingAndReadingMultipleLines();
void usingEOFStateFlag();
void usingTellGetAndTellPutPositions();
void usingSeekGetAndSeekPutPositions();
void usingSeekGetAndSeekPutPositionsWithOffset();
void writeBinaryFiles();
void readBinaryFiles();

int main()
{
    switch (optionToRun)
    {
    case 0: functionToRunPtr = createASampleFileUsingOFStream;
        break;
    case 1: functionToRunPtr = readASampleFileUsingOFStream;
        break;
    case 2: functionToRunPtr = usingDifferentModesWhenReadingOrWritingAFile;
        break;
    case 3: functionToRunPtr = validatingIfFileIsOpen;
        break;
    case 4: functionToRunPtr = writtingAndReadingMultipleLines;
        break;
    case 5: functionToRunPtr = usingEOFStateFlag;
        break;
    case 6: functionToRunPtr = usingTellGetAndTellPutPositions;
        break;
    case 7: functionToRunPtr = usingSeekGetAndSeekPutPositions;
        break;
    case 8: functionToRunPtr = usingSeekGetAndSeekPutPositionsWithOffset;
        break;
    case 9: functionToRunPtr = writeBinaryFiles;
        break;
    case 10: functionToRunPtr = readBinaryFiles;
        break;
    }

    functionToRunPtr();
}

void createASampleFileUsingOFStream()
{
    //creamos un stream tipo ofstream
    ofstream myfile;
    //creamos y abrimos el archivo
    myfile.open("example1.txt");
    //escribimos informacion en el archivo
    myfile << "Writing this to a file.\n";
    //finalmente cerramos el archivo
    myfile.close();
}

void readASampleFileUsingOFStream()
{
    //char dato[50];
    string datos;
    //declarando un stream de lectura que se llama myfile
    ifstream myfile;
    myfile.open("example1.txt");
    getline(myfile, datos);
    //myfile >> datos;
    myfile.close();
    cout << datos;
}

void usingDifferentModesWhenReadingOrWritingAFile()
{
    fstream fileWriter;
    fileWriter.open("example2.txt", ios::out);
    fileWriter << "Hello, world.\n";
    fileWriter.close();

    fileWriter.open("example2.txt", ios::out | ios::app);
    fileWriter << "Hello, LMADS!!.\n";
    fileWriter.close();

    fileWriter.open("example2.txt", ios::out | ios::trunc);
    fileWriter << "Hello, LMADS!!.\n";
    fileWriter.close();

    string buffer;
    fstream fileReader;
    fileReader.open("example2.txt", ios::in);
    getline(fileReader,buffer);
    fileReader.close();
    cout << buffer << endl;

    //fstream fileReader;
    fileReader.open("example2.txt", ios::in | ios::ate);
    getline(fileReader, buffer);
    fileReader.close();
    cout << buffer << endl;
}

void validatingIfFileIsOpen()
{
    fstream fileStream;
    fileStream.open("example200.txt", ios::in);
    if (fileStream.is_open())
    {
        /*fileStream << "How is it going?!\n";
        fileStream << "Hello, there!\n";
        fileStream << "What's up?!\n";
        fileStream << "Hi!\n";*/
        fileStream.close();
    }
    else
        cout << "Unable to open file" << endl;

}

void writtingAndReadingMultipleLines()
{
    fstream fileStream;
    int linesToWrite = 10;

    fileStream.open("example4.txt", ios::out);
    for (int i = 0; i < linesToWrite; i++)
    {
        fileStream << "Line #" << i + 1 <<" with a hardcoded text\n";
    }
    fileStream.close();

    string dataLine;
    fileStream.open("example4.txt", ios::in);
    while(getline(fileStream, dataLine))
    {
        cout << dataLine;
    }
    fileStream.close();
}

void usingEOFStateFlag()
{
    fstream fileStream;
    string dataLine;

    fileStream.open("example4.txt", ios::in);
    while (!fileStream.eof())// ! => not
        //!true = false, !false = true
    {
        fileStream >> dataLine;
        cout << dataLine;
    }
    
    fileStream.close();

}

void usingTellGetAndTellPutPositions()
{
    fstream fileStream;
    long tellPutPosition;

    fileStream.open("example5.txt", ios::out);
    fileStream << "abcde";
    tellPutPosition = fileStream.tellp();
    cout << "After storing \"abcde\" the put pointer is on " << tellPutPosition << endl;

    fileStream << "fghij";
    tellPutPosition = fileStream.tellp();
    cout << "After storing \"fghij\" the put pointer is on " << tellPutPosition << endl;
    
    fileStream << "klmno";
    tellPutPosition = fileStream.tellp();
    cout << "After storing \"klmno\" the put pointer is on " << tellPutPosition << endl;
    
    fileStream << "pqrst";
    tellPutPosition = fileStream.tellp();
    cout << "After storing \"pqrst\" the put pointer is on " << tellPutPosition << endl;
    
    fileStream << "uvwxyz";
    tellPutPosition = fileStream.tellp();
    cout << "After storing \"uvwxyz\" the put pointer is on " << tellPutPosition << endl;
    fileStream.close();


    string buffer;
    long tellGetPosition;
    fileStream.open("example5.txt", ios::in);
    tellGetPosition = fileStream.tellg();
    
    cout << "before getline => get position = " << tellGetPosition << endl;
    getline(fileStream, buffer);
    
    tellGetPosition = fileStream.tellg();
    cout << "after getline => get position = " << tellGetPosition << endl;
    cout << "buffer = " << buffer << endl;
    fileStream.close();
}

void usingSeekGetAndSeekPutPositions()
{

    fstream fileStream;
    long tellPutPosition;
    long seekPutPosition;

    fileStream.open("example6.txt", ios::out);
    fileStream << "abcde";
    tellPutPosition = fileStream.tellp();
    cout << "After storing \"abcde\" the put pointer is on " << tellPutPosition << endl;
   
    seekPutPosition = tellPutPosition - 3;
    fileStream.seekp(seekPutPosition);
    //abcde
    fileStream << "fghij";
    //abfghij
    tellPutPosition = fileStream.tellp();
    cout << "After storing \"fghij\" the put pointer is on " << tellPutPosition;
    
    seekPutPosition = tellPutPosition - 2;
    fileStream.seekp(seekPutPosition);
    //abfghij
    fileStream << "klmno";
    //abfghklmno
    tellPutPosition = fileStream.tellp();
    cout << "After storing \"klmno\" the put pointer is on " << tellPutPosition;
    seekPutPosition = tellPutPosition - 1;
    fileStream.seekp(seekPutPosition);

    fileStream << "pqrstuvwxyz";
    tellPutPosition = fileStream.tellp();
    cout << "After storing \"uvwxyz\" the put pointer is on " << tellPutPosition;
    seekPutPosition = tellPutPosition - 3;
    fileStream.seekp(seekPutPosition);

    fileStream << "X Y Z";
    fileStream.close();
}

void usingSeekGetAndSeekPutPositionsWithOffset()
{
    fstream fileStream;
    fileStream.open("example7.txt", ios::out);
    fileStream << "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    fileStream.seekp(1, ios::beg);
    fileStream << "9";//A9CDEFGHIJKLMNOPQRSTUVWXYZ";
    fileStream.seekp(-1, ios::end);
    fileStream << "0";//A9CDEFGHIJKLMNOPQRSTUVWX0Z";
    fileStream.seekp(5, ios::beg);
    fileStream << "_";//A9CD_FGHIJKLMNOPQRSTUVWX0Z";
    fileStream.seekp(5, ios::cur);
    fileStream << "@";//A9CD_FGHIJ@LMNOPQRSTUVWX0Z";
    fileStream.close();

}

struct Address {
    string street;
    string state;
    string country;
    int zipCode;
};

void writeBinaryFiles()
{
    Address addressToWrite;
    addressToWrite.country = "Mexico";
    addressToWrite.state = "Nuevo Leon";
    addressToWrite.street = "Pedro de alba";
    addressToWrite.zipCode = 61532;

    fstream fileStream;
    fileStream.open("example8.bin", ios::out | ios::binary);
    
    if (!fileStream.is_open())
    {
        cout << "Unable to open file" << endl;
        return;
    }
    
    fileStream.write((char*)(&addressToWrite), sizeof(Address));
    fileStream.close();

    //fstream fileStream;
    fileStream.open("example9.bin", ios::out | ios::binary);
    for (int i = 0 ; i < 10; i++)
    {
        fileStream.write((char*)(&addressToWrite), sizeof(Address));
    }
    fileStream.close();

}

void readBinaryFiles()
{
    Address addressToRead;
    fstream fileStream;
    fileStream.open("example8.bin", ios::in | ios::binary);
    fileStream.read((char*)&addressToRead, sizeof(Address));

    cout << addressToRead.country << endl;
    cout << addressToRead.state << endl;
    cout << addressToRead.street << endl;
    cout << addressToRead.zipCode << endl;

    fileStream.close();


    fileStream.open("example9.bin", ios::in | ios::binary | ios::ate);
    if (!fileStream.is_open())
    {
        cout << "Unable to open file" << endl;
        return;
    }
    int totalCharacters = fileStream.tellg();
    if (totalCharacters < 1) {
        cout << "Empty file \n";
        fileStream.close();
        return;
    }

    Address adresses[10];
    for (int i = 0, addressCounter = 0; i < totalCharacters / sizeof(Address); i++) {
        Address* temp = new Address;
        fileStream.seekg(i * sizeof(Address));
        fileStream.read(reinterpret_cast<char*>(temp), sizeof(Address));
        adresses[addressCounter++] = *temp;
        delete reinterpret_cast<char*>(temp);
    }

    fileStream.close();
    for (int i = 0; i < 10; i++)
    {
        cout << "Address #" << i + 1 << endl;
        cout << (*(adresses+i)).country << endl;
        cout << (*(adresses+i)).state << endl;
        cout << (*(adresses+i)).street << endl;
        cout << adresses[i].zipCode << endl;
    }

}
