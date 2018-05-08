/*
	Name: Caesar Cipher Hack
	Author: Erick Oliveira
	Date: 07/05/18 21:09
	Description: Brute force caesar cipher hack
*/

//Libraries
#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

//Macros
#define pause system("pause")
#define cls system("cls")
#define SetColorGreen system("color 0a")
#define SCT SetConsoleTitle
#define exit exit(0)
#define MAX_LINE 1000
#define MAX_PAL 50

//Global variable for counts
int attempts;

//Functions
void erro(); //Archive manipulation error
void save(string str); //Writes a possible match at "data.txt"
void separate(string ent); //Tests ever possible key of caesar cipher
void extract_words(); //Extracts every first word of each decoded phrase to "words.txt"
void compare(); //Takes every word from "words.txt" and send to find(string toFind) function
void reset(); //Deletes all temp files
bool find(string toFind); //Receives a word and search for it in the wordlist

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//-------------------------------------------------
//WARNING - SET YOUR LANGUAGE WORDLIST AT LINE 148
//-------------------------------------------------
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void erro()
{
	cout << "\n\nArchive manipulation error\n\n";
	pause;
	exit;
}

void save(string str)
{
	int i, tam = str.length();
	char exp[tam+1];
	
	for (i = 0; i < tam; i++) exp[i] = str[i];
	
	FILE *arq = fopen("data.txt", "a");
	if (!arq) erro();
	
    for (i = 0; i < tam; i++)
    {
    	fprintf(arq, "%c", exp[i]);
	}
	fprintf(arq,"\n");
	fclose(arq);
}

void separate(string ent)
{
	int i, tam, key = 1, j, flag;
	string ent2, str;
	string alf = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
	char c;
	
	while (ent[i])
	{
	    c = ent[i];
	    ent2 += tolower(c);
	    i++;
	}
	ent = ent2;
	
	tam = ent.length();
	
	while (key < 26)
	{
		str.clear();
		
		for (i = 0; i < tam; i++)
		{
			flag = 0;
			for (j = 26; j < alf.length(); j++)
			{
				if (alf[j] == ent[i])
				{
					str += alf[j-key];
					flag = 1; //Is a letter
					break;
				}
			}
			if (flag == 0) str += ent[i]; //If is not a letter, receive same char
		}
		
		printf("KEY %02d ", key);
		cout << str << endl;
		save(str);
		key++;
	}	
}

void extract_words()
{
	int i, j, k;
	char *word, wordToExport[50];
	
	word = (char *) malloc(sizeof(char) * MAX_LINE);
	if (!word) exit;
	
	FILE *arq = fopen("data.txt", "r");
	FILE *words = fopen("words.txt", "a");
	if (!arq || !words) erro();
	
	
	while (fscanf(arq, " %[^\n]s", word) != EOF)
	{
		for (i = 0; i < strlen(word); i++)
		{
			if (word[i] == ' ')
			{
				for (j = 0; j < i; j++) wordToExport[j] = word[j];
				for (k = 0; k <= j-1; k++)  fprintf(words, "%c", wordToExport[k]);
				fprintf(words, "\n");
				break;
			}
		}
	}
	fprintf(words, "\n");
	
	fclose(arq);
	fclose(words);	
}

bool find(string toFind)
{
	int i;
	char pal[MAX_PAL];
	string atual;
	attempts = 0;

	FILE *dic = fopen("brazilian.txt", "r"); //Set your wordlist here
	if (!dic) erro();
	
	while (fscanf(dic, "%s", &pal) != EOF)
	{
		attempts++;
		atual.clear();
		for (i = 0; i < strlen(pal); i++) atual += pal[i];
		if (atual == toFind) return true;
	}
	fclose(dic);
	
	return false;
}

void compare()
{
	char pal[MAX_PAL];
	int  i, cont = 0, key = 1;
	string toFind;
	bool found = false;
	
	FILE *words = fopen("words.txt", "r");
	if (!words) erro();
	
	while (fscanf(words, "%s", &pal) != EOF)
	{
		toFind.clear();
		for (i = 0; i < strlen(pal); i++) toFind += pal[i];
		found = find(toFind);
		if (found == true) break;
		key++;			
	}
	
	if (found == true)
	{
		cout << "Most likely match:\n\n";
		cout << "KEY " << key << endl;
		cout << "It took " << attempts << " attempts\n\n";
	}
	else cout << "Brute force did not succeed\n\n";
	
	fclose(words);	
}

void reset()
{
	system("del data.txt");
	system("del words.txt");
}

int main(void)
{
	SetColorGreen;
	SCT("Caesar Cipher Hack");
	
	string ent;
	
	cout << "Enter the encoded text:\n\n";
	getline(cin,ent);
	
	cls;
	cout << "All possible matches:\n\n";
	separate(ent);
	
	cout << "\n\nBrute force inicialized!\n\n\n";
	
	extract_words();
	compare();
	reset();

	return 0;
}
