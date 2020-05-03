#include "QueryEngine.h"

void QueryEngine::run(string query,char* CLAPath)
{
    argv = CLAPath;
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
    //exists to prevent mixing OR with AUTHOR
    size_t foundAuthor = query.find("AUTHOR");
    size_t foundOr = query.find("OR");
    if(foundOr != string::npos && foundAuthor == string::npos)
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

    //search for AUTHOR
    if(foundAuthor != string::npos)
    {
        string authorList = query.substr(foundAnd+7,query.length());
        for(int i=0;i<authorList.length();i++)
        {
            if(authorList.find_last_of('R') != string::npos)
                author = authorList.substr(authorList.find_last_of('R')+1,authorList.size());
        }///end for
    }///end if found AND
    query = query.substr(0,foundAnd-1);

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

    if(author.length()>0)
        searchAuthor();
}///end run

void QueryEngine::setDS(DataStructures<WordObject>* x)
{
    words = x;
}///end setAVL

void QueryEngine::searchSingle()
{
    //retrives wordobject from datastructur
    //and stores its data
    WordObject singleWordObj(singleWord);
    if(words->contains(singleWordObj))
    {
        singleWordObj = words->get(singleWordObj);
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
    else
        cout << "No results found" << endl;
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

void QueryEngine::searchAuthor()
{
    //retrives wordobject from datastructure
    //and stores its data
    WordObject singleWordObj(singleWord);
    if((words->contains(singleWordObj)) && words->get(singleWordObj).containsAuthor(author))
    {
        singleWordObj = words->get(singleWordObj);
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

    else
        cout << "No results found" << endl;
}//end searchAuthor

void QueryEngine::print(vector<string> toPrint)
{
    fPath = argv;

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

    //prints document titles
    if(toPrint.size() == 0)
        cout << "No results found" << endl;
    else
        {
        cout << endl << "Search results: " << endl;
        for(int i = 0; i < toPrint.size(); i++)
        {
            currFile.open(fPath + "/" + toPrint[i] + ".json");
            if(!currFile.is_open())
                cout << "Couldn't open file" << endl;

            //ignore everything until "text": " is reached
            bool fileOpen = true;
            while(fileOpen)
            {
                string currLine;
                getline(currFile,currLine);

                if(currLine.size()>3)
                {
                    currLine = currLine.substr(currLine.find_first_not_of(" "), currLine.find_last_of(","));

                    if(currLine.substr(1,5) == "title")
                    {
                        cout << i+1 << ")" << currLine.substr(8, currLine.size()-9) << endl;
                        fileOpen = false;
                    }//end if
                }//end if
            }//end while
            currFile.close();

            if(i == 14)
                break;
        }///end for
    }//end else

    string userIn;
    while(true)
    {
        cout << endl << "Which file would you like to look into? (enter '0' to go back)" << endl;
        cin >> userIn;
        if(userIn == "0")
            break;
        if(stoi(userIn) < 0 || stoi(userIn) > 15)
            cout << "Not a valid input" << endl;
        else
        {
            int userNum = stoi(userIn);
            printFile(toPrint[userNum-1]);
        }//end else
    }//end while
}///end print

int QueryEngine::printFile(string file)
{
    currFile.open(fPath + "/" + file + ".json");
    if(!currFile.is_open())
    {
        cout << "Couldn't open file" << endl;
        return -1;
    }//end if

    int numPgs = 0;
    while(true)
    {
        //ignore everything until "text": " is reached
        string currLine;
        getline(currFile,currLine);

        //removes spaces in begining of string
        if(currLine.size()>2)
            currLine = currLine.substr(currLine.find_first_not_of(" "),currLine.size());

        if(currLine.size() > 20)
            if(currLine.substr(1,4) == "text")
            {
                cout << currLine.substr(7, currLine.size()-8) << endl << endl;
                numPgs++;
                if(numPgs >= 3)
                    break;
            }//end if

    }///end while file still contains data
    currFile.close();
}//end printFile
