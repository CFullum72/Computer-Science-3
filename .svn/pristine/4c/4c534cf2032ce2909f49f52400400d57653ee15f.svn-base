#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include "WordList.hpp"

using std::cout; using std::endl;
int main(int argc, char const *argv[]){
    if (argc != 2){
        cout << "please execute with a single text file" << endl;
        return 0;
    }
    std::ifstream file(argv[1]);
    if(!(file.is_open())) {cout << "was unable to open " << argv[1] << endl; return 0;}

    WordList list;
    string word;

    while (file >> word){
        string final;
        for (int i = 0; i < word.size(); i++){
            char temp = word[i];
            if(isalnum(temp)){
                if(isupper(temp))
                    temp = char(tolower(temp));
                final.append(sizeof(temp), temp);
            }
        }
        list.addWord(final);
    }

    cout <<"the final word list is: \n\n";
    list.print();

    file.close();
    return 0;
}
