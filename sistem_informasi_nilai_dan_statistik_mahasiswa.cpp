#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX = 40;
const int JUMLAH_MK = 3;
int jumlah = 0;

// Array Data mahasiswa
string nama[MAX];
string nim[MAX];
float nilai[MAX][JUMLAH_MK][4]; // 0=tugas,1=uts,2=uas,3=nilai akhir
string namaMK[JUMLAH_MK] = {"Dasar Pemrograman", "Logika Matematika", "Kalkulus"};

// Modul garis pembatas
void garis() {
    cout << "------------------------------------------------------------\n";
}

// Modul hitung nilai, rata-rata dan status kelulusan
void hitungNilaiAkhir(int mhs) {
    float total = 0;
    for (int mk = 0; mk < JUMLAH_MK; mk++) {
        nilai[mhs][mk][3] = nilai[mhs][mk][0] * 0.3f + nilai[mhs][mk][1] * 0.3f + nilai[mhs][mk][2] * 0.4f;
        total += nilai[mhs][mk][3];
    }
}

float hitungRataRata(int mhs) {
    float total = 0;
    for (int mk = 0; mk < JUMLAH_MK; mk++) {
        total += nilai[mhs][mk][3];
    }
    return total / JUMLAH_MK;
}

string cekStatus(float rata) {
    return (rata >= 60) ? "Lulus" : "Tidak Lulus";
}

// Modul input data
void inputData() {
    int n;
    cout << "Masukkan jumlah mahasiswa: ";
    cin >> n;
    cin.ignore();
    garis();

    for (int mhs = jumlah; mhs < jumlah + n; mhs++) {
        cout << "\nData Mahasiswa ke-" << mhs + 1 << endl;
        cout << "Nama: ";
        getline(cin, nama[mhs]);
        cout << "NIM: ";
        getline(cin, nim[mhs]);

        for (int mk = 0; mk < JUMLAH_MK; mk++) {
            cout << "\nMata Kuliah: " << namaMK[mk] << endl;
            cout << "Nilai Tugas: ";
            cin >> nilai[mhs][mk][0];
            cout << "Nilai UTS  : ";
            cin >> nilai[mhs][mk][1];
            cout << "Nilai UAS  : ";
            cin >> nilai[mhs][mk][2];
        }
        cin.ignore();

        hitungNilaiAkhir(mhs);
        garis();
    }
    jumlah += n;
}

// Modul tampilkan semua data
void tampilkanData() {
    if (jumlah == 0) {
        garis();
        cout << "Belum ada data mahasiswa.\n";
        garis();
        return;
    }
    // Lebar total tabel
    int lebarTotal = 60;
    string judul = "DATA MAHASISWA";

    // Hitung spasi agar judul center
    int spasi = (lebarTotal - judul.length()) / 2;

    cout << "\n";
    cout << string(spasi, ' ') << judul << "\n";
    garis();
    cout << left << setw(20) << "Nama"
         << setw(15) << "NIM"
         << setw(15) << "Rata-Rata"
         << "Status" << endl;
    garis();

    for (int mhs = 0; mhs < jumlah; mhs++) {
        float rata = hitungRataRata(mhs);
        cout << left << setw(20) << nama[mhs]
             << setw(15) << nim[mhs]
             << setw(15) << fixed << setprecision(2) << rata
             << cekStatus(rata) << endl;
    }
}

// Modul tampilkan statistik nilai
void tampilkanStatistik() {
    if (jumlah == 0) {
        garis();
        cout << "Belum ada data mahasiswa.\n";
        garis();
        return;
    }

    float total = 0;
    float tertinggi = hitungRataRata(0);
    float terendah = hitungRataRata(0);

    for (int mhs = 0; mhs < jumlah; mhs++) {
        float rata = hitungRataRata(mhs);
        total += rata;
        if (rata > tertinggi) tertinggi = rata;
        if (rata < terendah) terendah = rata;
    }

    // Lebar total tabel
    int lebarTotal = 60;
    string judul = "STATISTIK NILAI MAHASISWA";

    // Hitung spasi agar judul center
    int spasi = (lebarTotal - judul.length()) / 2;

    cout << "\n";
    cout << string(spasi, ' ') << judul << "\n";
    garis();
    cout << "Rata-rata keseluruhan  : " << fixed << setprecision(2) << total / jumlah << endl;
    cout << "Nilai tertinggi        : " << tertinggi << endl;
    cout << "Nilai terendah         : " << terendah << endl;
}

// Modul pencarian berdasarkan NIM
void cariMahasiswa() {
    if (jumlah == 0) {
        cout << "\nBelum ada data mahasiswa!\n";
        return;
    }

    string cariNIM;
    cout << "Masukkan NIM yang ingin dicari: ";
    getline(cin, cariNIM);

    bool ditemukan = false;
    for (int mhs = 0; mhs < jumlah; mhs++) {
        if (nim[mhs] == cariNIM) {
            ditemukan = true;
            garis();
            cout << "Data ditemukan!\n";
            cout << "Nama Mahasiswa: " << nama[mhs] << endl;
            cout << "NIM           : " << nim[mhs] << endl;
            float rata = hitungRataRata(mhs);
            cout << "Rata-Rata     : " << fixed << setprecision(2) << rata << endl;
            cout << "Status        : " << cekStatus(rata) << endl;
            cout << "\nDetail Nilai per Mata Kuliah:\n";
            for (int mk = 0; mk < JUMLAH_MK; mk++) {
                cout << "  " << namaMK[mk] << " - "
                     << "Tugas: " << nilai[mhs][mk][0] << ", "
                     << "UTS: " << nilai[mhs][mk][1] << ", "
                     << "UAS: " << nilai[mhs][mk][2] << ", "
                     << "Nilai Akhir: " << fixed << setprecision(2) << nilai[mhs][mk][3] << endl;
            }
            garis();
            break;
        }
    }

    if (!ditemukan) {
        cout << "\nMahasiswa dengan NIM " << cariNIM << " tidak ditemukan!\n";
    }
}

// Modul ubah data mahasiswa berdasarkan NIM
void ubahMahasiswa() {
    if (jumlah == 0) {
        cout << "\nBelum ada data mahasiswa!\n";
        return;
    }

    string ubahNIM;
    cout << "Masukkan NIM mahasiswa yang ingin diubah: ";
    getline(cin, ubahNIM);

    bool ditemukan = false;
    for (int mhs = 0; mhs < jumlah; mhs++) {
        if (nim[mhs] == ubahNIM) {
            ditemukan = true;
            garis();
            cout << "Data lama mahasiswa:\n";
            cout << "Nama: " << nama[mhs] << endl;
            for (int mk = 0; mk < JUMLAH_MK; mk++) {
                cout << "Mata Kuliah: " << namaMK[mk] << endl;
                cout << "  Tugas       : " << nilai[mhs][mk][0] << endl;
                cout << "  UTS         : " << nilai[mhs][mk][1] << endl;
                cout << "  UAS         : " << nilai[mhs][mk][2] << endl;
                cout << "  Nilai Akhir : " << fixed << setprecision(2) << nilai[mhs][mk][3] << endl;
            }

            char konfirmasi;
            cout << "\nApakah Anda ingin mengubah data ini? (y/n): ";
            cin >> konfirmasi;
            cin.ignore();

            if (konfirmasi == 'y' || konfirmasi == 'Y') {
                cout << "\nMasukkan data baru:\n";
                cout << "Nama: ";
                getline(cin, nama[mhs]);

                for (int mk = 0; mk < JUMLAH_MK; mk++) {
                    cout << "\nMata Kuliah: " << namaMK[mk] << endl;
                    cout << "Nilai Tugas: ";
                    cin >> nilai[mhs][mk][0];
                    cout << "Nilai UTS  : ";
                    cin >> nilai[mhs][mk][1];
                    cout << "Nilai UAS  : ";
                    cin >> nilai[mhs][mk][2];
                }
                cin.ignore();

                hitungNilaiAkhir(mhs);
                cout << "\nData berhasil diperbarui!\n";
            } else {
                cout << "\nPerubahan dibatalkan.\n";
            }
            break;
        }
    }

    if (!ditemukan)
        cout << "\nMahasiswa dengan NIM " << ubahNIM << " tidak ditemukan!\n";
}

// Modul hapus data mahasiswa berdasarkan NIM
void hapusMahasiswa() {
    if (jumlah == 0) {
        cout << "\nBelum ada data mahasiswa!\n";
        return;
    }

    string hapusNIM;
    cout << "Masukkan NIM mahasiswa yang ingin dihapus: ";
    getline(cin, hapusNIM);

    bool ditemukan = false;
    for (int mhs = 0; mhs < jumlah; mhs++) {
        if (nim[mhs] == hapusNIM) {
            ditemukan = true;
            char konfirmasi;
            cout << "Apakah Anda yakin ingin menghapus data " << nama[mhs] << " (y/n)? ";
            cin >> konfirmasi;
            cin.ignore();

            if (konfirmasi == 'y' || konfirmasi == 'Y') {
                // Geser data ke kiri karena ada yang dihapus
                for (int i = mhs; i < jumlah - 1; i++) {
                    nama[i] = nama[i + 1];
                    nim[i] = nim[i + 1];
                    for (int mk = 0; mk < JUMLAH_MK; mk++) {
                        for (int nilaiIdx = 0; nilaiIdx < 4; nilaiIdx++) {
                            nilai[i][mk][nilaiIdx] = nilai[i + 1][mk][nilaiIdx];
                        }
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
        cout << "\nMahasiswa dengan NIM " << hapusNIM << " tidak ditemukan!\n";
}

// Fungsi Utama
int main() {
    int pilihan;

    do {
        cout << "\n=== SISTEM INFORMASI NILAI MAHASISWA ===\n";
        cout << "1. Input Data Mahasiswa\n";
        cout << "2. Tampilkan Data Mahasiswa\n";
        cout << "3. Statistik Nilai\n";
        cout << "4. Cari Mahasiswa berdasarkan NIM\n";
        cout << "5. Edit Data Mahasiswa\n";
        cout << "6. Hapus Data Mahasiswa\n";
        cout << "7. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                cout << "\n";
                garis();
                inputData();
                break;
            case 2:
                cout << "\n";
                garis();
                tampilkanData();
                cout << "\n";
                garis();
                break;
            case 3:
                cout << "\n";
                garis();
                tampilkanStatistik();
                cout << "\n";
                garis();
                break;
            case 4:
                cout << "\n";
                garis();
                cariMahasiswa();
                break;
            case 5:
                cout << "\n";
                garis();
                ubahMahasiswa();
                break;
            case 6:
                cout << "\n";
                garis();
                hapusMahasiswa();
                break;
            case 7:
                cout << "\n";
                garis();
                cout << "Terima kasih telah menggunakan program ini!\n";
                garis();
                break;
            default:
                cout << "\n";
                garis();
                cout << "Pilihan tidak valid, coba lagi.\n";
                garis();
                break;
        }
    } while (pilihan != 7);

    return 0;
}
