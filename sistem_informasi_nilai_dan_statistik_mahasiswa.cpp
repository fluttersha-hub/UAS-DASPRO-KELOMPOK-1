#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX_MHS = 100;
const int JUMLAH_MK = 3;
string namaMK[JUMLAH_MK] = {"Dasar Pemrograman", "Logika Matematika", "Kalkulus"};

struct Nilai {
    float tugas;
    float uts;
    float uas;
    float nilaiAkhir;
};

struct Mahasiswa {
    string nama;
    string nim;
    Nilai mk[JUMLAH_MK];
    float rataRata;
    string status;
};

// Deklarasi fungsi
void inputData(Mahasiswa mhs[], int &n);
void hitungNilai(Mahasiswa mhs[], int n);
void tampilData(Mahasiswa mhs[], int n);
void tampilStatistik(Mahasiswa mhs[], int n);
void cariMahasiswa(Mahasiswa mhs[], int n, string nimCari);

void garis() {
    cout << "------------------------------------------\n";
}

// Fungsi Input Data
void inputData(Mahasiswa mhs[], int &n) {
    garis();
    int jumlahBaru;
    cout << "Masukkan jumlah mahasiswa: ";
    cin >> jumlahBaru;
    cin.ignore();

    int awal = n;         // simpan jumlah mahasiswa yang sudah ada
    n += jumlahBaru;      // tambahkan jumlah mahasiswa baru ke total

    for (int i = awal; i < n; i++) {
        garis();
        cout << "\nData ke-" << i + 1 << endl;
        cout << "Nama Mahasiswa: ";
        getline(cin, mhs[i].nama);
        cout << "NIM: ";
        getline(cin, mhs[i].nim);

        for (int j = 0; j < JUMLAH_MK; j++) {
            cout << "\nMata Kuliah: " << namaMK[j] << endl;
            cout << "Nilai Tugas: ";
            cin >> mhs[i].mk[j].tugas;
            cout << "Nilai UTS  : ";
            cin >> mhs[i].mk[j].uts;
            cout << "Nilai UAS  : ";
            cin >> mhs[i].mk[j].uas;
        }
        cin.ignore();
    }
}

// Fungsi Hitung Nilai Akhir
void hitungNilai(Mahasiswa mhs[], int n) {
    for (int i = 0; i < n; i++) {
        float total = 0;
        for (int j = 0; j < JUMLAH_MK; j++) {
            mhs[i].mk[j].nilaiAkhir = (mhs[i].mk[j].tugas * 0.3) + (mhs[i].mk[j].uts * 0.3) + (mhs[i].mk[j].uas * 0.4);
            total += mhs[i].mk[j].nilaiAkhir;
        }
        mhs[i].rataRata = total / JUMLAH_MK;
        mhs[i].status = (mhs[i].rataRata >= 60) ? "Lulus" : "Tidak Lulus";
    }
}

// Fungsi Tampilkan Data
void tampilData(Mahasiswa mhs[], int n) {
    garis();
    if (n == 0) {
        cout << "Belum ada data mahasiswa yang diinput.\n";
        garis(); // garis hanya muncul kalau belum ada data
        return;
    }

    cout << "\n=== DATA MAHASISWA ===\n" << "\n";
    cout << left << setw(20) << "Nama"
         << setw(15) << "NIM"
         << setw(15) << "Rata-rata"
         << setw(15) << "Status" << endl;
    cout << string(61, '-') << endl;

    for (int i = 0; i < n; i++) {
        cout << left << setw(20) << mhs[i].nama
             << setw(15) << mhs[i].nim
             << setw(15) << fixed << setprecision(2) << mhs[i].rataRata
             << setw(15) << mhs[i].status << endl;
    }
    cout << "\n";
    garis();
}

// Fungsi Statistik
void tampilStatistik(Mahasiswa mhs[], int n) {
    garis();
    if (n == 0) {
        cout << "Belum ada data mahasiswa yang diinput.";
        return;
    }

    float total = 0, tertinggi = mhs[0].rataRata, terendah = mhs[0].rataRata;
    for (int i = 0; i < n; i++) {
        total += mhs[i].rataRata;
        if (mhs[i].rataRata > tertinggi) tertinggi = mhs[i].rataRata;
        if (mhs[i].rataRata < terendah) terendah = mhs[i].rataRata;
    }

    cout << "\n=== STATISTIK NILAI ===\n" << "\n";
    cout << "Rata-rata Nilai Akhir : " << total / n << endl;
    cout << "Nilai Tertinggi       : " << tertinggi << endl;
    cout << "Nilai Terendah        : " << terendah << endl;
}

// Fungsi Pencarian
void cariMahasiswa(Mahasiswa mhs[], int n, string nimCari) {
    if (n == 0) {
        garis();
        cout << "Belum ada data mahasiswa yang diinput.";
        return;
    }

    bool ditemukan = false;
    for (int i = 0; i < n; i++) {
        if (mhs[i].nim == nimCari) {
            cout << "Data Mahasiswa Ditemukan!\n" << endl;
            cout << "Nama            : " << mhs[i].nama << endl;
            cout << "NIM             : " << mhs[i].nim << endl;
            cout << "Rata-rata Nilai : " << fixed << setprecision(2) << mhs[i].rataRata << endl;
            cout << "Status          : " << mhs[i].status << endl;
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan)
        cout << "Mahasiswa dengan NIM " << nimCari << " tidak ditemukan.\n";
}

int main() {
    Mahasiswa mhs[MAX_MHS];
    int n = 0;
    int pilihan;
    string nimCari;

    do {
        cout << "\n=== SISTEM INFORMASI NILAI MAHASISWA ===\n";
        cout << "1. Input Data Mahasiswa\n";
        cout << "2. Tampilkan Data Mahasiswa\n";
        cout << "3. Statistik Nilai\n";
        cout << "4. Cari Mahasiswa berdasarkan NIM\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                inputData(mhs, n);
                hitungNilai(mhs, n);
                cout << "\n";
                garis();
                break;
            case 2:
                tampilData(mhs, n);
                break;
            case 3:
                tampilStatistik(mhs, n);
                cout << "\n";
                garis();
                break;
            case 4:
            garis();
            if (n == 0) {
                cout << "Belum ada data mahasiswa untuk dicari.\n";
                garis();
                break;
            }

            // Pengulangan pencarian mahasiswa
            {
                string ulang;
                do {
                    cout << "Masukkan NIM yang ingin dicari: ";
                    getline(cin, nimCari);
                    garis();
                    cout << "\n";
                    cariMahasiswa(mhs, n, nimCari);
                    cout << "\n";
                    garis();

                    // Validasi input untuk ulang pencarian
                    do {
                        cout << "\nApakah ingin mencari lagi? (yay/nay): ";
                        cin >> ulang;
                        cout << "\n";
                        cin.ignore();
                        if (ulang != "yay" && ulang != "YAY" && ulang != "nay" && ulang != "NAY") {
                            garis();
                            cout << "\nInput tidak valid! Masukkan hanya 'yay' atau 'nay'.\n";
                            garis();
                        }
                    } while (ulang != "yay" && ulang != "YAY" && ulang != "nay" && ulang != "NAY");

                    garis();
                } while (ulang == "yay" || ulang == "YAY");
            }
                break;

            case 5:
                cout << "Keluar dari program.\n";
                break;
            default:
                garis();
                cout << "Pilihan tidak valid!\n";
                garis();
        }
    } while (pilihan != 5);

    return 0;
}


// tambah fitur hapus data Mahasiswa
// fitur edit data mahasiswa juga boleh
