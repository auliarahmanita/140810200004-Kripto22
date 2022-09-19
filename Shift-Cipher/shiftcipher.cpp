/*
Praktikum Kriptografi - Program Shift Cipher
Aulia Rahmanita 
140810200004
Kelas B
*/

#include <iostream>
#include <string.h>
using namespace std;

int main(){
    char ptext[50];
    char pil;
    int key, opsi, length;

    cout << "PROGRAM SHIFT CIPHER" << endl;

    cout << "Input Plaintext : ";
    cin.getline(ptext,50);

    cout << "Input Key : ";
    cin >> key;

    length = strlen(ptext);

    cout << "\nOPSI : \n1. Enkripsi\n2. Dekripsi\n";
    cout << "Pilih : ";
    cin >> opsi;

    if(opsi==1){
        char ctext;
        for(int i=0; ptext[i] != '\0'; i++){
            ctext = ptext[i];

            if(ctext >= 'a' && ctext <= 'z'){
                ctext = ctext + key;
                if(ctext > 'z'){
                    ctext = ctext - 'z' + 'a' - 1;
                }
                ptext[i] = ctext;
            }
        
     else if (ctext >= 'A' && ctext <= 'Z'){
        ctext = ctext + key;
        if (ctext > 'Z'){
            ctext = ctext - 'Z' + 'A' - 1;
        }
        ptext[i] = ctext;
        }
    }
    printf("\nEnkripsi Plaintext : %s", ptext);

    } else if(opsi==2){
        char ctext;
        for (int i = 0; ptext[i] != '\0'; ++i){
            ctext = ptext[i];
            if(ctext >= 'a' && ctext <= 'z'){
                ctext = ctext - key;
                if(ctext < 'a'){
                    ctext = ctext + 'z' - 'a' + 1;
                }
                ptext[i] = ctext;
            }

            else if(ctext >= 'A' && ctext <= 'Z'){
                ctext = ctext - key;
                if(ctext < 'A'){
                    ctext = ctext + 'Z' - 'A' + 1;
                }
                ptext[i] = ctext;
            }
        }
        printf("\nDekripsi Plaintext : %s", ptext);
    } else {
        cout << "\nNomor yang diinput salah! Silahkan ulangi kembali!" << endl;
    }
}