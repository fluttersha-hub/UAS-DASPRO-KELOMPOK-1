#include <iostream>

using namespace std;

// -----------------------------------------------------
// 1. Definisi Struktur Data dan Konstanta (tanpa <string>, <vector>)
// -----------------------------------------------------

const int MAX_MAHASISWA = 10; // Batas maksimum mahasiswa
const int NAMA_SIZE = 50;     // Ukuran maksimum nama/NIM
const double BOBOT_TUGAS = 0.20;
const double BOBOT_UTS = 0.30;
const double BOBOT_UAS = 0.50;
const double BATAS_LULUS = 60.0;

// Struktur untuk menyimpan data satu mahasiswa (menggunakan char array)
struct Mahasiswa {
    char nama[NAMA_SIZE];
    char nim[NAMA_SIZE];
    double tugas;
    double uts;
    double uas;
    double nilai_akhir;
    char status_kelulusan[20];
};

// Array statis untuk menyimpan semua data mahasiswa
Mahasiswa data_mahasiswa[MAX_MAHASISWA];
int jumlah_mahasiswa = 0; // Penghitung data yang sudah terisi

// -----------------------------------------------------
// 2. Fungsi Perhitungan dan Logika
// -----------------------------------------------------

/**
 * @brief Menghitung Nilai Akhir dengan rata-rata berbobot.
 */
double hitungNilaiAkhir(double tugas, double uts, double uas) {
    return (tugas * BOBOT_TUGAS) + (uts * BOBOT_UTS) + (uas * BOBOT_UAS);
}

/**
 * @brief Menentukan status kelulusan.
 * @param mhs Pointer ke objek Mahasiswa yang datanya akan diisi.
 */
void tentukanStatusKelulusan(Mahasiswa* mhs) {
    if (mhs->nilai_akhir >= BATAS_LULUS) {
        // Menggunakan library C standard untuk manipulasi string
        char status_lulus[] = "LULUS";
        for (int i = 0; i < 6; ++i) { mhs->status_kelulusan[i] = status_lulus[i]; }
    } else {
        char status_tidak_lulus[] = "TIDAK LULUS";
        for (int i = 0; i < 12; ++i) { mhs->status_kelulusan[i] = status_tidak_lulus[i]; }
    }
}

// -----------------------------------------------------
// 3. Fungsi Input Data
// -----------------------------------------------------

/**
 * @brief Mengambil input data satu mahasiswa dan memprosesnya.
 */
void inputDataMahasiswa() {
    if (jumlah_mahasiswa >= MAX_MAHASISWA) {
        cout << "\n❌ Batas maksimum " << MAX_MAHASISWA << " mahasiswa telah tercapai." << endl;
        return;
    }

    Mahasiswa* mhs = &data_mahasiswa[jumlah_mahasiswa];
    double tugas, uts, uas;

    cout << "\n--- Input Data Mahasiswa ke-" << jumlah_mahasiswa + 1 << " ---" << endl;

    // Clear buffer untuk getline
    cin.ignore(10000, '\n');

    cout << "Masukkan Nama Mahasiswa: ";
    cin.getline(mhs->nama, NAMA_SIZE);

    cout << "Masukkan NIM Mahasiswa  : ";
    cin.getline(mhs->nim, NAMA_SIZE);

    // Input Nilai dengan validasi sederhana
    cout << "Masukkan Nilai Tugas (0-100): ";
    if (!(cin >> tugas) || tugas < 0 || tugas > 100) {
        cout << "❌ Input nilai Tugas tidak valid (harus angka 0-100)." << endl;
        cin.clear();
        return;
    }
    cout << "Masukkan Nilai UTS (0-100)  : ";
    if (!(cin >> uts) || uts < 0 || uts > 100) {
        cout << "❌ Input nilai UTS tidak valid (harus angka 0-100)." << endl;
        cin.clear();
        return;
    }
    cout << "Masukkan Nilai UAS (0-100)  : ";
    if (!(cin >> uas) || uas < 0 || uas > 100) {
        cout << "❌ Input nilai UAS tidak valid (harus angka 0-100)." << endl;
        cin.clear();
        return;
    }

    // Clear buffer sisa input
    cin.ignore(10000, '\n');

    // Hitung dan simpan hasil
    mhs->tugas = tugas;
    mhs->uts = uts;
    mhs->uas = uas;
    mhs->nilai_akhir = hitungNilaiAkhir(tugas, uts, uas);
    tentukanStatusKelulusan(mhs);

    jumlah_mahasiswa++;
    cout << "\n✅ Data Mahasiswa " << mhs->nama << " berhasil ditambahkan!" << endl;
}

// -----------------------------------------------------
// 4. Fungsi Tampilan (Output)
// -----------------------------------------------------

/**
 * @brief Menampilkan data semua mahasiswa dalam bentuk tabel.
 */
void tampilkanSemuaData() {
    if (jumlah_mahasiswa == 0) {
        cout << "\nBelum ada data mahasiswa yang tersimpan." << endl;
        return;
    }

    cout << "\n==========================================================================" << endl;
    cout << "               📊 DATA NILAI AKADEMIK MAHASISWA 📊" << endl;
    cout << "==========================================================================" << endl;

    // Header Tabel
    cout << "| No. | NIM        | Nama Mahasiswa           | Tugas | UTS | UAS | NA  | Status      |" << endl;
    cout << "--------------------------------------------------------------------------" << endl;

    // Isi Tabel
    for (int i = 0; i < jumlah_mahasiswa; ++i) {
        const Mahasiswa& mhs = data_mahasiswa[i];

        // Pengaturan lebar dan presisi manual (karena <iomanip> tidak digunakan)
        cout.setf(ios::fixed, ios::floatfield);
        cout.precision(1);

        cout << "| " << i + 1 << "   | ";
        cout.width(10); cout << left << mhs.nim;
        cout << " | ";
        cout.width(25); cout << left << mhs.nama;
        cout << " | ";
        cout.width(5); cout << right << mhs.tugas;
        cout << " | ";
        cout.width(3); cout << right << mhs.uts;
        cout << " | ";
        cout.width(3); cout << right << mhs.uas;
        cout << " | ";
        cout.precision(2); // Untuk NA, kita pakai 2 angka di belakang koma
        cout.width(3); cout << right << mhs.nilai_akhir;
        cout << " | ";
        cout.width(11); cout << left << mhs.status_kelulusan;
        cout << " |" << endl;
    }
    cout << "==========================================================================" << endl;
}

/**
 * @brief Menghitung dan menampilkan statistik nilai akhir.
 */
void tampilkanStatistikNilai() {
    if (jumlah_mahasiswa == 0) {
        cout << "\nTidak ada data untuk dihitung statistik." << endl;
        return;
    }

    double total_na = 0.0;
    double nilai_tertinggi = -1.0;
    double nilai_terendah = 101.0;

    // Perulangan untuk menghitung total, tertinggi, dan terendah
    for (int i = 0; i < jumlah_mahasiswa; ++i) {
        double na = data_mahasiswa[i].nilai_akhir;
        total_na += na;

        if (na > nilai_tertinggi) {
            nilai_tertinggi = na;
        }
        if (na < nilai_terendah) {
            nilai_terendah = na;
        }
    }

    double rata_rata = total_na / jumlah_mahasiswa;

    // Tampilkan Hasil
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);

    cout << "\n--- 📈 Statistik Nilai Akhir (NA) ---" << endl;
    cout << "Total Mahasiswa          : " << jumlah_mahasiswa << endl;
    cout << "Rata-rata Nilai Akhir    : " << rata_rata << endl;
    cout << "Nilai Akhir TERTINGGI    : " << nilai_tertinggi << endl;
    cout << "Nilai Akhir TERENDAH     : " << nilai_terendah << endl;
    cout << "----------------------------------------" << endl;
}

/**
 * @brief Mencari dan menampilkan data mahasiswa berdasarkan NIM.
 */
void cariMahasiswaByNIM() {
    if (jumlah_mahasiswa == 0) {
        cout << "\nBelum ada data mahasiswa untuk dicari." << endl;
        return;
    }

    char nim_cari[NAMA_SIZE];

    // Clear buffer untuk getline
    cin.ignore(10000, '\n');

    cout << "\nMasukkan NIM Mahasiswa yang dicari: ";
    cin.getline(nim_cari, NAMA_SIZE);

    bool ditemukan = false;

    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);

    for (int i = 0; i < jumlah_mahasiswa; ++i) {
        // Bandingkan NIM (perlu perulangan karena tidak ada <string.h>)
        bool nim_sama = true;
        for (int j = 0; nim_cari[j] != '\0' || data_mahasiswa[i].nim[j] != '\0'; ++j) {
            if (nim_cari[j] != data_mahasiswa[i].nim[j]) {
                nim_sama = false;
                break;
            }
        }

        if (nim_sama) {
            ditemukan = true;
            const Mahasiswa& mhs = data_mahasiswa[i];

            cout << "\n--- ✅ Data Mahasiswa Ditemukan ---" << endl;
            cout << "Nama Mahasiswa    : " << mhs.nama << endl;
            cout << "NIM               : " << mhs.nim << endl;
            cout << "Nilai Tugas       : "; cout.precision(1); cout << mhs.tugas << endl;
            cout << "Nilai UTS         : "; cout.precision(1); cout << mhs.uts << endl;
            cout << "Nilai UAS         : "; cout.precision(1); cout << mhs.uas << endl;
            cout << "---------------------------------" << endl;
            cout << "**NILAI AKHIR (NA): "; cout.precision(2); cout << mhs.nilai_akhir << "**" << endl;
            cout << "**STATUS KELULUSAN: " << mhs.status_kelulusan << "**" << endl;
            cout << "---------------------------------" << endl;
            break;
        }
    }

    if (!ditemukan) {
        cout << "\n❌ Mahasiswa dengan NIM " << nim_cari << " tidak ditemukan." << endl;
    }
}

// -----------------------------------------------------
// 5. Fungsi Utama (Menu Program)
// -----------------------------------------------------

int main() {
    int pilihan;

    do {
        cout << "\n_____________________________________________" << endl;
        cout << "*| SISTEM MANAJEMEN NILAI MAHASISWA (IOSTREAM)|" << endl;
        cout << "______________________________________________" << endl;
        cout << "1. Input Data Mahasiswa Baru" << endl;
        cout << "2. Tampilkan Semua Data Nilai" << endl;
        cout << "3. Tampilkan Statistik Nilai Akhir" << endl;
        cout << "4. Cari Data Mahasiswa (Berdasarkan NIM)" << endl;
        cout << "5. Keluar Program" << endl;
        cout << "___________________________________________" << endl;
        cout << "Masukkan pilihan Anda (1-5): ";

        // Input Pilihan Menu
        if (!(cin >> pilihan)) {
            cout << "\n⚠️ Input tidak valid. Silakan masukkan angka." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue; // Ulangi loop
        }

        switch (pilihan) {
            case 1:
                inputDataMahasiswa();
                break;
            case 2:
                tampilkanSemuaData();
                break;
            case 3:
                tampilkanStatistikNilai();
                break;
            case 4:
                cariMahasiswaByNIM();
                break;
            case 5:
                cout << "\nTerima kasih! Program dihentikan." << endl;
                break;
            default:
                cout << "\n⚠️ Pilihan tidak valid. Silakan masukkan angka antara 1 sampai 5." << endl;
                break;
        }
    } while (pilihan != 5);

    return 0;
}
