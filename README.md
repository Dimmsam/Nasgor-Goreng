# Nasgor-Goreng
Repository untuk memenuhi tugas mata kuliah SDA Praktik

Project: PROGRAM SISTEM PERPUSTAKAAN DIGITAL

# Anggota
- Abdurahman Nur Fadilah (241511033)
- Dimas Rizal Ramadhani (241511040)
- Mahesa Fazrie Mahardhika Gunadi (241511047)

# Cara Menjalankan Program
## Menggunakan VSCode
1. Install MINGW-32
2. Install Extension C/C++
3. Compile dengan command
   `gcc -o perpustakaan main.c src/menu.c src/admin.c src/booklist.c src/queue.c src/stack.c src/tree.c src/transaksi.c src/rekomendasi.c -I header`
4. Jalankan dengan command
   `./perpustakaan.exe`

## Menggunakan Dev-C++
1. Buat Folder baru dalam komputermu beri nama apapun, ex: `Sistem Perpustakaan Digital`
3. Download semua file dari Repository ini
4. Simpan Folder data, header, src, dan juga file main.c ke dalam folder yang telah dibuat
5. Install Dev-C++ v.5.11 dari link berikut [https://bloodshed-dev-c-plus-plus.en.uptodown.com/windows/download]
6. Pilih menu File -> New -> Project
7. Pilih Empty Project dan C Project
8. Beri nama Project `Sistem Perpustakaan Digital`, klik OK
9. Simpan Project ke tempat yang sama dengan folder data, header, src, dan main.c
10. Klik kanan pada Panel kiri -> Add to Project
11. Pilih semua file .c yang ada pada folder src dan juga file main.c
12. Lalu, klik menu Project di panel atas -> Project Options
13. Pilih bagian Directories -> Include Directories
14. Pada ikon folder klik ikon tersebut lalu pilih folder header yang tadi disimpan pada folder baru yang telah dibuat
15. Klik Add -> OK
16. Terakhir pilih menu Compile & Run (F11)

@Kelompok_Nasgor_Goreng_1B_D3_Teknik Informatika_2025
