#include <iostream>
#include <fstream>
#include <string>
// soundfile.sapp.org/doc/WaveFormat for wav struct
typedef struct  WAV_HEADER{
    char                RIFF[4];        // RIFF Header      Magic header
    uint32_t            ChunkSize;      // RIFF Chunk Size  
    char                WAVE[4];        // WAVE Header    
    char                SubChunk1ID[3]; // "fmt"
    uint32_t            SubChunk1Size;
    uint16_t            AudioFormat;
    uint16_t            NumChannels; // 1 for mono, 2 for stereo
    uint32_t            SampleRate;
    uint32_t            ByteRate;
    uint16_t            BlockAlign; // n0 of bites in one sample, all channels
    uint16_t            BitsPerSample; // IMPORTANT
    // check if pcm =! 1, may hold extra params like:
    // uint16_t extraparamsize
    // extraparams
    char                SubChunk2ID[4]; // "data"
    uint32_t            SubChunk2Size; // NumSamples * NumChannels * BitsPerSample/8
    //                                    actual data size
} wav_hdr;


int main(void) {
    FILE * pfile;
    //FILE * write;
    wav_hdr buffer;
    size_t result;
    pfile = fopen("file_example_WAV_1MG.wav", "r");

    if (pfile == NULL) {
        std::cout << "File doesn't exist" << std::endl; exit(1);
    }
    else {
        fseek(pfile, 0, SEEK_END);
        //long size = ftell(pfile);
        rewind(pfile);
        //std::cout << size << std::endl;
/*
        //buffer = (char*) malloc(sizeof(char)*size);
        if (buffer == NULL) {
            std::cout << "memory error"; exit(2);
        }
        //write = fopen("gibber.txt", "a");
        //fseek(pfile, 100000, SEEK_SET);
*/
        int size = sizeof(wav_hdr);

        fread(&buffer,size,1,pfile);
        std::cout << buffer.SubChunk2ID[0] << std::endl;
        

        
            
        
  //if (result != size) {fputs ("Reading error",stderr); exit (3);}
    }


    fclose(pfile);
    //fclose(write);
    //free(buffer);
}