#include<bits/stdc++.h>
using namespace std;
#define NO_OF_ALPHABETS (26)
#define INDEX_OF_CHAR(c) ((int)c - (int)'a')
class TrieNode
{
    public:
    TrieNode *childs[NO_OF_ALPHABETS];
    bool WordEnd;
};
TrieNode *getNode(void)
{
    TrieNode *newNode = new TrieNode;
    newNode->WordEnd = false;

    for (int i = 0; i < NO_OF_ALPHABETS; i++)
        newNode->childs[i] = NULL;

    return newNode;
}
void insert(TrieNode *root,  const string key)
{
    TrieNode *pointerCrawl = root;

    for (int levelTrie = 0; levelTrie < key.length(); levelTrie++)
    {
        int index = INDEX_OF_CHAR(key[levelTrie]);
        if (!pointerCrawl->childs[index])
            pointerCrawl->childs[index] = getNode();

        pointerCrawl = pointerCrawl->childs[index];
    }
    pointerCrawl->WordEnd = true;
}
bool search(TrieNode *root, const string key)
{
    int length = key.length();
    TrieNode *pointerCrawl = root;
    for (int levelTrie = 0; levelTrie < length; levelTrie++)
    {
        int index = INDEX_OF_CHAR(key[levelTrie]);

        if (!pointerCrawl->childs[index])
            return false;

        pointerCrawl = pointerCrawl->childs[index];
    }

    return (pointerCrawl != NULL && pointerCrawl->WordEnd);
}
bool isLastNode(TrieNode* root)
{
    for (int i = 0; i < NO_OF_ALPHABETS; i++)
        if (root->childs[i])
            return 0;
    return 1;
}

void suggestions(TrieNode* root, string currPrefix)
{

    if (root->WordEnd)
    {
        cout << currPrefix;
        cout << endl;
    }

    if (isLastNode(root))
        return;

    for (int i = 0; i < NO_OF_ALPHABETS; i++)
    {
        if (root->childs[i])
        {
            currPrefix.push_back(97 + i);
            suggestions(root->childs[i], currPrefix);
            currPrefix.pop_back();
        }
    }
}

int printAutoSuggestions(TrieNode* root, const string query)
{
    TrieNode* pointerCrawl = root;
    int levelTrie;
    int n = query.length();
    for (levelTrie = 0; levelTrie < n; levelTrie++)
    {
        int index = INDEX_OF_CHAR(query[levelTrie]);
        if (!pointerCrawl->childs[index])
            return 0;

        pointerCrawl = pointerCrawl->childs[index];
    }
    bool isWord = (pointerCrawl->WordEnd == true);
    bool isLast = isLastNode(pointerCrawl);
    if (isWord && isLast)
    {
        cout << query << endl;
        return -1;
    }
    if (!isLast)
    {
        string prefix = query;
        suggestions(pointerCrawl, prefix);
        return 1;
    }
}
int main()
{
    TrieNode* root = getNode();
    int n;
    string s,s1;
    // cout<<"Enter the number of strings you want to store: ";
    // cin>>n;
    //
    // for(int i=0;i<n;i++){
    //     cin>>s;
    //     insert(root, s);
    // }
    ifstream file;
    file.open("words.txt");
    while(file >> s){
        insert(root,s);
    }
    cout<<"\nEnter the prefix of the string you want to search:";
    cin>>s1;
    transform(s1.begin(), s1.end(), s1.begin(), ::tolower);//lower
    int comp = printAutoSuggestions(root, s1);
    if (comp == -1)
        cout << "No other strings found with this prefix\n";

    else if (comp == 0)
        cout << "No string found with this prefix\n";

    return 0;
}
