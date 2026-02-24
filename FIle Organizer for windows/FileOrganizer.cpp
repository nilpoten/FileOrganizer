#include <iostream>
#include <filesystem>
#include <map>
#include <vector>
#include <algorithm>
#include <cstdlib>

namespace fs = std::filesystem;
using namespace std;

/* -------- FILE TYPE → DESTINATION -------- */

map<string, string> categoryMap = {

    // Images
    {".jpg","Pictures"}, {".jpeg","Pictures"},
    {".png","Pictures"}, {".gif","Pictures"},
    {".bmp","Pictures"},

    // Videos
    {".mp4","Videos"}, {".mkv","Videos"},
    {".avi","Videos"},

    // Music
    {".mp3","Music"}, {".wav","Music"},

    // Documents
    {".pdf","Documents"}, {".docx","Documents"},
    {".txt","Documents"}, {".pptx","Documents"},

    // Programs
    {".cpp","Programs"}, {".c","Programs"},
    {".py","Programs"}, {".java","Programs"},
    {".js","Programs"}, {".html","Programs"}
};

/* -------- SAFE MOVE -------- */

void moveSafe(const fs::path& file, const fs::path& destinationFolder)
{
    try
    {
        fs::create_directories(destinationFolder);

        fs::path dest = destinationFolder / file.filename();

        int count = 1;

        // avoid overwrite
        while (fs::exists(dest))
        {
            dest = destinationFolder /
                (file.stem().string() + "_" +
                 to_string(count++) +
                 file.extension().string());
        }

        fs::rename(file, dest);

        cout << "Moved: " << file << " -> " << dest << endl;
    }
    catch (exception& e)
    {
        cout << "Error: " << e.what() << endl;
    }
}

/* -------- ORGANIZER -------- */

void organize(const fs::path& source,
              const map<string, fs::path>& destinations)
{
    if (!fs::exists(source)) return;

    cout << "\nScanning " << source << endl;

    for (auto& entry : fs::directory_iterator(source))
    {
        if (!entry.is_regular_file())
            continue;

        fs::path file = entry.path();

        string ext = file.extension().string();
        transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

        string category = "Others";

        if (categoryMap.count(ext))
            category = categoryMap[ext];

        fs::path destination = destinations.at(category);

        moveSafe(file, destination);
    }
}

/* -------- MAIN -------- */

int main()
{
    cout << "=== Smart Windows File Organizer ===\n";

    const char* user = getenv("USERPROFILE");

    if (!user)
    {
        cout << "User profile not found.\n";
        return 1;
    }

    fs::path home(user);

    /* DESTINATION FOLDERS (REAL WINDOWS ONES) */

    map<string, fs::path> destinations = {
        {"Pictures",  home / "Pictures"},
        {"Videos",    home / "Videos"},
        {"Music",     home / "Music"},
        {"Documents", home / "Documents"},
        {"Programs",  home / "Documents" / "Programs"},
        {"Others",    home / "Documents" / "Others"}
    };

    /* SOURCE FOLDERS TO CLEAN */

    vector<fs::path> sources = {
        home / "Desktop",
        home / "Downloads",
        home / "Documents"
    };

    for (auto& folder : sources)
        organize(folder, destinations);

    cout << "\n✅ Organization Finished\n";
}