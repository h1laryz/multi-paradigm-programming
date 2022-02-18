#include <iostream>
#include <fstream>

int main()
{
    FILE* fp;
    int i = 0, j = 0, countOfWords = 0, maxWordLength = 0;;
    char current;

    fopen_s(&fp, "1.txt", "rb");
    if (fp == NULL) return 0;

    char buffer[10000];
    int bufferLength = 0;

startReading:
    current = fgetc(fp);
    if (current == EOF)
        goto endReading;

    if (current != '\r' && current != '\n')
    {
        if ((current == ' ' && bufferLength != 0 && buffer[bufferLength - 1] != ' ') || current != ' ')
        {
            if (static_cast<int>(current) >= 65 && static_cast<int>(current) <= 90)
                current = static_cast<char>(static_cast<int>(current) + 32);
            buffer[bufferLength] = current;
            bufferLength = bufferLength + 1;
        }
    }
    else if (current == '\n')
    {
        buffer[bufferLength] = ' ';
        bufferLength++;
    }

    goto startReading;
endReading:
    fclose(fp);

    if (bufferLength == 0) return 0;
    if (buffer[bufferLength - 1] == ' ') bufferLength--;

    countOfWords++;
    i = 0;
checkSize:
    if (i == bufferLength) goto endChecking;

    if (buffer[i] == ' ') countOfWords++;

    i++;
    goto checkSize;
endChecking:

    int notSameWords = 0;
    auto arrWords = new std::string[countOfWords];

    i = 0;
    j = 0;

add:
    if (i == bufferLength) goto endAdding;
    if (buffer[i] == ' ' && i != 0)
    {
        j++;
        i++;
        goto add;
    }

    arrWords[j] += buffer[i];

    i++;
    goto add;
endAdding:

    int* count = new int[countOfWords];

    i = 0;

makingToZero:
    if (i == countOfWords) goto endMakingToZero;
    count[i] = 1;
    i++;
    goto makingToZero;
endMakingToZero:

    i = 0;
    j = 0;

deletingSmallWords:
    if (i > countOfWords)
        goto endDeletingSmallWords;
    if (arrWords[i].size() < 3)
        arrWords[i] = "";

    i++;
    goto deletingSmallWords;
endDeletingSmallWords:


    i = 0;
    j = 0;
count:

    if (i >= countOfWords)
    {
        goto endCounting;
    }
    if (arrWords[i] != "")
    {
        int k = i + 1;
    intern:
        if (k >= countOfWords)
            goto endIntern;
        if (arrWords[i] == arrWords[k])
        {
            arrWords[k] = "";
            count[k] = 0;
            count[i]++;
        }
        k++;
        goto intern;
    endIntern:
        int s;
    }
    i++;
    goto count;



endCounting:


    //fopen_s(&fp, "output.txt", "w");
    //fwrite()
    std::string strTemp;
    int temp;

    i = 0;
externalSort:
    if (i >= countOfWords - 1) goto endSort;

    j = 0;
internalSort:
    if (j >= countOfWords - i - 1) goto endInternal;
        
    if (count[j] < count[j + 1])
    {
        strTemp = arrWords[j];
        temp = count[j];
        arrWords[j] = arrWords[j + 1];
        count[j] = count[j + 1];
        arrWords[j + 1] = strTemp;
        count[j + 1] = temp;
    }
        j++;
        goto internalSort;
    endInternal:

    i++;
    goto externalSort;
endSort:

    std::ofstream outFile("output.txt");

    i = 0;
output:
    if (i >= countOfWords) goto endOutput;
    if (arrWords[i] != "")
    {
        outFile << arrWords[i] << " - " << count[i] << std::endl;
    }

    i++;
    goto output;
endOutput:

    outFile.close();
}
