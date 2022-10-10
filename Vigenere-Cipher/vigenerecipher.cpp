#include<bits/stdc++.h>
using namespace std;
 
string generateKey(string pt, string key){
    int k = pt.size();
 
    for (int i = 0; ; i++){
        if (k == i)
            i = 0;
        if (key.size() == pt.size())
            break;
        key.push_back(key[i]);
    }
    return key;
}

string encryption(string pt, string key){
    string cipher_text;
    for (int i = 0; i < pt.size(); i++){

        char k = (pt[i] + key[i]) %26;

        k += 'A';
        cipher_text.push_back(k);
    }
    return cipher_text;
}

string decryption(string cipher_text, string key){
    string orig_text;
 
    for (int i = 0 ; i < cipher_text.size(); i++){
        char k = (cipher_text[i] - key[i] + 26) %26;
 
        k += 'A';
        orig_text.push_back(k);
        }

        return orig_text;
    }
    
void input(string &str,string &keyword){
    cout << "\n!!! NOTICE : GUNAKAN UPPERCASE !!!";
    cout << "\nMasukan teks : ";
    cin >> str;
    cout << "Masukan Kunci : ";
    cin >> keyword;
    cout << "\nTeks awal : " << str;
    cout << "\nKey : " << keyword << "\n";
}

int main(){
    string str;
    string keyword;
    int opsi;

    cout << "PROGRAM VIGENERE CIPHER" << endl;
    cout << "1. Enkripsi\n2. Dekripsi" << endl;
    cout << "Pilihan : ";
    cin >> opsi;
    
    if (opsi == 1){
        input(str,keyword);
        string key = generateKey(str, keyword);
    	string cipher_text = encryption(str, key);
    	cout << "Teks terenkripsi : " << cipher_text << "\n"; 
    } else if (opsi == 2){
        input(str,keyword);
        string key = generateKey(str, keyword);
        cout << "Teks terdekripsi : "<< decryption(str, key);
    } else {
        cout << "Input Salah! Silahkan Ulangi Kembali!" << endl;
        exit(1);
    } 
}
