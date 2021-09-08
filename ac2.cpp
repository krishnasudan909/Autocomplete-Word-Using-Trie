#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
typedef struct trieNode
{
    struct trieNode *children[26];
    bool isEnd;
} trieNode;

 /*
     int *arr1;
     arr1 = malloc(30*sizeof(int));
     int arr2[30];
 */

void insert(trieNode *Root, char *word)
{

    trieNode *temp = Root;

    int len = strlen(word);
    int index ;
    for (int i = 0; i < len; i++)
    {
        index = word[i] - 97;//ascii value of 'a' is 97
        trieNode *curr = temp->children[index];

        if (curr == NULL)
        {
            curr = (trieNode *)malloc(sizeof(trieNode));
            curr->isEnd = 0;

            for (int j = 0; j < 26; j++)
                curr->children[j] = NULL;

        }

        temp->children[index] = curr;
        temp = temp->children[index];
    }

    temp->isEnd = 1;

}

char *append(char *prefix, char ch)
{

    char *str = (char *)malloc(sizeof(char) * (strlen(prefix) + 2));

    int i = 0;
    while (prefix[i] != '\0')
        str[i] = prefix[i++];

    str[i++] = ch;
    str[i] = '\0';

    return str;
}

void print(trieNode *temp, char *prefix)
{
    if (temp->isEnd)
        printf(" %s\n", prefix);


    for (int i = 0; i < 26; i++)
        if (temp->children[i] != NULL)
        {
            char * str = append(prefix, i + 97);
            print(temp->children[i], str);
            free(str);
        }

}

void autocomplete(trieNode *temp, char *prefix)
{

    int len = strlen(prefix);
    for (int i = 0; i < len; i++)
    {
        temp = temp->children[prefix[i] - 97];
        if(temp==NULL)
            break;
    }

    if(temp!=NULL)
        print(temp, prefix);
    else
        printf(" No words found with such prefix....\n");

}

int main()
{
    trieNode root;   //defining root for trie

    //initializing
    root.isEnd = 0;
    for (int i = 0; i < 26; i++)
        root.children[i] = NULL;


    FILE *fp = fopen("Dit.txt", "r");   //reading words from dictionary

    char str[29];

    while (!feof(fp))
    {
        fscanf(fp, "%s", str);   //storing the string in character array
        insert(&root, str);
    }

    fclose(fp);

    char input[29];
    int x=1;
    while (x)
    {
        printf("\n Search word or Press 0 to exit: ");
        printf(">> ");
        scanf("%d", &x);
        if (x != 0)
        {
            scanf("%s", input);
            for(int i=0;input[i]!='\0';i++)
                if(input[i]>'A'&&input[i]<'Z')
                    input[i] = input[i] + 32 ;

            autocomplete(&root, input);
        }
    }

    return 0;
}
