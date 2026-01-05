#include <iostream>
#include <sstream>
#include <limits>
#include <string>

using namespace std;

/* ===================== STRUKTUR DATA ===================== */
#define MAX_SISWA 100

struct Jadwal {
    int jumlahHari;
    string hari[7];
    string jam;
};

struct Siswa {
    int id;
    string username;
    string password;
    string nama;
    string jenjang;
    int kelas;
    int jumlahMapel;
    string mapel[10];
    Jadwal jadwal;
    int hargaBulanan;
    bool lunas;
};

struct NodeLog {
    string aksi;
    NodeLog* next;
};

struct NodeQueue {
    int id;
    NodeQueue* next;
};

struct NodeBST {
    int key;
    string nama;
    NodeBST *left, *right;
};

/* ===================== GLOBAL ===================== */

Siswa dataSiswa[MAX_SISWA];
int jumlahSiswa = 0;
int autoID = 1001;

NodeLog* topLog = NULL;
NodeQueue* frontQ = NULL;
NodeQueue* rearQ = NULL;
NodeBST* rootBST = NULL;

/* ===================== UTIL ===================== */

// Fungsi pengganti to_string untuk kompatibilitas Dev-C++ lama
string intKeString(int n) {
    stringstream ss;
    ss << n;
    return ss.str();
}

void tampilHeader(const string& judul) {
    cout << "\n=====================================\n";
    cout << "   " << judul << endl;
    cout << "=====================================\n";
}

int cariIndexSiswa(int id) {
    for (int i = 0; i < jumlahSiswa; i++) {
        if (dataSiswa[i].id == id) return i;
    }
    return -1;
}

int hitungHarga(const string& jenjang, int jumlahMapel) {
    int harga = 0;
    if (jenjang == "SD" || jenjang == "sd") harga = 100000;
    else if (jenjang == "SMP" || jenjang == "smp") harga = 150000;
    else if (jenjang == "SMA" || jenjang == "sma") harga = 200000;

    int total = harga * jumlahMapel;
    if (jumlahMapel > 3) total = total * 90 / 100;
    if (jumlahMapel == 1) total = total * 70 / 100;

    return total;
}

/* ===================== STACK LOG ===================== */

void pushLog(string aksi) {
    NodeLog* n = new NodeLog;
    n->aksi = aksi;
    n->next = topLog;
    topLog = n;
}

void tampilLog() {
    tampilHeader("LOG AKTIVITAS");
    NodeLog* cur = topLog;
    int no = 1;
    if (!cur) cout << "Log masih kosong.\n";
    while (cur) {
        cout << no++ << ". " << cur->aksi << endl;
        cur = cur->next;
    }
}

/* ===================== QUEUE ===================== */

void enqueuePendaftar(int id) {
    NodeQueue* n = new NodeQueue;
    n->id = id;
    n->next = NULL;
    if (!rearQ) {
        frontQ = rearQ = n;
    } else {
        rearQ->next = n;
        rearQ = n;
    }
}

/* ===================== BST ===================== */

NodeBST* insertBST(NodeBST* node, int key, string nama) {
    if (!node) {
        NodeBST* n = new NodeBST;
        n->key = key;
        n->nama = nama;
        n->left = n->right = NULL;
        return n;
    }
    if (key < node->key) node->left = insertBST(node->left, key, nama);
    else node->right = insertBST(node->right, key, nama);
    return node;
}

void tampilPrioritas(NodeBST* root) {
    if (!root) return;
    tampilPrioritas(root->right);
    cout << root->nama << " | Rp " << root->key << endl;
    tampilPrioritas(root->left);
}

/* ===================== SISWA ===================== */

bool loginSiswa(int &index) {
    string u, p;
    tampilHeader("LOGIN SISWA");
    cout << "Username : "; cin >> u;
    cout << "Password : "; cin >> p;

    for (int i = 0; i < jumlahSiswa; i++) {
        if (dataSiswa[i].username == u && dataSiswa[i].password == p) {
            index = i;
            return true;
        }
    }
    cout << "Login gagal.\n";
    return false;
}

void menuEditSiswa(int index) {
    Siswa &s = dataSiswa[index];
    int pilih;

    do {
        tampilHeader("EDIT DATA SISWA");
        cout << "1. Nama\n2. Jenjang & Kelas\n3. Mapel\n4. Jadwal\n0. Kembali\nPilih : ";
        cin >> pilih;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (pilih == 1) {
            cout << "Nama baru : ";
            getline(cin, s.nama);
        }
        else if (pilih == 2) {
            cout << "Jenjang : "; getline(cin, s.jenjang);
            cout << "Kelas   : "; cin >> s.kelas;
        }
        else if (pilih == 3) {
            cout << "Jumlah Mapel : "; cin >> s.jumlahMapel;
            cin.ignore();
            for (int i = 0; i < s.jumlahMapel; i++) {
                cout << "Mapel " << i + 1 << " : ";
                getline(cin, s.mapel[i]);
            }
        }
        else if (pilih == 4) {
            cout << "Jumlah Hari : "; cin >> s.jadwal.jumlahHari;
            cin.ignore();
            for (int i = 0; i < s.jadwal.jumlahHari; i++) {
                cout << "Hari " << i + 1 << " : ";
                getline(cin, s.jadwal.hari[i]);
            }
            cout << "Jam : "; getline(cin, s.jadwal.jam);
        }
    } while (pilih != 0);

    s.hargaBulanan = hitungHarga(s.jenjang, s.jumlahMapel);
    s.lunas = false;

    pushLog("Siswa ID " + intKeString(s.id) + " mengubah data");
}

void registrasiUser() {
    if (jumlahSiswa >= MAX_SISWA) {
        cout << "Kuota penuh!\n";
        return;
    }

    Siswa &s = dataSiswa[jumlahSiswa];
    s.id = autoID++;
    s.lunas = false;

    tampilHeader("REGISTRASI");
    cout << "Username : "; cin >> s.username;
    cout << "Password : "; cin >> s.password;
    cin.ignore();

    cout << "Nama     : "; getline(cin, s.nama);
    cout << "Jenjang  : "; getline(cin, s.jenjang);
    cout << "Kelas    : "; cin >> s.kelas;
    cout << "Jumlah Mapel : "; cin >> s.jumlahMapel;
    cin.ignore();

    for (int i = 0; i < s.jumlahMapel; i++) {
        cout << "Mapel " << i + 1 << " : ";
        getline(cin, s.mapel[i]);
    }

    cout << "Jumlah Hari : "; cin >> s.jadwal.jumlahHari;
    cin.ignore();
    for (int i = 0; i < s.jadwal.jumlahHari; i++) {
        cout << "Hari " << i + 1 << " : ";
        getline(cin, s.jadwal.hari[i]);
    }
    cout << "Jam : "; getline(cin, s.jadwal.jam);

    s.hargaBulanan = hitungHarga(s.jenjang, s.jumlahMapel);

    enqueuePendaftar(s.id);
    rootBST = insertBST(rootBST, s.hargaBulanan, s.nama);
    pushLog("Registrasi " + s.nama);

    jumlahSiswa++;
    cout << "\nRegistrasi Berhasil! ID Anda: " << s.id << endl;
}

/* ===================== MENU ===================== */

void menuUser() {
    int p;
    do {
        tampilHeader("MENU SISWA");
        cout << "1. Registrasi\n2. Login & Edit Data\n0. Kembali\nPilih : ";
        cin >> p;

        if (p == 1) registrasiUser();
        else if (p == 2) {
            int idx;
            if (loginSiswa(idx))
                menuEditSiswa(idx);
        }
    } while (p != 0);
}

void prosesPembayaran() {
    tampilHeader("ACC PEMBAYARAN");
    int id;
    cout << "ID Siswa : "; cin >> id;

    int idx = cariIndexSiswa(id);
    if (idx == -1 || dataSiswa[idx].lunas) {
        cout << "ID tidak valid atau sudah lunas.\n";
        return;
    }

    dataSiswa[idx].lunas = true;
    pushLog("ACC pembayaran ID " + intKeString(id));
    cout << "Pembayaran Siswa " << dataSiswa[idx].nama << " telah dikonfirmasi.\n";
}

void menuAdmin() {
    int p;
    do {
        tampilHeader("MENU ADMIN");
        cout << "1. Data Siswa\n2. ACC Pembayaran\n3. Log Aktivitas\n4. Prioritas Biaya\n0. Kembali\nPilih : ";
        cin >> p;

        if (p == 1) {
            for (int i = 0; i < jumlahSiswa; i++)
                cout << dataSiswa[i].id << " | " << dataSiswa[i].nama
                     << " | " << (dataSiswa[i].lunas ? "LUNAS" : "PENDING") << endl;
        }
        else if (p == 2) prosesPembayaran();
        else if (p == 3) tampilLog();
        else if (p == 4) tampilPrioritas(rootBST);

    } while (p != 0);
}

/* ===================== MAIN ===================== */

int main() {
    int menu;
    do {
        tampilHeader("MLS - SISTEM PENDAFTARAN LES");
        cout << "1. Siswa\n2. Admin\n0. Keluar\nPilih : ";
        if(!(cin >> menu)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (menu == 1) menuUser();
        else if (menu == 2) menuAdmin();

    } while (menu != 0);

    return 0;
}
