#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Konstanta global untuk batas maksimal buku
const int MAKS_BUKU = 100;

// Struct untuk menampung data buku
struct ItemBuku
{
    int no;
    string judul;
    string penulis;
    int stok;
};

// Class untuk mengelola semua fungsi perpustakaan
class Perpustakaan
{
private:
    ItemBuku koleksi[MAKS_BUKU];
    int jumlahBuku;

    void simpanSemuaData()
    {
        ofstream file_keluar("buku.txt");
        for (int i = 0; i < jumlahBuku; i++)
        {
            file_keluar << koleksi[i].no << " " << koleksi[i].judul << " "
                        << koleksi[i].penulis << " " << koleksi[i].stok << endl;
        }
        file_keluar.close();
    }

    void tambahData()
    {
        if (jumlahBuku >= MAKS_BUKU)
        {
            cout << "Penyimpanan penuh!" << endl;
            return;
        }

        ItemBuku bukuBaru;
        cout << "\n--- Tambah Buku ---" << endl;
        cout << "No Buku: ";
        cin >> bukuBaru.no;

        cin.ignore(10000, '\n'); 

        cout << "Judul: ";
        getline(cin, bukuBaru.judul);

        cout << "Penulis: ";
        getline(cin, bukuBaru.penulis);

        cout << "Stok: ";
        cin >> bukuBaru.stok;

        koleksi[jumlahBuku] = bukuBaru;
        jumlahBuku++;
        simpanSemuaData();
        cout << "Buku berhasil ditambahkan dan disimpan." << endl;
    }

    void cariData()
    {
        int pilih;
        string kataKunci;
        bool ada = false;

        cout << "Cari berdasarkan (1) Judul (2) Penulis: ";
        cin >> pilih;
        
        cin.ignore(10000, '\n');

        cout << "Masukkan kata kunci (harus sama persis): ";
        getline(cin, kataKunci);

        string namaFileHasil;
        if (pilih == 1)
        {
            namaFileHasil = "hasil_cari_judul.txt";
        }
        else
        {
            namaFileHasil = "hasil_cari_penulis.txt";
        }

        ofstream file_hasil(namaFileHasil.c_str());

        cout << "\n--- Hasil Pencarian ---" << endl;
        for (int i = 0; i < jumlahBuku; i++)
        {
            // --- INI BAGIAN YANG MENGGUNAKAN CARA 1 ---
            if ((pilih == 1 && koleksi[i].judul == kataKunci) ||
                (pilih == 2 && koleksi[i].penulis == kataKunci))
            {
                cout << "No: " << koleksi[i].no << ", Judul: " << koleksi[i].judul << ", Penulis: " << koleksi[i].penulis << ", Stok: " << koleksi[i].stok << endl;
                file_hasil << "No: " << koleksi[i].no << ", Judul: " << koleksi[i].judul << ", Penulis: " << koleksi[i].penulis << ", Stok: " << koleksi[i].stok << endl;
                ada = true;
            }
        }
        file_hasil.close();

        if (!ada)
        {
            cout << "Data tidak ditemukan." << endl;
        }
        else
        {
            cout << "Hasil juga disimpan ke file " << namaFileHasil << endl;
        }
    }

    void cariStokKurang()
    {
        bool ada = false;
        cout << "\n--- Buku dengan Stok < 5 ---" << endl;
        for (int i = 0; i < jumlahBuku; i++)
        {
            if (koleksi[i].stok < 5)
            {
                cout << "No: " << koleksi[i].no << ", Judul: " << koleksi[i].judul << ", Penulis: " << koleksi[i].penulis << ", Stok: " << koleksi[i].stok << endl;
                ada = true;
            }
        }

        if (!ada)
        {
            cout << "Tidak ada buku dengan stok kurang dari 5." << endl;
        }
    }

    void cariStokTerbanyak()
    {
        if (jumlahBuku == 0)
        {
            cout << "Belum ada data buku." << endl;
            return;
        }

        ItemBuku terbanyak = koleksi[0];
        for (int i = 1; i < jumlahBuku; i++)
        {
            if (koleksi[i].stok > terbanyak.stok)
            {
                terbanyak = koleksi[i];
            }
        }

        cout << "\n--- Buku Stok Terbanyak ---" << endl;
        cout << "No: " << terbanyak.no << ", Judul: " << terbanyak.judul << ", Penulis: " << terbanyak.penulis << ", Stok: " << terbanyak.stok << endl;
    }

    void urutkanData()
    {
        int pilih;
        cout << "Urutkan judul (1) A-Z (2) Z-A: ";
        cin >> pilih;

        for (int i = 0; i < jumlahBuku - 1; i++)
        {
            for (int j = 0; j < jumlahBuku - i - 1; j++)
            {
                bool tukar = false;
                if (pilih == 1 && koleksi[j].judul > koleksi[j + 1].judul)
                {
                    tukar = true;
                }
                if (pilih == 2 && koleksi[j].judul < koleksi[j + 1].judul)
                {
                    tukar = true;
                }
                if (tukar)
                {
                    ItemBuku temp = koleksi[j];
                    koleksi[j] = koleksi[j + 1];
                    koleksi[j + 1] = temp;
                }
            }
        }

        cout << "\n--- Data Setelah Diurutkan ---" << endl;
        tampilkanSemua();
    }

    void tampilkanSemua()
    {
        if (jumlahBuku == 0)
        {
            cout << "Belum ada data buku." << endl;
            return;
        }

        cout << "\n--- Semua Data Buku ---" << endl;
        for (int i = 0; i < jumlahBuku; i++)
        {
            cout << "No: " << koleksi[i].no << ", Judul: " << koleksi[i].judul << ", Penulis: " << koleksi[i].penulis << ", Stok: " << koleksi[i].stok << endl;
        }
    }

public:
    Perpustakaan()
    {
        jumlahBuku = 0;
        ifstream file_masuk("buku.txt");
        if (file_masuk.is_open())
        {
            // Menggunakan getline untuk membaca dari file agar judul/penulis dengan spasi bisa terbaca
            while (jumlahBuku < MAKS_BUKU && (file_masuk >> koleksi[jumlahBuku].no >> ws) && 
                   getline(file_masuk, koleksi[jumlahBuku].judul, '\t') && 
                   getline(file_masuk, koleksi[jumlahBuku].penulis, '\t') && 
                   (file_masuk >> koleksi[jumlahBuku].stok))
            {
                jumlahBuku++;
            }
            file_masuk.close();
        }
    }

    int tampilMenu()
    {
        int pilihan = 0;
        cout << "\n===== MENU PERPUSTAKAAN =====" << endl;
        cout << "1. Tambah Buku" << endl;
        cout << "2. Cari Buku" << endl;
        cout << "3. Tampilkan Stok < 5" << endl;
        cout << "4. Tampilkan Stok Terbanyak" << endl;
        cout << "5. Urutkan Buku" << endl;
        cout << "6. Tampilkan Semua Buku" << endl;
        cout << "7. Keluar" << endl;
        cout << "=============================" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            pilihan = 0;
        }

        switch (pilihan)
        {
            case 1:
                tambahData();
                break;
            case 2:
                cariData();
                break;
            case 3:
                cariStokKurang();
                break;
            case 4:
                cariStokTerbanyak();
                break;
            case 5:
                urutkanData();
                break;
            case 6:
                tampilkanSemua();
                break;
            case 7:
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
        return pilihan;
    }
};

int main()
{
    Perpustakaan perpusku;
    char lagi = 'y';

    do
    {
        int pilihanMenu = perpusku.tampilMenu();

        if (pilihanMenu == 7)
        {
            break;
        }

        cout << "\nKembali ke menu utama? (y/n): ";
        cin >> lagi;
        cin.ignore(10000, '\n');

    } while (lagi == 'y' || lagi == 'Y');

    cout << "Terima kasih!" << endl;
    return 0;
}
