#ifndef PARSER_H
#define PARSER_H

#include "../external-libs/porter2_stemmer.h"
#include <string>
#include <fstream>
#include <dirent.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include "data-structures/AVLTree.h"
#include "data-structures/HashTable.h"

using namespace std;

class Parser
{
public:
    ifstream currentFile;
    vector<string> stopWords = {"","'","''", "a", "able", "about", "above", "abroad", "according", "accordingly", "across", "actually", "adj", "after", "afterwards",
                                "again", "against", "ago", "ahead", "ain't", "all", "allow", "allows", "almost", "alone", "along", "alongside",
                                "already", "also", "although", "always", "am", "amid", "amidst", "among", "amongst", "an", "and", "another",
                                "any", "anybody", "anyhow", "anyone", "anything", "anyway", "anyways", "anywhere", "apart", "appear", "appreciate",
                                "appropriate", "are", "aren't", "around", "as", "aside", "ask", "asking", "associated", "at", "available",
                                "away", "awfully", "back", "backward", "backwards", "be", "became", "because", "become", "becomes", "becoming",
                                "been", "before", "beforehand", "begin", "behind", "being", "believe", "below", "beside", "besides", "best",
                                "better", "between", "beyond", "both", "brief", "but", "by", "came", "can", "cannot", "cant", "can't", "caption",
                                "cause", "causes", "certain", "certainly", "changes", "clearly", "c'mon", "co", "com", "come", "comes",
                                "concerning", "consequently", "consider", "considering", "contain", "containing", "contains", "corresponding",
                                "could", "couldn't", "course", "currently", "dare", "daren't", "definitely", "described", "despite", "did",
                                "didn't", "different", "directly", "do", "does", "doesn't", "doing", "done", "don't", "down", "downwards", "during",
                                "each", "edu", "eight", "eighty", "either", "else", "elsewhere", "end", "ending", "enough", "entirely",
                                "especially", "etc", "even", "ever", "evermore", "every", "everybody", "everyone", "everything", "everywhere",
                                "ex", "exactly", "example", "except", "fairly", "far", "farther", "few", "fewer", "fifth", "first", "five",
                                "followed", "following", "follows", "for", "forever", "former", "formerly", "forth", "forward", "found", "four",
                                "from", "further", "furthermore", "get", "gets", "getting", "given", "gives", "go", "goes", "going", "gone",
                                "got", "gotten", "greetings", "had", "hadn't", "half", "happens", "hardly", "has", "hasn't", "have", "haven't",
                                "having", "he", "he'd", "he'll", "hello", "help", "hence", "her", "here", "hereafter", "hereby", "herein",
                                "here's", "hers", "herself", "he's", "hi", "him", "himself", "his", "hither", "hopefully", "how",
                                "however", "hundred", "i'd", "ie", "if", "ignored", "i'll", "i'm", "immediate", "in",
                                "inc", "indeed", "indicate", "indicated", "indicates", "inner", "inside", "insofar", "instead", "into",
                                "inward", "is", "isn't", "it", "it'd", "it'll", "its", "it's", "itself", "i've", "just", "k", "keep", "keeps",
                                "kept", "know", "known", "knows", "last", "lately", "later", "latter", "latterly", "least", "less", "lest",
                                "let", "let's", "like", "liked", "likely", "likewise", "little", "look", "looking", "looks", "low", "lower",
                                "made", "mainly", "make", "makes", "many", "may", "maybe", "me", "mean", "meantime", "meanwhile",
                                "merely", "might", "mine", "minus", "miss", "more", "moreover", "most", "mostly", "mr", "mrs", "much",
                                "must", "mustn't", "my", "myself", "name", "namely", "near", "nearly", "necessary", "need", "needn't",
                                "needs", "neither", "never", "neverless", "nevertheless", "new", "next", "nine", "ninety", "no",
                                "nobody", "non", "none", "nonetheless", "noone", "no-one", "nor", "normally", "not", "nothing",
                                "novel", "now", "nowhere", "obviously", "of", "off", "often", "oh", "ok", "okay", "old", "on", "once", "one",
                                "ones", "one's", "only", "onto", "opposite", "or", "other", "others", "otherwise", "ought", "oughtn't", "our",
                                "ours", "ourselves", "out", "outside", "over", "overall", "own", "particular", "particularly", "past", "per",
                                "perhaps", "placed", "please", "plus", "possible", "presumably", "probably", "provided", "provides", "que", "quite",
                                "rather", "really", "reasonably", "recent", "recently", "regarding", "regardless", "regards",
                                "relatively", "respectively", "right", "round", "said", "same", "saw", "say", "saying", "says", "second",
                                "secondly", "see", "seeing", "seem", "seemed", "seeming", "seems", "seen", "self", "selves", "sensible", "sent",
                                "serious", "seriously", "seven", "several", "shall", "she", "she'd", "she'll", "she's", "should",
                                "shouldn't", "since", "six", "so", "some", "somebody", "someday", "somehow", "someone", "something", "sometime",
                                "sometimes", "somewhat", "somewhere", "soon", "sorry", "specified", "specify", "specifying", "still", "sub",
                                "such", "sup", "sure", "take", "taken", "taking", "tell", "tends", "than", "thank", "thanks",
                                "that", "that'll", "thats", "that's", "that've", "the", "their", "theirs", "them", "themselves", "then",
                                "there", "thereafter", "thereby", "there'd", "therefore", "therein", "there'll", "there're", "theres", "there's",
                                "there've", "these", "they", "they'd", "they'll", "they're", "they've", "thing", "things", "think",
                                "third", "thirty", "this", "thorough", "thoroughly", "those", "though", "three", "through", "throughout", "thru",
                                "thus", "till", "to", "together", "too", "took", "toward", "towards", "tried", "tries", "truly", "try", "trying",
                                "twice", "two", "under", "underneath", "undoing", "unfortunately", "unless", "unlike", "unlikely",
                                "until", "unto", "up", "upon", "upwards", "us", "use", "used", "useful", "uses", "using", "usually", "value",
                                "various", "versus", "very", "via", "want", "wants", "was", "wasn't", "way", "we", "we'd", "welcome",
                                "well", "we'll", "went", "were", "we're", "weren't", "we've", "what", "whatever", "what'll", "what's", "what've",
                                "when", "whence", "whenever", "where", "whereas", "whereby", "wherein", "where's",
                                "wherever", "whether", "which", "whichever", "while", "whilst", "who", "who'd", "whoever", "whole",
                                "who'll", "whom", "whomever", "who's", "whose", "why", "will", "willing", "wish", "with", "within", "without",
                                "wonder", "won't", "would", "wouldn't", "yes", "yet", "you", "you'd", "you'll", "your", "you're", "yours",
                                "yourself", "yourselves", "you've", "zero"};

    //FUNCTIONS
    int run(string filePath);
    void fixAndAddWords(string paragraph);
    string removeMiscChars(string paragraph);
    void stemWords(string paragraph);
    void setAVL();
    void setHash();
    void insert(string word);
    DataStructures<WordObject>* getDS();


private:
    string filePath;
    string file;
    DataStructures<WordObject>* words;
    int filesParsed = 0;
    int wordsAdded = 0;
    string currAuthor;
};///end parser

#endif // PARSER_H
