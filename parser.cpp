#include "parser.h"

int Parser::run(string filePath)
{
    //FOR DEMO
    cout << "How many files would you like to index?" << endl;
    int amtToParse;
    cin >> amtToParse;

    //adds a slash at end of file path if needed
    if((filePath[filePath.length()-1]) != '/')
        filePath = filePath + "/";

    cout << "Parsing commencing..." << endl;

    //Sets directory to provided filepath
    DIR* dir = opendir(filePath.c_str());
    struct dirent* ent;

    if(dir == nullptr)
    {
        cout << "Failed to open directory" << endl << endl;
        return -1;
    }///end if directory not found
    //reads every file in the directory
    while((ent = readdir(dir)) != nullptr)
    {
        //opens file and stores ID in an int
        //cout << ent->d_name << endl;
        file = ent->d_name;
        currentFile.open(filePath + file);

        //used for adding IDs to word objs
        file = file.substr(0,file.find_first_of('.'));

        if(!currentFile.is_open() && file.size() > 2)
            cout << "Failed to open file" << endl;

        string opinion;
        while(currentFile.good())
        {
            //ignore everything until "text": " is reached
            getline(currentFile,opinion);

            //removes spaces in begining of string
            if(opinion.size()>2)
                opinion = opinion.substr(opinion.find_first_not_of(" "),opinion.size());

            if(opinion.size() > 2)
                if(opinion.substr(1,4) == "text")
                    fixAndAddWords(opinion.substr(7,opinion.size()));

        }///end while file still contains data
        currentFile.close();
        filesParsed++;

        if(filesParsed==amtToParse)
            break;
    }///end while directory still has files
    closedir(dir);
    cout << "Parsing Complete" << endl << endl;
    return 0;
}///end run

//will take the paragraph, divide into coherent words, and add to AVL
void Parser::fixAndAddWords(string paragraph)
{
    //removes misc characters using ASCII codes
    paragraph = removeMiscChars(paragraph);

    //stems and adds
    stemWords(paragraph);
}///end fixandAddWords

string Parser::removeMiscChars(string paragraph)
{
    unsigned long j = 0;
    for(unsigned long i=0;i<paragraph.size();i++)
    {
        if((paragraph[i] >= 'A' && paragraph[i] <= 'Z') || (paragraph[i] >= 'a' && paragraph[i] <= 'z') || (paragraph[i] == ' '))
        {
            paragraph[j] = paragraph[i];
            j++;
        }///end if
    }///end for
    return paragraph.substr(0,j);
}///end removeMiscChars

void Parser::stemWords(string paragraph)
{
    //makes all characters lowercase
    transform(paragraph.begin(),paragraph.end(),paragraph.begin(),::tolower);

    //stems the words and adds them if they arent a stop word
    if(paragraph.find_first_not_of(" ") == string::npos) {}
    else
    {
        string tempParagraph = paragraph.substr(paragraph.find_first_not_of(" "),paragraph.size());
        while((tempParagraph.find(' ') != string::npos) && tempParagraph.find_first_not_of(' ') != string::npos)
        {
            unsigned long spaceIndex = tempParagraph.find_first_of(" ");
            string temp = tempParagraph.substr(0,spaceIndex);
            //doesnt go through if stopword or shorter than 3 letters
            if((binary_search(stopWords.begin(),stopWords.end(),temp)) || temp.length() < 3){}
            else
            {
                //trims words
                Porter2Stemmer::trim(temp);
                Porter2Stemmer::stem(temp);
                insert(temp);
            }///end else
            tempParagraph = tempParagraph.substr(spaceIndex+1,tempParagraph.size());
            if(tempParagraph.find_first_not_of(" ") != string::npos)
                tempParagraph = tempParagraph.substr(tempParagraph.find_first_not_of(" "),tempParagraph.size());
        }///end while
    }///end else
}///end stemWords

void Parser::setAVL()
{
    words = new AVLTree<WordObject>;
}///end setAVL

void Parser::setHash()
{
    words = new HashTable<WordObject>;
}///end setHash

void Parser::insert(string word)
{
        WordObject wordObj(word,file);
        //tests if word is already in tree
        //if not it gets added
        if(words->contains(wordObj) == true)
        {
            //if the word has been already found in the file
            //the frequency counter will incriment
            //if not, the file will be added to the list
            if(words->get(wordObj).containsID(file) == true)
                words->get(wordObj).incrimentOccurs(file);
            else
                words->get(wordObj).addID(file);
        }///end if contains word
        else
            words->insert(wordObj);
}///end insert

DataStructures<WordObject>* Parser::getDS()
{
    return words;
}//end getDS