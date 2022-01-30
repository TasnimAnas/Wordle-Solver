#include <bits/stdc++.h>
using namespace std;

bool contain(string str, char ch)
{
    for (auto it : str)
        if (it == ch)
            return true;
    return false;
}

bool containAtPlace(string str, char ch, int place)
{
    if (str[place] == ch)
        return true;
    return false;
}

bool valid(string &str)
{
    for (int i = 0; i < 5; i++)
        str[i] = toupper(str[i]);
    for (int i = 0; i < 5; i++)
        if (str[i] != 'G' and str[i] != 'Y' and str[i] != 'B')
            return false;
    return true;
}

int main()
{
    vector<string> allWords;
    ifstream fin("all_wordle_words.txt");
    while (fin)
    {
        string str;
        fin >> str;
        allWords.push_back(str);
    }
    sort(allWords.begin(), allWords.end());
    allWords.erase(allWords.begin() + 0);
    string tryString = allWords[0];
    string say;
    vector<pair<int, char>> finalPlaces;
    vector<pair<int, char>> finalChars;
    vector<char> wrongChars;
    int ttt = 6;

    while (ttt--)
    {
        cout << "TRY LEFT: " << ttt + 1 << endl;
        cout << "TRY INPUT: " << tryString << endl;
        cout << "ENTER OUTPUT:" << endl
             << "(G for green, Y for yellow, B for grey, ex: GGBYB): ";
        while (true)
        {
            cin >> say;
            if (say.length() != 5 or !valid(say))
                cout << "Invalid input, try again: ";
            else
                break;
        }

        for (int i = 0; i < 5; i++)
        {
            if (say[i] == 'G')
                finalPlaces.push_back(make_pair(i, tryString[i]));
            else if (say[i] == 'Y')
                finalChars.push_back(make_pair(i, tryString[i]));
            else
                wrongChars.push_back(tryString[i]);
        }
        vector<int> earsables;

        for (int i = 0; i < allWords.size(); i++)
        {
            for (auto iit : finalPlaces)
            {
                if (!containAtPlace(allWords[i], iit.second, iit.first))
                {
                    earsables.push_back(i);
                    break;
                }
            }
        }
        for (int i = earsables.size() - 1; i >= 0; i--)
            allWords.erase(allWords.begin() + earsables[i]);
        earsables.clear();

        for (int i = 0; i < allWords.size(); i++)
        {
            for (auto iit : finalChars)
            {
                if (containAtPlace(allWords[i], iit.second, iit.first))
                {
                    earsables.push_back(i);
                    break;
                }
            }
        }
        for (int i = earsables.size() - 1; i >= 0; i--)
            allWords.erase(allWords.begin() + earsables[i]);
        earsables.clear();

        for (int i = 0; i < allWords.size(); i++)
        {
            for (auto it : wrongChars)
            {
                if (contain(allWords[i], it))
                {
                    earsables.push_back(i);
                    break;
                }
            }
        }
        for (int i = earsables.size() - 1; i >= 0; i--)
            allWords.erase(allWords.begin() + earsables[i]);
        earsables.clear();

        for (int i = 0; i < allWords.size(); i++)
        {
            for (auto iit : finalChars)
            {
                if (!contain(allWords[i], iit.second))
                {
                    earsables.push_back(i);
                    break;
                }
            }
        }
        for (int i = earsables.size() - 1; i >= 0; i--)
            allWords.erase(allWords.begin() + earsables[i]);
        earsables.clear();

        tryString = allWords[0];
        cout << endl
             << endl;
    }
}