# 🌀 Explorer Cyber-Neon Scrollbar (Configurable Alpha Override)

![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)
![Mod Version](https://img.shields.io/badge/Version-0.7-blue.svg)
![Mod Preview](banner.png)
> Neon scrollbar mod for Windows Explorer with configurable glow and alpha override.


Mod Windhawk ini menggambar scrollbar neon di Windows Explorer dengan efek glow dan kontrol alpha manual untuk area yang mencurigakan.

This Windhawk mod draws neon scrollbars in Windows Explorer with glow effects and manual alpha control for suspicious areas.

---

## 🎨 Fitur | Features [ID | EN]

- Thumb hijau neon dengan glow dinamis  
  Neon green thumb with dynamic glow

- Track ungu transparan yang bisa disesuaikan  
  Translucent purple track with adjustable alpha

- Safe mode: auto override alpha di area mencurigakan  
  Safe mode: auto alpha override in suspicious UI regions

- Konfigurasi penuh via Windhawk UI  
  Fully configurable via Windhawk UI

---

## ⚙️ Konfigurasi | Configuration

| Nama | Fungsi | Name | Description |
|------|--------|------|-------------|
| `track.alpha` | Transparansi track (0–255) | Track alpha | Track transparency |
| `thumb.alpha` | Transparansi thumb | Thumb alpha | Thumb visibility |
| `glow.size` | Ukuran glow | Glow size | Outer glow radius |
| `safeMode` | Aktifkan override otomatis | Safe mode | Enable auto override |
| `overrideAlpha` | Nilai alpha override | Override alpha | Alpha value for suspicious areas |

---

## 📦 Installation Guide | Cara Instalasi 

There are two ways to install this mod in Windhawk:  
Ada dua cara untuk menginstal mod ini di Windhawk:

### 🔹 Option 1: Install from file | Instal dari file

**EN:**
1. Download `explorer-neon-scroll-configurable.wh.cpp` from the [Releases](https://github.com/mrkhozin/windhawk-explorer-neon-scrollbar/releases)
2. Open Windhawk
3. Click **“Install mod from file”**
4. Select the downloaded `.wh.cpp` file
5. Enable the mod

**ID:**
1. Unduh `explorer-neon-scroll-configurable.wh.cpp` dari [Releases](https://github.com/mrkhozin/windhawk-explorer-neon-scrollbar/releases)
2. Buka Windhawk
3. Klik **“Install mod from file”**
4. Pilih file `.wh.cpp` yang sudah diunduh
5. Aktifkan mod-nya

---

### 🔹 Option 2: Create mod manually | Buat mod secara manual

**EN:**
1. Open Windhawk
2. Click **“Create mod”**
3. Delete the default code
4. Copy and paste the contents of `explorer-neon-scroll-configurable.wh.cpp`
5. Save and enable the mod

**ID:**
1. Buka Windhawk
2. Klik **“Create mod”**
3. Hapus kode default
4. Salin dan tempel isi file `explorer-neon-scroll-configurable.wh.cpp`
5. Simpan dan aktifkan mod-nya

---

# 🧩 Scrollbar Width Tweaks (.reg)

**EN:** These registry scripts adjust the width of scrollbars in classic Windows apps like File Explorer.  
**ID:** Skrip registry ini mengatur lebar scrollbar di aplikasi klasik Windows seperti File Explorer.

Go to folder | Cek di folder 📂: [scrollbar-width](https://github.com/mrkhozin/windhawk-explorer-neon-scrollbar/tree/main/scrollbar-width) 

---

## 🧪 Catatan Teknis / Technical Notes

- Hook pada `DrawThemeBackground` dari `uxtheme.dll`  
  Hooks `DrawThemeBackground` from `uxtheme.dll`

- Menggunakan GDI+ untuk rendering glow dan rounded thumb  
  Uses GDI+ for glow and rounded thumb rendering

- Tidak mengubah registry atau driver  
  Does not modify registry or drivers

---
## 🧩 Metadata

- License | Lisensi: MIT
- Tags | Tag: `scrollbar`, `explorer`, `neon`, `visual`, `customization`
- Compatibility | Kompatibilitas: Windhawk v1.4+

---

## 🙌 Credits | Kredit

Dikembangkan oleh **Moch. Khozin & Copilot**  
Developed by **Moch. Khozin & Copilot**

Mod ini dibuat untuk komunitas modding dan troubleshooting lokal  
This mod was built for the local modding and troubleshooting community

Dibuat oleh [@mrkhozin](https://github.com/mrkhozin)
Created by [@mrkhozin](https://github.com/mrkhozin)  

---

🔝 [Kembali ke atas / Back to top](#-explorer-cyber-neon-scrollbar-configurable-alpha-override)

