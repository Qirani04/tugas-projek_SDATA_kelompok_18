#ifndef LES_DATA_H
#define LES_DATA_H

#include <string>
using namespace std;

const int MAX_SISWA = 100;
const int MAX_MAPEL = 5;
const int MAX_HARI  = 7;

/* ===================== STRUCT DATA ===================== */

struct Jadwal {
    int jumlahHari;
    string hari[MAX_HARI];
    string jam;
    int mapelPerHari[MAX_HARI];
    string mapel[MAX_HARI][MAX_MAPEL];
};

struct Siswa {
    int id;
    string username;
    string password;
    string nama;
    string jenjang;
    int kelas;
    string mapel[MAX_MAPEL];
    int jumlahMapel;
    int hargaBulanan;
    bool lunas;
    Jadwal jadwal;
};

/* ===================== STACK LOG ===================== */

struct NodeLog {
    string aksi;
    NodeLog* next;
};

/* ===================== QUEUE PENDAFTAR ===================== */

struct NodeQueue {
    int idSiswa;
    NodeQueue* next;
};

/* ===================== BST PRIORITAS ===================== */

struct NodeBST {
    int key;
    string nama;
    NodeBST* left;
    NodeBST* right;
};

/* ===================== GLOBAL ===================== */

extern Siswa dataSiswa[MAX_SISWA];
extern int jumlahSiswa;
extern int autoID;

/* ===================== FUNCTION ===================== */

void tampilHeader(const string& judul);

/* Stack */
void pushLog(const string& aksi);
void tampilLog();

/* Queue */
void enqueuePendaftar(int id);

/* BST */
NodeBST* insertBST(NodeBST* node, int key, const string& nama);
void tampilPrioritas(NodeBST* root);

/* Util */
int hitungHarga(const string& jenjang, int jumlahMapel);
int cariIndexSiswa(int id);

/* Siswa */
bool loginSiswa(int &index);
void registrasiUser();
void menuEditSiswa(int index);
void menuUser();

/* Admin */
void prosesPembayaran();
void menuAdmin();

#endif

