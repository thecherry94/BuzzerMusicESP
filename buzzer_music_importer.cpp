#include <iostream>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <map>


using namespace std;


#define A 27.50
#define B 30.87
#define C 32.70
#define D 36.70
#define E 41.20
#define F 43.65
#define G 49.00


#define __DEBUG__


struct MusicTone
{
    uint32_t frequency;
    double duration;
};


int main(int argc, char** argv)
{
    if (argc != 2)
    {
        cout << "Invalid parameters!\n";
        cout << "Syntax: program import_file_name\n";
    }

    const char* filename = argv[1];

    int fd = open(filename, O_RDONLY, 0644);

    size_t num_elem = 0;
    read(fd, &num_elem, sizeof(size_t));

    MusicTone buf;
    std::vector<MusicTone> music;
    music.reserve(num_elem);

    while(read(fd, &buf, sizeof(MusicTone)))
        music.push_back(buf);
    

    char* info = "";
    if(num_elem < music.size())
        info = "more";
    else if (num_elem > music.size())
        info = "less";

    if (strcmp(info, "") != 0)
        cout << "[WARNING] File contains " << info << " elements than specified\n";
    

    cout << "Number of tones: " << music.size() << endl;
    for(int i = 0; i < music.size(); i++)
    {
        cout << "Tone: " << music[i].frequency << "Hz | " << music[i].duration << "sec\n";
    }


    return 0;
}