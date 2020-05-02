#include "queryengine.h"

void QueryEngine::run(string query)
{
    origQuery = query;

    //search for NOT
    size_t foundNot = query.find("NOT");
    if(foundNot != string::npos)
    {
        string notList = query.substr(foundNot+4,query.length());
        for(int i=0;i<notList.length();i++)
        {
            if(notList.find_first_of(' ') != string::npos)
            {
                string temp = notList.substr(0,notList.find_first_of(' '));
                transform(temp.begin(),temp.end(),temp.begin(),::tolower);
                Porter2Stemmer::trim(temp);
                Porter2Stemmer::stem(temp);
                notWords.push_back(temp);
                notList = notList.substr(notList.find_first_of(' ')+1,notList.length());
            }///end if not out of bounds
        }///end for
        transform(notList.begin(),notList.end(),notList.begin(),::tolower);
        Porter2Stemmer::trim(notList);
        Porter2Stemmer::stem(notList);
        notWords.push_back(notList);
    }///end if found NOT
    query = query.substr(0,foundNot-1);

    //search for AND
    size_t foundAnd = query.find("AND");
    if(foundAnd != string::npos)
    {
        string andList = query.substr(foundAnd+4,query.length());
        for(int i=0;i<andList.length();i++)
        {
            if(andList.find_first_of(' ') != string::npos)
            {
                string temp = andList.substr(0,andList.find_first_of(' '));
                transform(temp.begin(),temp.end(),temp.begin(),::tolower);
                Porter2Stemmer::trim(temp);
                Porter2Stemmer::stem(temp);
                andWords.push_back(temp);
                andList = andList.substr(andList.find_first_of(' ')+1,andList.length());
            }///end if not out of bounds
        }///end for
        transform(andList.begin(),andList.end(),andList.begin(),::tolower);
        Porter2Stemmer::trim(andList);
        Porter2Stemmer::stem(andList);
        andWords.push_back(andList);
    }///end if found AND
    query = query.substr(0,foundAnd-1);

    //search for OR
    size_t foundOr = query.find("OR");
    if(foundOr != string::npos)
    {
        string orList = query.substr(foundOr+3,query.length());
        for(int i=0;i<orList.length();i++)
        {
            if(orList.find_first_of(' ') != string::npos)
            {
                string temp = orList.substr(0,orList.find_first_of(' '));
                transform(temp.begin(),temp.end(),temp.begin(),::tolower);
                Porter2Stemmer::trim(temp);
                Porter2Stemmer::stem(temp);
                orWords.push_back(temp);
                orList = orList.substr(orList.find_first_of(' ')+1,orList.length());
            }///end if not out of bounds
        }///end for
        transform(orList.begin(),orList.end(),orList.begin(),::tolower);
        Porter2Stemmer::trim(orList);
        Porter2Stemmer::stem(orList);
        orWords.push_back(orList);
    }///end if found OR
    query = query.substr(0,foundOr-1);

    //stores leftover single word
    singleWord = query;
    transform(singleWord.begin(),singleWord.end(),singleWord.begin(),::tolower);
    Porter2Stemmer::trim(singleWord);
    Porter2Stemmer::stem(singleWord);

    //chooses which to run
    //searches single word
    if((andWords.empty() && orWords.empty()))
        searchSingle();

    //searches AND words
    if(!andWords.empty())
        searchAnd();

    //searches OR words
    if(!orWords.empty())
        searchOr();
}///end run

void QueryEngine::setDS(DataStructures<WordObject>* x)
{
    words = x;
}///end setAVL

void QueryEngine::searchSingle()
{
    //retrives wordobject from AVL
    //and stores its data
    if(words->contains(singleWord))
    {
        WordObject singleWordObj(singleWord);
        singleWordObj = words->get(singleWord);
        vector<string> files = singleWordObj.getIDs();
        vector<int> freq = singleWordObj.getOccurs();

        //selection sorts by frequencey
        int minIndex;

        // One by one move boundary of unsorted subarray
        for(int i=0;i<freq.size()-1;i++)
        {
            // Find the minimum element in unsorted array
            minIndex = i;
            for(int j=i+1;j<freq.size();j++)
                if (freq[j] < freq[minIndex])
                    minIndex = j;

            // Swap the found minimum element with the first element
            int tempInt = freq[minIndex];
            string tempStr = files[minIndex];

            freq[minIndex] = freq[i];
            files[minIndex] = files[i];

            freq[i] = tempInt;
            files[i] = tempStr;
        }///end for

        //reverses array and outputs it
        reverse(files.begin(),files.end());

        print(files);
    }///end if word exists
}///end searchSingle

void QueryEngine::searchAnd()
{
    //builds vector that combines all AND word data
    vector<string> files;
    vector<int> freq;
    vector<string> newFiles;
    vector<int> newFreq;
    for(int i=0;i<andWords.size();i++)
    {
        //imports the words
        WordObject currentWordObj(andWords[i]);
        currentWordObj = words->get(currentWordObj);
        for(int j=0;j<currentWordObj.getIDs().size();j++)
        {
            files.push_back(currentWordObj.getIDs()[j]);
            freq.push_back(currentWordObj.getOccurs()[j]);
        }///end for j
    }///end for

    //removes non duplicates
    for(int i=0;i<files.size();i++)
    {
        for(int j=0;j<files.size();j++)
        {
            if((files[i]==files[j] && i!=j))
            {
                //adds duplicate file
                newFiles.push_back(files[i]);
                files.erase(files.begin()+j);

                //fixes frequencies
                newFreq.push_back(freq[i]+freq[j]);
                freq[i]+=freq[j];
                freq.erase(freq.begin()+j);
            }///endif duplicate
        }///end for j
    }///end for i

    //selection sorts by frequencey
    int minIndex;

    // One by one move boundary of unsorted subarray
    for(int i=0;i<newFreq.size()-1;i++)
    {
        // Find the minimum element in unsorted array
        minIndex = i;
        for(int j=i+1;j<newFreq.size();j++)
            if (newFreq[j] < newFreq[minIndex])
                minIndex = j;

        // Swap the found minimum element with the first element
        int tempInt = newFreq[minIndex];
        string tempStr = newFiles[minIndex];

        newFreq[minIndex] = newFreq[i];
        newFiles[minIndex] = newFiles[i];

        newFreq[i] = tempInt;
        newFiles[i] = tempStr;
    }///end for

    //reverses array and outputs it
    reverse(newFiles.begin(),newFiles.end());
    print(newFiles);
}///end searchAnd

void QueryEngine::searchOr()
{
    //builds vector that combines all OR word data
    vector<string> files;
    vector<int> freq;
    for(int i=0;i<orWords.size();i++)
    {
        //imports the words
        WordObject currentWordObj(orWords[i]);
        currentWordObj = words->get(currentWordObj);
        for(int j=0;j<currentWordObj.getIDs().size();j++)
        {
            files.push_back(currentWordObj.getIDs()[j]);
            freq.push_back(currentWordObj.getOccurs()[j]);
        }///end for j
    }///end for

    //clears duplicates
    for(int i=0;i<files.size();i++)
    {
        for(int j=0;j<files.size();j++)
        {
            if((files[i]==files[j] && i!=j))
            {
                //removes duplicate file
                files.erase(files.begin()+j);

                //fixes frequencies
                freq[i]+=freq[j];
                freq.erase(freq.begin()+j);
            }///endif duplicate
        }///end for j
    }///end for i

    //selection sorts by frequencey
    int minIndex;

    // One by one move boundary of unsorted subarray
    for(int i=0;i<freq.size()-1;i++)
    {
        // Find the minimum element in unsorted array
        minIndex = i;
        for(int j=i+1;j<freq.size();j++)
            if (freq[j] < freq[minIndex])
                minIndex = j;

        // Swap the found minimum element with the first element
        int tempInt = freq[minIndex];
        string tempStr = files[minIndex];

        freq[minIndex] = freq[i];
        files[minIndex] = files[i];

        freq[i] = tempInt;
        files[i] = tempStr;
    }///end for

    //reverses array and outputs it
    reverse(files.begin(),files.end());
    print(files);
}///end searchOr

void QueryEngine::print(vector<string> toPrint)
{
    //filters NOT words
    //imports notWord files
    vector<string> notFiles;
    for(int i=0;i<notWords.size();i++)
    {
        //imports the words
        WordObject currentWordObj(notWords[i]);
        currentWordObj = words->get(currentWordObj);
        for(int j=0;j<currentWordObj.getIDs().size();j++)
            notFiles.push_back(currentWordObj.getIDs()[j]);
    }///end for

    //removes notWord files
    for(int i=0;i<toPrint.size();i++)
    {
        for(int j=0;j<notFiles.size();j++)
        {
            if(toPrint[i] == notFiles[j])
                toPrint.erase(toPrint.begin()+i);
        }///end for j
    }///end for i

    //prints words
    cout << endl << "Search results: " << endl;
    for(int i=0;i<toPrint.size();i++)
    {
        cout << i+1 << ") " << toPrint[i] << ".json" << endl;
        if(i==14)
            break;
    }///end for
    cout << endl;
}///end print
