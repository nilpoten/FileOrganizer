#include <iostream>
#include <filesystem>
#include <map>
#include <algorithm>
#include <cstdlib>

namespace fs = std::filesystem;
using namespace std;

/* ---------- EXTENSION → CATEGORY ---------- */

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

    // Programs / Code
    {".cpp","Programs"}, {".c","Programs"},
    {".py","Programs"}, {".java","Programs"},
    {".js","Programs"}, {".html","Programs"},
    {".css","Programs"}
};

/* ---------- SKIP SYSTEM / DANGEROUS FOLDERS ---------- */

bool shouldSkip(const fs::path& p)
{
    string name = p.filename().string();

    return name == "AppData" ||
           name == "Windows" ||
           name == "Program Files" ||
           name == "Program Files (x86)" ||
           (!name.empty() && name[0] == '.');
}

/* ---------- SAFE MOVE FUNCTION ---------- */

void moveSafe(const fs::path& src, const fs::path& destFolder)
{
    try
    {
        fs::create_directories(destFolder);

        fs::path dest = destFolder / src.filename();

        int count = 1;

        // prevent overwrite
        while (fs::exists(dest))
        {
            dest = destFolder /
                (src.stem().string() + "_" +
                 to_string(count++) +
                 src.extension().string());
        }

        fs::rename(src, dest);

        cout << "Moved: " << src.filename()
             << " -> " << destFolder << endl;
    }
    catch (...)
    {
        // ignore permission or locked files
    }
}

/* ---------- MAIN ---------- */

int main()
{
    cout << "=== Smart File Organizer (Windows) ===\n";

    const char* user = getenv("USERPROFILE");

    if (!user)
    {
        cout << "Cannot detect USERPROFILE.\n";
        return 1;
    }

    fs::path home(user);

    /* Destination folders (REAL Windows folders) */

    map<string, fs::path> dest = {
        {"Pictures",  home / "Pictures"},
        {"Videos",    home / "Videos"},
        {"Music",     home / "Music"},
        {"Documents", home / "Documents"},
        {"Programs",  home / "Documents" / "Programs"}
    };

    cout << "Scanning user directory...\n";

    fs::recursive_directory_iterator it(
        home,
        fs::directory_options::skip_permission_denied);

    fs::recursive_directory_iterator end;

    for (; it != end; ++it)
    {
        try
        {
            fs::path current = it->path();

            /* Skip system folders */
            if (it->is_directory() && shouldSkip(current))
            {
                it.disable_recursion_pending();
                continue;
            }

            if (!it->is_regular_file())
                continue;

            fs::path file = current;

            string ext = file.extension().string();
            transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

            if (!category.count(ext))
                continue;

            string cat = category[ext];
            fs::path correctFolder = dest[cat];

            // already in correct location
            if (file.parent_path() == correctFolder)
                continue;

            moveSafe(file, correctFolder);
        }
        catch (...)
        {
            // skip inaccessible files
        }
    }

    cout << "\n✅ Organization Complete\n";
    return 0;
}