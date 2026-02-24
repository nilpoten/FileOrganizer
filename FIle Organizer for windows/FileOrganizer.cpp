#include <iostream>
#include <filesystem>
#include <map>
#include <algorithm>
#include <cstdlib>

namespace fs = std::filesystem;
using namespace std;

/* -------- EXTENSION → CATEGORY -------- */

map<string,string> category = {

    // images
    {".jpg","Pictures"}, {".jpeg","Pictures"},
    {".png","Pictures"}, {".gif","Pictures"},

    // videos
    {".mp4","Videos"}, {".mkv","Videos"},
    {".avi","Videos"}, {".mov","Videos"},

    // music
    {".mp3","Music"}, {".wav","Music"},

    // documents
    {".pdf","Documents"}, {".docx","Documents"},
    {".txt","Documents"}, {".pptx","Documents"},

    // programs
    {".cpp","Programs"}, {".c","Programs"},
    {".py","Programs"}, {".java","Programs"},
    {".js","Programs"}
};

/* -------- SKIP SYSTEM FOLDERS -------- */

bool shouldSkip(const fs::path& p)
{
    string name = p.filename().string();

    return name == "AppData" ||
           name == "Windows" ||
           name == "Program Files" ||
           name == "Program Files (x86)" ||
           name.starts_with(".");
}

/* -------- SAFE MOVE -------- */

void moveSafe(const fs::path& src, const fs::path& destFolder)
{
    try
    {
        fs::create_directories(destFolder);

        fs::path dest = destFolder / src.filename();

        int i = 1;
        while (fs::exists(dest))
        {
            dest = destFolder /
                (src.stem().string() + "_" +
                 to_string(i++) +
                 src.extension().string());
        }

        fs::rename(src, dest);

        cout << "Moved: " << src << " -> " << dest << endl;
    }
    catch(...) {}
}

/* -------- MAIN ORGANIZER -------- */

int main()
{
    const char* user = getenv("USERPROFILE");

    if(!user)
    {
        cout<<"User profile not found\n";
        return 1;
    }

    fs::path home(user);

    /* destination folders */
    map<string, fs::path> dest = {
        {"Pictures", home/"Pictures"},
        {"Videos", home/"Videos"},
        {"Music", home/"Music"},
        {"Documents", home/"Documents"},
        {"Programs", home/"Documents"/"Programs"}
    };

    cout<<"Scanning entire user directory...\n";

    for(auto& entry :
        fs::recursive_directory_iterator(
            home,
            fs::directory_options::skip_permission_denied))
    {
        try
        {
            if(entry.is_directory())
            {
                if(shouldSkip(entry.path()))
                    entry.disable_recursion_pending();
                continue;
            }

            if(!entry.is_regular_file())
                continue;

            fs::path file = entry.path();

            string ext = file.extension().string();
            transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

            if(!category.count(ext))
                continue;

            string cat = category[ext];
            fs::path correct = dest[cat];

            // already correct location
            if(file.parent_path() == correct)
                continue;

            moveSafe(file, correct);
        }
        catch(...) {}
    }

    cout<<"\n✅ Full system organization complete\n";
}