#include <iostream>
#include <filesystem>
#include <map>
#include <vector>
#include <algorithm>
#include <cstdlib>

namespace fs = std::filesystem;
using namespace std;

/* ---------- FILE TYPE → DESTINATION ---------- */

map<string,string> category = {

    // Images
    {".jpg","Pictures"}, {".jpeg","Pictures"},
    {".png","Pictures"}, {".gif","Pictures"},
    {".bmp","Pictures"},

    // Videos
    {".mp4","Videos"}, {".mkv","Videos"},
    {".avi","Videos"}, {".mov","Videos"},

    // Music
    {".mp3","Music"}, {".wav","Music"},
    {".flac","Music"},

    // Documents
    {".pdf","Documents"}, {".docx","Documents"},
    {".txt","Documents"}, {".pptx","Documents"},
    {".xlsx","Documents"},

    // Programming files
    {".cpp","Programs"}, {".c","Programs"},
    {".py","Programs"}, {".java","Programs"},
    {".js","Programs"}, {".html","Programs"},
    {".css","Programs"}
};

/* ---------- SAFE MOVE ---------- */

void moveSafe(const fs::path& src, const fs::path& destFolder)
{
    try
    {
        fs::create_directories(destFolder);

        fs::path dest = destFolder / src.filename();

        int count = 1;
        while (fs::exists(dest))
        {
            dest = destFolder /
                (src.stem().string() + "_" +
                 to_string(count++) +
                 src.extension().string());
        }

        fs::rename(src, dest);

        cout << "Moved: "
             << src.filename()
             << " -> "
             << destFolder.filename() << endl;
    }
    catch (...) {}
}

/* ---------- ORGANIZE ONE FOLDER ---------- */

void organizeFolder(const fs::path& folder,
                    map<string,fs::path>& destinations)
{
    if (!fs::exists(folder)) return;

    cout << "Scanning: " << folder.filename() << endl;

    for (auto it = fs::recursive_directory_iterator(
            folder,
            fs::directory_options::skip_permission_denied);
         it != fs::recursive_directory_iterator();
         ++it)
    {
        try
        {
            if (!it->is_regular_file())
                continue;

            fs::path file = it->path();

            string ext = file.extension().string();
            transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

            if (!category.count(ext))
                continue;

            fs::path correctFolder = destinations[category[ext]];

            // already correct
            if (file.parent_path() == correctFolder)
                continue;

            moveSafe(file, correctFolder);
        }
        catch (...) {}
    }
}

/* ---------- MAIN ---------- */

int main()
{
    cout << "=== Smart File Organizer ===\n";

    const char* user = getenv("USERPROFILE");

    if (!user)
    {
        cout << "USERPROFILE not found\n";
        return 1;
    }

    fs::path home(user);

    /* destination folders */

    map<string, fs::path> destinations = {
        {"Pictures",  home/"Pictures"},
        {"Videos",    home/"Videos"},
        {"Music",     home/"Music"},
        {"Documents", home/"Documents"},
        {"Programs",  home/"Documents"/"Programs"}
    };

    /* SAFE folders to scan */

    vector<fs::path> scanFolders = {
        home/"Desktop",
        home/"Downloads",
        home/"Documents",
        home/"Pictures",
        home/"Videos",
        home/"Music"
    };

    for (auto& folder : scanFolders)
        organizeFolder(folder, destinations);

    cout << "\n✅ Organization Complete\n";
    return 0;
}