# 📂 C++ File Organizer (Windows + Linux)

A lightweight **cross-platform file organizer** written in **C++17** that automatically sorts files from common user folders into structured directories based on file type.

Works on:

* ✅ Windows 10 / 11
* ✅ Linux (Arch, Ubuntu, etc.)
* ✅ Any system supporting C++17 filesystem

---

## 🚀 Features

* Automatically scans:

  * Desktop
  * Downloads
* Organizes files by extension
* Creates folders automatically
* Cross-platform (Windows + Linux)
* Built using modern `std::filesystem`
* No external libraries required

---

## 📁 Organization Rules

| File Type                             | Destination Folder   |
| ------------------------------------- | -------------------- |
| Images (`.jpg .png .jpeg .gif .webp`) | `Pictures`           |
| Videos (`.mp4 .mkv .avi .mov`)        | `Videos`             |
| Documents (`.pdf .docx .txt .pptx`)   | `Documents`          |
| Programming Files                     | `Documents/Programs` |
| Archives (`.zip .rar .tar .gz`)       | `Documents/Archives` |
| Unknown Types                         | `Documents/Others`   |

---

## 🧠 Supported Programming Extensions

```
.cpp  .c  .py  .java
.js   .ts  .html  .css
.json .sh
```

---

## ⚙️ Requirements

* C++17 compatible compiler

### Linux

* GCC 8+ or Clang with filesystem support

### Windows

* MinGW OR Visual Studio 2019+

Check version:

```bash
g++ --version
```

---

## 🛠️ Compilation

### 🐧 Linux (Arch / Ubuntu)

```bash
g++ FileOrganizer.cpp -o organizer -std=c++17
```

Run:

```bash
./organizer
```

---

### 🪟 Windows (MinGW)

```bash
g++ FileOrganizer.cpp -o organizer.exe -std=c++17
```

Run:

```bash
organizer.exe
```

---

### 🪟 Windows (Visual Studio)

1. Create **Console Application**
2. Replace `main.cpp` with `FileOrganizer.cpp`
3. Set language standard:

```
Project Properties → C/C++ → Language → C++17
```

4. Build and Run.

---

## 📂 Folder Structure Created

```
Documents/
 ├── Programs/
 ├── Archives/
 └── Others/
```

Folders are created automatically if they do not exist.

---

## 🔄 Automation (Optional)

### Linux — Run Every Hour

```bash
crontab -e
```

Add:

```
0 * * * * /home/USERNAME/organizer
```

---

### Windows — Run Automatically

1. Open **Task Scheduler**
2. Create Basic Task
3. Select trigger:

   * At logon OR Daily
4. Action → Start Program
5. Select `organizer.exe`

---

## ⚠️ Notes

* Only top-level files in Desktop and Downloads are processed.
* Existing files with the same name may be skipped.
* System/hidden files are ignored.
* Administrator/root privileges are not required.

---

## 📈 Future Improvements

* Real-time monitoring (auto organize instantly)
* Configurable rules via JSON
* Duplicate file detection
* GUI interface
* Logging system
* Undo operation

---

## 📜 License

Open-source — free to use and modify for learning and personal projects.

---

## 👨‍💻 Author

C++ filesystem automation project demonstrating cross-platform file management using modern C++.
