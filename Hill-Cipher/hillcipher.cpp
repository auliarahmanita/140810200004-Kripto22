#include <iostream>
#include<bits/stdc++.h>
using namespace std ;
 
int key[3][3] ; //Sebagai kunci global batas ordo matriks
 
int mod26(int x){ //fungsi untuk modulo
    return x >= 0 ? (x%26) : 26-(abs(x)%26) ; 
}
 
// Mencari determinan matriks
int findDet(int m[3][3] , int n){
    int det;
    if(n == 2){ // jika ordo matriks = 2
        det = m[0][0] * m[1][1] - m[0][1]*m[1][0] ;
    } else det = 0 ; // invalid input
    return mod26(det);
}
 
int findDetInverse(int R , int D = 26){ // Mencari invers matriks
// R adalah sisa atau determinan
    int i = 0 ;
    int p[100] = {0,1};
    int q[100] = {0} ; // hasil bagi
 
    while(R!=0){ // jika sisa tidak sama dengan 0
        q[i] = D/R ;
        int oldD = D ;
        D = R ;
        R = oldD%R ;
        if(i>1){
            p[i] = mod26(p[i-2] - p[i-1]*q[i-2]) ;
        }
        i++ ;
    } if (i == 1) return 1;
    else return p[i] = mod26(p[i-2] - p[i-1]*q[i-2]) ;
}

int gcd(int m, int n){
    if (n > m)
        swap(m,n);
    
    do{
        int temp = m % n;
        m = n;
        n = temp;
    } while (n != 0);
    
    return m;
}
 
void multiplyMatrices(int a[1000][3] , int a_rows , int a_cols ,  int b[1000][3] , int b_rows , int b_cols , int res[1000][3]){
    for(int i=0 ; i < a_rows ; i++){
        for(int j=0 ; j < b_cols ; j++){
            for(int k=0 ; k < b_rows ; k++){
                res[i][j] += a[i][k]*b[k][j] ;
            }
            res[i][j] = mod26(res[i][j]) ;
        }
    }
}
void findKey(){
    //deklarasi
    string plainteks,cipherteks;
    int key[2][2],det,detInv,adj[2][2],plainteksInv[2][2],plainMatrix[2][2],cipMatrix[2][2],counter;
    int p,c;
    int transpose[2][2];
    
    //input plainteks
    cout << "Masukkan Plainteks : ";
    cin.ignore();
    getline(cin,plainteks);
    
    //assign plainteks ke plainMatrix
    counter = 0;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            p = toupper(plainteks[counter]) - 65;
            plainMatrix[i][j] = p;
            counter++;
        }
    }
    
    //input cipherteks
    cout << "Masukkan Cipherteks : ";
    getline(cin,cipherteks);
    
    //assign cipherteks ke cipMatrix
    counter = 0;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            c = toupper(cipherteks[counter]) - 65;
            cipMatrix[i][j] = c;
            counter++;
        }
    }
    
    // determinan
    det = (plainMatrix[0][0] * plainMatrix[1][1]) - (plainMatrix[0][1] * plainMatrix[1][0]);
    if(gcd(det,26)==1){
        // inverse dari determinan mod 26
        detInv = findDetInverse(det, 26);
        
        //menghitung adjoin
        adj[0][0] = plainMatrix[1][1];
        adj[0][1] = (-1)*plainMatrix[0][1];
        adj[1][0] = (-1)*plainMatrix[1][0];
        adj[1][1] = plainMatrix[0][0];
        
        //menghitung matriks invers dari plainteks
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                plainteksInv[i][j] = detInv * adj[i][j];
                if(plainteksInv[i][j] < 0){
                    plainteksInv[i][j] = 26 - (abs(plainteksInv[i][j])%26); 
                }else{
                    plainteksInv[i][j] = plainteksInv[i][j];
                    plainteksInv[i][j] = plainteksInv[i][j] % 26;
                }
            } 
        }
        
        //Search key
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                key [i][j] = 0;
                for(int k = 0; k < 2; k++){
                    key [i][j] += (plainteksInv[i][k] * cipMatrix[k][j]);
                }
                key [i][j] %= 26;
            }
        }
        
 
        for (int i = 0; i < 2; i++){
            for (int j = 0; j < 2; j++){
                transpose[j][i] = key[i][j];
            }
        }

        cout << "\nMatriks Kunci : " << endl;
        for(int i = 0; i < 2; i++){
            for (int j = 0; j < 2; j++){
                cout << (transpose[i][j]) << "\t";
            }
            cout <<endl;
        }       
    } else{
        cout << "Determinan tidak relatif " <<endl;
        cout << "Kunci tidak ditemukan!" <<endl<<endl;
    }
 
}
/* Invers = (matriks * det Invers) mod 26 */
/* cari Invers(matrix , order_of_matrix , result_matrix) */
void findInverse(int m[3][3] , int n , int m_inverse[3][3] ){
    int adj[3][3] = {0};
 
    int det = findDet(m , n); // ini menggunakan fungsi findDet(matrix , order_of_matrix)
    int detInverse = findDetInverse(det);
 
    if(n==2){ //jika ordo matrik 2x2
        adj[0][0] = m[1][1];
        adj[1][0] = -m[1][0];
        adj[0][1] = -m[0][1];
        adj[1][1] = m[0][0];
    }
 
    for(int i=0; i<n ; i++){
        for(int j=0; j<n ; j++){
            m_inverse[i][j] = mod26(adj[i][j] * detInverse) ;
        }
    }
}
 
// C = P * K
string encrypt(string ptext, int n){
    int P[1000][3] = {0} ; // plaintext
    int C[1000][3] = {0} ; // cipher text
    int ptextIter = 0  ;
 
    while(ptext.length()%n != 0){
        ptext += "x" ;  // pad extra x, ini digunakan jika plaintext di module dengan matrik tidak sama dengan 0
    }
    int row = (ptext.length())/n; // jumlah baris dalam plaintext
 
    for(int i=0; i<row ; i++){
        for(int j=0; j<n; j++){
            P[i][j] = ptext[ptextIter++]-'a' ;
        }
    }
 
    // multiplyMatrices(mat_a , row_a , col_a , mat_b, row_b, col_b , mat_result)
    multiplyMatrices(P, row , n , key , n , n , C) ;
 
    string ctext = "" ;
    for(int i=0 ; i<row ; i++){
        for(int j=0 ; j<n ;j++){
            ctext += (C[i][j] + 'a');
        }
    }
    return ctext;
}
 
// P = C*K^-1
string decrypt(string ctext, int n){
    int P[1000][3] = {0} ; // plaintext
    int C[1000][3] = {0} ; // cipher text
    int ctextIter = 0 ;
 
    int row = ctext.length()/n; // banyak baris di chipertext
 
    for(int i=0; i<row ; i++){
        for(int j=0; j<n; j++){
            C[i][j] = ctext[ctextIter++]-'a' ;
        }
    }
 
    int k_inverse[3][3] = {0};
    /* findInverse(matrix , order_of_matrix , result_matrix) */
    findInverse(key, n , k_inverse);
 
    /* multiplyMatrices(mat_a , row_a , col_a , mat_b, row_b, col_b , mat_result) */
    multiplyMatrices(C, row , n , k_inverse , n , n , P) ;
 
    string ptext = "" ;
    for(int i = 0 ; i<row ; i++){
        for(int j=0 ; j<n ; j++){
            ptext += (P[i][j] + 'a');
        }
    }
    return ptext ;
}
 
int main(void){
    bool menuActive = true;
    string ptext, ctext;
    int n ;
    int pilih;
 
    while(menuActive){
        cout << "\nPROGRAM HILL CIPHER" <<endl;
        cout << "OPSI : " <<endl;
        cout << "1. ENKRIPSI" <<endl;
        cout << "2. DEKRIPSI" <<endl;
        cout << "3. MENCARI KUNCI" <<endl;
        cout << "4. EXIT" <<endl;
        cout << "PILIHAN : "; cin >> pilih;
        switch(pilih){
            case 1:
                    cout << "\nMasukan pesan untuk dienkripsi : " ;
                    cin >> ptext;
                    cout << "Masukkan ordo matriks (harus 2x2) : ";
                    cin >> n ;
 
                    for(int i=0; i<n; i++){
                        for(int j=0; j<n; j++){
                            cout<<"Masukkan matriks baris-" << j+1 << " kolom-" << i+1 << " : "; 
                            cin >> key[i][j];
                        }
                    }
 
                    cout << "\nPesan sebelum dienkripsi : " << ptext << endl;
 
                    ctext = encrypt(ptext, n) ;
                    cout << "Pesan terenkripsi : " << ctext << endl;
                    break;
            case 2:
                    cout << "\nMasukan pesan untuk didekripsi : " ;
                    cin >> ctext;
                    cout << "Masukkan ordo matriks (harus 2x2) : ";
                    cin >> n ;
 
                    for(int i=0; i<n; i++){
                        for(int j=0; j<n; j++){
                            cout<<"Masukkan matriks baris-" << j+1 << " kolom-" << i+1 << " : "; 
                            cin >> key[i][j];
                        }
                    }
 
                    cout << "\nPesan sebelum didekripsi : " << ctext << endl;
                    cout << "Pesan terdekripsi : " << decrypt(ctext, n)<< endl;
                    break;
            case 3:
                    cout<<endl;
                    findKey();
                    break;
            default:
                    cout << "Anda keluar dari Program" <<endl;
                    return 0;
                    break;
        }
    } 
}