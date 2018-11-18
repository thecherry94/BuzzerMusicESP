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


bool importNotes_exportMusic(const char* input_file, const char* output_file);



int main(int argc, char** argv)
{
    if (argc < 3)
    {
        cout << "Too few parameters!\n";
        cout << "Syntax: program input_file_name output_file_name\n";

        return -1;
    }

    const char* input_file = argv[1];
    const char* output_file = argv[2];

    return importNotes_exportMusic(input_file, output_file);
}

bool importNotes_exportMusic(const char* input_file, const char* output_file)
{
    std::vector<MusicTone> music;

    // Import logic here
    #pragma region Import & Processing
    

    map<char, double> m;
    m['A'] = A; 
    m['B'] = B; 
    m['C'] = C; 
    m['D'] = D; 
    m['E'] = E;
    m['F'] = F; 
    m['G'] = G; 

    

    int fd_import = open(input_file, O_RDWR | O_CREAT, 0644);

    char line_buf[1024];
    char char_buf;
    int i = 0;
    while(read(fd_import, &char_buf, sizeof(char)))
    {
        if (char_buf == '\n')
        {
            float dur;
            char note;
            int oct;

            
            sscanf(line_buf, "%c%d %f", &note, &oct, &dur);
            
            #ifdef __DEBUG__
                cout << line_buf << endl;
                cout << "Note:\t\t" << note << endl;
                cout << "Octave:\t\t" << oct << endl;
                cout << "Duration:\t" << dur << endl << endl;
            #endif

            MusicTone tone;
            tone.duration = dur;
            tone.frequency = m[note] * (1 << oct);

            music.push_back(tone);            

            memset(&line_buf[0], 0, sizeof(line_buf));
            i = 0;
            continue;
        }

        line_buf[i] = char_buf;
        i++;
    }

    close(fd_import);

    #pragma endregion



    // Export logic here
    #pragma region Export 

    int fd_export = open(output_file, O_RDWR | O_CREAT, 0644);
    size_t num_elem = music.size();

    write(fd_export, &num_elem, sizeof(size_t));

    for(int i = 0; i < music.size(); i++)
    {
        write(fd_export, &music[i], sizeof(MusicTone));
    }
    close(fd_export);

    #pragma endregion


    return true;
}