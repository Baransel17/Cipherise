#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

void processMessage(const int &mode, int shift = 0){

    fstream file, outputfile;
    string input , line;

    if(mode == 1){
        cin.ignore();
        file.open("EncryptedMessage.txt", ios::out);
        if(!file.is_open()){
            cout << "Error! File does not exist." << endl;
            return;
        }

        cout << "Your message (Type 'q' and press enter to finish): ";

        while(true){
            getline(cin, input);

            if(input == "q") break;

            for(auto &ch : input){
                if(ch >= 'A' && ch <= 'Z'){
                    ch = ((ch - 'A' + shift) % 26) + 'A';
                }else if(ch >= 'a' && ch <= 'z'){
                    ch = ((ch - 'a' + shift) % 26) + 'a';
                }
            }
            file << input << endl;
        }
        file.close();
        cout << "\t\tMessage encrypted and saved to 'EncryptedMessage.txt'.\n\n" << endl;
    }
    else if(mode == 2){
        file.open("EncryptedMessage.txt", ios::in);
        outputfile.open("DecryptedMessage.txt", ios::out);

        if(file.is_open() && outputfile.is_open()){
            while(getline(file, line)){
                for(auto& ch : line){
                    if(ch >= 'A' && ch <= 'Z'){
                        ch = ((ch - 'A' - shift + 26) % 26) + 'A'; 
                    }else if (ch >= 'a' && ch <= 'z'){
                        ch = ((ch - 'a' - shift + 26) % 26) + 'a';
                    }
                }
                outputfile << line << endl;
            }
            file.close();
            outputfile.close();
            cout << "\t\tMessage decrypted and saved to 'DecryptedMessage.txt'.\n\n" << endl;
        }else{
            cout << "Error! File cannot be opened." << endl;
        }
    }
    else if(mode == 3){
        file.open("EncryptedMessage.txt", ios::out | ios::trunc);
        outputfile.open("DecryptedMessage.txt", ios::out | ios::trunc);

        if(file.is_open() && outputfile.is_open()){
            cout << "\t\tMessages cleared!" << endl;
        }else{
            cout << "Error! File cannot be opened." << endl;
        }
        file.close();
        outputfile.close();
    }else if(mode == 4){
        cout << "Exiting program..." << endl;
        this_thread::sleep_for(chrono::seconds(3));
    }
}

int main(){

    int shift = 0;
    int mode;

    cout << endl << "\t\t\tEncryption and Decryption\n\n\n";
    cout << "\t\t1 - Encrypt" << endl;
    cout << "\t\t2 - Decrypt" << endl;
    cout << "\t\t3 - Clear messages" << endl;
    cout << "\t\t4 - Exit" << endl;
    cout << "\t\tSelect an option: ";
    cin >> mode;

    processMessage(mode, shift);
    
    return 0;
}