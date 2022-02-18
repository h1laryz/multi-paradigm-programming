#include <iostream>
#include <string>
#include <fstream>

struct Word
{
    std::string word;
    int page = 0;
};

int main()
{
    FILE* fp;
    int i = 0, j = 0, countOfWords = 0;
    char current;
    int currPage = 1;
    int countLinesProccessed = 0;


    fopen_s(&fp, "2.txt", "rb");

    if (fp == NULL) return 0;

    int bufferLength = 0;
    std::string currWord = "";
    std::string allWords;
    int bufferSize = 0;

startReading:
    current = fgetc(fp);
    if (current == EOF)
        goto endReading;

    if (current != ' ' && current != ',' && current != '.' && current != '-' && current != ':' && current != '!' && current != '?'
        && current != '\r' && current != '\n' && current != -30 && current != -128 && current != -99 && current != '_' && current != 'њ' && current != ';')
    {
        currWord += current;
        bufferSize++;
    }
    else
    {
        if (currWord != "" && currWord != "1" && currWord != "0" && currWord != "2" && currWord != "3" && currWord != "4" && currWord != "5"
            && currWord != "6" && currWord != "7" && currWord != "8" && currWord != "9" && current != -30 && current != -128 && current != -99 && current != '_' && current != 'њ')
        {
            allWords += currWord + " ";
            countOfWords++;
            bufferSize++;
            currWord = "";
        }
    }

    goto startReading;
endReading:
    fclose(fp);

    int countOfSymbols = 0;
    Word* arrayWords = new Word[countOfWords];
    i = 0;

    j = 0;
beginAddingToStruct:
    if (j >= allWords.size()) goto endAddingToStruct;


    countOfSymbols++;
    if (allWords[j] == ' ')
    {
        i++;
        j++;
        goto beginAddingToStruct;
    }
    if (static_cast<int>(allWords[j]) >= 65 && static_cast<int>(allWords[j]) <= 90)
        allWords[j] = static_cast<char>(static_cast<int>(allWords[j]) + 32);

    arrayWords[i].word += allWords[j];
    arrayWords[i].page = static_cast<int>(countOfSymbols / 1800) + 1;


    j++;
    goto beginAddingToStruct;
endAddingToStruct:


    int countWord = 0;

    i = 0;
externalDeletingOver100:
    if (i >= countOfWords) goto externalEndDeletingOver100;

    countWord = 0;
    currWord = arrayWords[i].word;

    j = 0;
internalCountSycle:
    if (j >= countOfWords) goto endInternalCountSycle;



    if (currWord == arrayWords[j].word)
    {
        countWord++;
    }

    j++;
    goto internalCountSycle;
endInternalCountSycle:


    if (countWord > 100)
    {
        j = 0;
    internalDeletingSycle:
        if (j >= countOfWords) goto endInternalDeletingSycle;


        if (arrayWords[i].word == currWord)
        {
            arrayWords[i].word = "";
            arrayWords[i].page = 0;
        }

        j++;
        goto internalDeletingSycle;

    }
endInternalDeletingSycle:
    i++;
    goto externalDeletingOver100;
externalEndDeletingOver100:

    i = 0;
deleteWithSamePages:
    if (i >= countOfWords) goto endDeleteWithSamePages;

    currWord = arrayWords[i].word;
    j = 0;
internalDeleteWithSamePages:
    if (j >= countOfWords) goto endInternalDeleteWithSamePages;

    if (currWord == arrayWords[j].word && i != j)
    {
        if (arrayWords[i].page == arrayWords[j].page)
        {
            arrayWords[j].page = 0;
            arrayWords[j].word = "";
        }
    }

    j++;
    goto internalDeleteWithSamePages;
endInternalDeleteWithSamePages:

    i++;
    goto deleteWithSamePages;
endDeleteWithSamePages:

    std::string strTemp;
    int temp;
    i = 0;
externalSort:
    if (i >= countOfWords - 1) goto endSort;

    j = 0;
internalSort:
    if (j >= countOfWords - i - 1) goto endInternal;

    if (arrayWords[j].word > arrayWords[j + 1].word)
    {
        strTemp = arrayWords[j].word;
        temp = arrayWords[j].page;
        arrayWords[j].word = arrayWords[j + 1].word;
        arrayWords[j].page = arrayWords[j + 1].page;
        arrayWords[j + 1].word = strTemp;
        arrayWords[j + 1].page = temp;
    }
    j++;
    goto internalSort;
endInternal:

    i++;
    goto externalSort;
endSort:

    std::ofstream outFile("output.txt");

    i = 0;
outputToFile:
    if (i >= countOfWords) goto endOutputToFile;

    currWord = arrayWords[i].word;

    if (currWord != "")
    {
        outFile << currWord << " - ";

        j = 0;
    internalOutputToFile:
        if (j >= countOfWords) goto internalEndOutputToFile;
        if (currWord == arrayWords[j].word)
        {
            outFile << arrayWords[j].page << " ";
            arrayWords[j].word = "";
        }
        j++;
        goto internalOutputToFile;
    internalEndOutputToFile:

        outFile << std::endl;
    }
    i++;
    goto outputToFile;
endOutputToFile:

    outFile.close();
}

