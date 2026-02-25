# 📂 Smart File Organizer (C++17 — Windows)

A lightweight automatic file organizer written in modern **C++17** that scans common user folders and moves misplaced files into their correct Windows directories based on file type.

Built using the standard `std::filesystem` library — no external dependencies required.

---

## 🚀 Features

✅ Automatically scans user folders:

- Desktop
- Downloads
- Documents
- Pictures
- Videos
- Music

✅ Organizes files globally (not just inside one folder)  
✅ Moves misplaced files to correct Windows locations  
✅ Creates required folders automatically  
✅ Crash-safe filesystem traversal (Windows-safe iteration)  
✅ Works without administrator privileges  
✅ Detailed terminal output showing moved files  
✅ Final summary report after completion  

---

## 🧠 How It Works

The program scans safe user directories and checks each file’s extension.

If a file is located in the wrong folder, it is moved automatically.

Example:

Downloads/photo.jpg   → Pictures/photo.jpg  
Pictures/movie.mp4    → Videos/movie.mp4  
Desktop/song.mp3      → Music/song.mp3  
Documents/code.cpp    → Documents/Programs/code.cpp  

---

## 📁 Organization Rules

| File Type | Destination |
|---|---|
| Images (.jpg .jpeg .png .gif .bmp) | Pictures |
| Videos (.mp4 .mkv .avi .mov) | Videos |
| Music (.mp3 .wav .flac) | Music |
| Documents (.pdf .docx .txt .pptx .xlsx) | Documents |
| Programming Files | Documents/Programs |

Folders are automatically created if they do not exist.

---

## 💻 Terminal Output

During execution the program displays:

SMART FILE ORGANIZER

Scanning: Downloads  
[MOVED] cat.jpg -> Pictures  
[MOVED] video.mp4 -> Videos  

After completion:

Organization Completed Successfully!  
Files scanned : XXX  
Files moved   : XX  

Thank you for using Smart File Organizer ❤️

---

## ⚙️ Requirements

- C++17 compatible compiler
- Windows 10 / Windows 11

Supported compilers:

- MinGW-w64
- GCC (cross-compile from Linux)
- Visual Studio 2019+

---

## 🛠️ Compilation

### Compile on Linux (Arch → Windows EXE)

Install cross compiler:

sudo pacman -S mingw-w64-gcc

Build:

x86_64-w64-mingw32-g++ FileOrganizer.cpp -std=c++17 -O2 -static -static-libgcc -static-libstdc++ -o organizer.exe

---

### Compile Directly on Windows (MinGW)

g++ FileOrganizer.cpp -std=c++17 -O2 -o organizer.exe

Run:

organizer.exe

---

### Visual Studio

1. Create Console Application
2. Replace main.cpp with FileOrganizer.cpp
3. Set language standard:

Project Properties → C/C++ → Language → C++17

4. Build and Run.

---

## 📂 Folder Structure Created

Documents/
 └── Programs/

Created automatically when needed.

---

## 🔒 Safety Design

- Skips system directories automatically
- Avoids Windows junction/symlink crashes
- Ignores locked or protected files
- Prevents filename overwriting
- Requires no admin permissions
- Uses error-code based filesystem traversal

---

## ⚠️ Notes

- Only standard user folders are scanned.
- System folders such as AppData are intentionally ignored.
- Files already in the correct location are not moved.
- Existing files are never overwritten (renamed automatically).

---

## 📈 Future Improvements

- Preview mode (--dry-run)
- Undo operation
- Progress bar
- Configuration file support
- GUI application
- Background auto-organization

---

## 📜 License

Open source — free for learning, modification, and personal use.

---

## 👨‍💻 Author

Smart File Organizer — a C++17 filesystem automation project demonstrating practical system-level programming and safe file management.
