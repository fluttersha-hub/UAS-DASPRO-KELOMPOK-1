#include <iostream>
#include <string>
using namespace std;

const int MAX = 100;

// Array Data mahasiswa
string nama[MAX];
string nim[MAX];
float nilai[MAX][4]; // 0=tugas, 1=UTS, 2=UAS, 3=Nilai Akhir
int jumlah = 0;

// Modul input data
void inputData() {
    cout << "\nMasukkan jumlah mahasiswa: ";
    cin >> jumlah;

    for (int i = 0; i < jumlah; i++) {
        cout << "\nData Mahasiswa ke-" << i + 1 << endl;
        cout << "Nama: ";
        cin >> ws;
        getline(cin, nama[i]);
        cout << "NIM: ";
        cin >> nim[i];
        cout << "Nilai Tugas: ";
        cin >> nilai[i][0];
        cout << "Nilai UTS: ";
        cin >> nilai[i][1];
        cout << "Nilai UAS: ";
        cin >> nilai[i][2];
    }
}

// Modul hitung nilai akhir
void hitungNilaiAkhir() {
    if (jumlah == 0) {
        cout << "\nBelum ada data mahasiswa!\n";
        return;
    }

    for (int i = 0; i < jumlah; i++) {
        nilai[i][3] = (nilai[i][0] * 0.3) + (nilai[i][1] * 0.3) + (nilai[i][2] * 0.4);
    }
    cout << "\nNilai akhir berhasil dihitung!\n";
}

// Modul tampilkan semua data
void tampilkanData() {
    if (jumlah == 0) {
        cout << "\nBelum ada data mahasiswa!\n";
        return;
    }

    cout << "\n===== DATA MAHASISWA =====\n";
    for (int i = 0; i < jumlah; i++) {
        cout << i + 1 << ". " << nama[i] << " (" << nim[i] << ")\n";
        cout << "   Tugas: " << nilai[i][0]
             << ", UTS: " << nilai[i][1]
             << ", UAS: " << nilai[i][2]
             << ", Nilai Akhir: " << nilai[i][3] << endl;
    }
}

// Modul tampilkan kelulusan
void tampilKelulusan() {
    if (jumlah == 0) {
        cout << "\nBelum ada data mahasiswa!\n";
        return;
    }

    cout << "\n===== STATUS KELULUSAN =====\n";
    for (int i = 0; i < jumlah; i++) {
        cout << nama[i] << " (" << nim[i] << ") - Nilai Akhir: " << nilai[i][3];
        if (nilai[i][3] >= 60)
            cout << " -> LULUS\n";
        else
            cout << " -> TIDAK LULUS\n";
    }
}

// Modul tampilkan statistik nilai
void tampilStatistik() {
    if (jumlah == 0) {
        cout << "\nBelum ada data mahasiswa!\n";
        return;
    }

    float tertinggi = nilai[0][3];
    float terendah = nilai[0][3];
    float total = 0;

    for (int i = 0; i < jumlah; i++) {
        if (nilai[i][3] > tertinggi) tertinggi = nilai[i][3];
        if (nilai[i][3] < terendah) terendah = nilai[i][3];
        total += nilai[i][3];
    }

    float rata = total / jumlah;
    cout << "\n===== STATISTIK NILAI =====\n";
    cout << "Nilai Tertinggi : " << tertinggi << endl;
    cout << "Nilai Terendah  : " << terendah << endl;
    cout << "Rata-rata Nilai : " << rata << endl;
}

// Modul pencarian berdasarkan NIM
void cariMahasiswa() {
    if (jumlah == 0) {
        cout << "\nBelum ada data mahasiswa!\n";
        return;
    }

    string cari;
    bool ditemukan = false;
    cout << "\nMasukkan NIM yang ingin dicari: ";
    cin >> cari;

    for (int i = 0; i < jumlah; i++) {
        if (nim[i] == cari) {
            cout << "\nData ditemukan!\n";
            cout << "Nama          : " << nama[i] << endl;
            cout << "NIM           : " << nim[i] << endl;
            cout << "Tugas         : " << nilai[i][0] << endl;
            cout << "UTS           : " << nilai[i][1] << endl;
            cout << "UAS           : " << nilai[i][2] << endl;
            cout << "Nilai Akhir   : " << nilai[i][3] << endl;
            cout << "Status        : " << (nilai[i][3] >= 60 ? "LULUS" : "TIDAK LULUS") << endl;
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan)
        cout << "\nMahasiswa dengan NIM tersebut tidak ditemukan!\n";
}

// Modul hapus data mahasiswa berdasarkan NIM
void hapusMahasiswa() {
    if (jumlah == 0) {
        cout << "\nBelum ada data mahasiswa!\n";
        return;
    }

    string hapusNIM;
    cout << "\nMasukkan NIM mahasiswa yang ingin dihapus: ";
    cin >> hapusNIM;

    bool ditemukan = false;
    for (int i = 0; i < jumlah; i++) {
        if (nim[i] == hapusNIM) {
            ditemukan = true;
            char konfirmasi;
            cout << "Apakah Anda yakin ingin menghapus data " << nama[i] << " (y/n)? ";
            cin >> konfirmasi;

            if (konfirmasi == 'y' || konfirmasi == 'Y') {
                // Geser semua data ke atas
                for (int j = i; j < jumlah - 1; j++) {
                    nama[j] = nama[j + 1];
                    nim[j] = nim[j + 1];
                    for (int k = 0; k < 4; k++) {
                        nilai[j][k] = nilai[j + 1][k];
                    }
                }
                jumlah--;
                cout << "\nData mahasiswa berhasil dihapus!\n";
            } else {
                cout << "\nPenghapusan dibatalkan.\n";
            }
            break;
        }
    }

    if (!ditemukan)
        cout << "\nMahasiswa dengan NIM tersebut tidak ditemukan!\n";
}

// Modul edit data mahasiswa berdasarkan NIM
void editMahasiswa() {
    if (jumlah == 0) {
        cout << "\nBelum ada data mahasiswa!\n";
        return;
    }

    string editNIM;
    cout << "\nMasukkan NIM mahasiswa yang ingin diedit: ";
    cin >> editNIM;

    bool ditemukan = false;
    for (int i = 0; i < jumlah; i++) {
        if (nim[i] == editNIM) {
            ditemukan = true;
            cout << "\nData lama mahasiswa:\n";
            cout << "Nama: " << nama[i] << "\nTugas: " << nilai[i][0]
                 << ", UTS: " << nilai[i][1]
                 << ", UAS: " << nilai[i][2]
                 << ", Nilai Akhir: " << nilai[i][3] << endl;

            char konfirmasi;
            cout << "\nApakah Anda ingin mengedit data ini? (y/n): ";
            cin >> konfirmasi;

            if (konfirmasi == 'y' || konfirmasi == 'Y') {
                cout << "\nMasukkan data baru:\n";
                cout << "Nama: ";
                cin >> ws;
                getline(cin, nama[i]);
                cout << "Nilai Tugas: ";
                cin >> nilai[i][0];
                cout << "Nilai UTS: ";
                cin >> nilai[i][1];
                cout << "Nilai UAS: ";
                cin >> nilai[i][2];
                nilai[i][3] = (nilai[i][0] * 0.3) + (nilai[i][1] * 0.3) + (nilai[i][2] * 0.4);
                cout << "\nData berhasil diperbarui!\n";
            } else {
                cout << "\nEdit dibatalkan.\n";
            }
            break;
        }
    }

    if (!ditemukan)
        cout << "\nMahasiswa dengan NIM tersebut tidak ditemukan!\n";
}

int main() {
    int pilihan;

    do {
        cout << "\n===== PROGRAM DATA NILAI MAHASISWA =====\n";
        cout << "1. Input data mahasiswa\n";
        cout << "2. Hitung nilai akhir\n";
        cout << "3. Tampilkan data mahasiswa\n";
        cout << "4. Tampilkan status kelulusan\n";
        cout << "5. Tampilkan statistik nilai\n";
        cout << "6. Cari mahasiswa berdasarkan NIM\n";
        cout << "7. Edit data mahasiswa\n";
        cout << "8. Hapus data mahasiswa\n";
        cout << "9. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        if (pilihan == 1) inputData();
        else if (pilihan == 2) hitungNilaiAkhir();
        else if (pilihan == 3) tampilkanData();
        else if (pilihan == 4) tampilKelulusan();
        else if (pilihan == 5) tampilStatistik();
        else if (pilihan == 6) cariMahasiswa();
        else if (pilihan == 7) editMahasiswa();
        else if (pilihan == 8) hapusMahasiswa();
        else if (pilihan == 9) cout << "\nTerima kasih telah menggunakan program ini!\n";
        else cout << "\nPilihan tidak valid!\n";

    } while (pilihan != 9);

    return 0;
}
