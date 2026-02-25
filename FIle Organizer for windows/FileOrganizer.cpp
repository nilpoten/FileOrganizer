#include <iostream>
#include <filesystem>
#include <map>
#include <vector>
#include <algorithm>
#include <cstdlib>

namespace fs = std::filesystem;
using namespace std;

/* ---------------- FILE TYPE MAP ---------------- */

map<string,string> category = {

    {".jpg","Pictures"}, {".jpeg","Pictures"},
    {".png","Pictures"}, {".gif","Pictures"},
    {".bmp","Pictures"},

    {".mp4","Videos"}, {".mkv","Videos"},
    {".avi","Videos"}, {".mov","Videos"},

    {".mp3","Music"}, {".wav","Music"},
    {".flac","Music"},

    {".pdf","Documents"}, {".docx","Documents"},
    {".txt","Documents"},

    {".cpp","Programs"}, {".c","Programs"},
    {".py","Programs"}, {".java","Programs"},
    {".js","Programs"}
};

/* ---------------- GLOBAL COUNTERS ---------------- */

int movedCount = 0;
int scannedCount = 0;

/* ---------------- SAFE MOVE ---------------- */

void moveSafe(const fs::path& src, const fs::path& destFolder)
{
    std::error_code ec;

    fs::create_directories(destFolder, ec);

    fs::path dest = destFolder / src.filename();

    int n = 1;
    while (fs::exists(dest))
    {
        dest = destFolder /
            (src.stem().string() + "_" +
             to_string(n++) +
             src.extension().string());
    }

    fs::rename(src, dest, ec);

    if (!ec)
    {
        movedCount++;
        cout << "[MOVED] "
             << src.filename()
             << " -> "
             << destFolder.filename()
             << endl;
    }
}

/* ---------------- ORGANIZE ---------------- */

void organizeFolder(const fs::path& folder,
                    map<string,fs::path>& destinations)
{
    error_code ec;

    if (!fs::exists(folder)) return;

    cout << "\nScanning: " << folder.filename() << endl;

    fs::recursive_directory_iterator it(
        folder,
        fs::directory_options::skip_permission_denied,
        ec);

    fs::recursive_directory_iterator end;

    while (it != end)
    {
        if (ec)
        {
            ec.clear();
            it.increment(ec);
            continue;
        }

        scannedCount++;

        const fs::path file = it->path();

        /* Skip symlinks / junctions */
        if (fs::is_symlink(file, ec))
        {
            it.disable_recursion_pending();
            it.increment(ec);
            continue;
        }

        if (fs::is_regular_file(file, ec))
        {
            string ext = file.extension().string();
            transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

            if (category.count(ext))
            {
                fs::path correct = destinations[category[ext]];

                if (file.parent_path() != correct)
                    moveSafe(file, correct);
            }
        }

        it.increment(ec); // ⭐ SAFE increment (no crash)
    }
}

/* ---------------- MAIN ---------------- */

int main()
{
    cout << "====================================\n";
    cout << "      SMART FILE ORGANIZER\n";
    cout << "====================================\n";

    const char* user = getenv("USERPROFILE");

    if (!user)
    {
        cout << "USERPROFILE not found.\n";
        return 1;
    }

    fs::path home(user);

    map<string, fs::path> destinations = {
        {"Pictures",  home/"Pictures"},
        {"Videos",    home/"Videos"},
        {"Music",     home/"Music"},
        {"Documents", home/"Documents"},
        {"Programs",  home/"Documents"/"Programs"}
    };

    vector<fs::path> folders = {
        home/"Desktop",
        home/"Downloads",
        home/"Documents",
        home/"Pictures",
        home/"Videos",
        home/"Music"
    };

    for (auto& f : folders)
        organizeFolder(f, destinations);

    /* -------- SUMMARY -------- */

    cout << "\n====================================\n";
    cout << "Organization Completed Successfully!\n";
    cout << "Files scanned : " << scannedCount << endl;
    cout << "Files moved   : " << movedCount << endl;
    cout << "====================================\n";

    cout << "\nThank you for using Smart File Organizer ;)\n";

    system("pause"); // keeps terminal open on Windows
    return 0;
}