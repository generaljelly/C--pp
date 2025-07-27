#include <iostream>
#include <fstream>
#include <string>
// soundfile.sapp.org/doc/WaveFormat for wav struct
typedef struct  WAV_HEADER{
    char                RIFF[4];        // Magic header == "RIFF"
    uint32_t            ChunkSize;      // Entire file size - 8 bytes 
    char                WAVE[4];        // WAVE Header  == "WAVE" 
    char                SubChunk1ID[3]; // == "fmt"
    uint32_t            SubChunk1Size;
    uint16_t            AudioFormat; // PCM == 1 (linear quant)
    uint16_t            NumChannels; // 1 for mono, 2 for stereo
    uint32_t            SampleRate;
    uint32_t            ByteRate;
    uint16_t            BlockAlign; // n0 of bites in one sample, all channels
    uint16_t            BitsPerSample; // IMPORTANT
    // check if pcm =! 1, may hold extra params like:
    // uint16_t extraparamsize
    // extraparams
    //char                SubChunk2ID[4]; // == "data"
    //uint32_t            SubChunk2Size; // NumSamples * NumChannels * BitsPerSample/8
    //                                    actual data size 
    
} wav_hdr;


void validateAudio(wav_hdr buffer) {
    if (!(buffer.RIFF[0] == 'R' && buffer.RIFF[1] == 'I' && buffer.RIFF[2] == 'F' && buffer.RIFF[3] == 'F')) {
        std::cout << "Invalid File Type" << std::endl; exit(1);
    }
    if (!(buffer.WAVE[0] == 'W' && buffer.WAVE[1] == 'A' && buffer.WAVE[2] == 'V' && buffer.WAVE[3] == 'E')) {
        std::cout << "Invalid File Type" << std::endl; exit(1);
    }
    if (!(buffer.SubChunk1ID[0] == 'f' && buffer.SubChunk1ID[1] == 'm' && buffer.SubChunk1ID[2] == 't')) {
        std::cout << "Invalid File Type" << std::endl; exit(1);
    }
    std::cout << "SubChunk1Size: " << buffer.SubChunk1Size << "\n\n"; // SKIP ANYTHING OUT OF THIS RANGE (ftell() +  subchunk1size)
    std::cout << "Audio Format (PCM) :" << buffer.AudioFormat << "\n\n";
    std::cout << "NumChannels: " << buffer.NumChannels << "\n\n";
    std::cout << "BlockAlign: " << buffer.BlockAlign<< "\n\n";
    std::cout << "Bits per Sample: " << buffer.BitsPerSample << "\n\n";

        //std::cout << "Raw Data Size: " << buffer.SubChunk2Size << "\n" << std::endl;


    
}


int main(void) {
    FILE * audioRead;
    wav_hdr buffer;
    
    //uint16_t* zeroedOut; // take care of initial empty space in data

    //size_t result;

    audioRead = fopen("file_example_WAV_1MG.wav", "r");

    if (audioRead == NULL) {
        std::cout << "File doesn't exist" << std::endl; exit(1);
    }

    
    else {
        fseek(audioRead, 0, SEEK_END);
        //long size = ftell(audioRead);
        rewind(audioRead);
        //std::cout << size << std::endl;
        //fseek(audioRead, 100000, SEEK_SET);

        int size = sizeof(wav_hdr);


        fread(&buffer,size,1,audioRead); // read wav header into buffer

        std::cout << ftell(audioRead) << std::endl;

        validateAudio(buffer); 
        //fclose(audioRead);
        //exit(1);
        int j = 0;
        char data;

        while (j < 100) {
            fseek(audioRead, j, SEEK_SET);
            data = fgetc(audioRead);
            if (data == 'd') {
                fseek(audioRead, ++j, SEEK_SET);
                if (data =='a') {
                    std::cout << "found: " << ftell(audioRead) - 1 << std::endl; 
                    exit(1);
                }
            }
            j++;
        }
        /*
        buffer.SubChunk2Size = 
        
        size_t fileSize = buffer.ChunkSize + 8;
        //char* readFile = malloc()
        size_t rawDataSize = buffer.SubChunk2Size;
    
        switch (buffer.BitsPerSample) {
            case 8:
                uint8_t* rawData;
            case 16:
                uint16_t* rawData;
            case 32:
                uint32_t* rawData;
        }
    

       uint8_t* rawData = (uint8_t*) malloc(rawDataSize); // rawData array for analysis
    
       if (rawData == NULL) {
            std::cout << "Error Allocating Memory"; exit(2);
        }
    /*
        FILE * write;
        write = fopen("rawData.txt", "w");
        if (write == NULL) {
            std::cout << "Couldn't create write file pointer" << std::endl; exit(3);
        }
    */
   /*
        //fseek(audioRead, 100, SEEK_CUR);
        std::cout << ftell(audioRead) << std::endl;
        uint16_t sample, i = 0;
        while (ftell(audioRead) < 1000) {
            sample = fgetc(audioRead);
            std::cout << sample << " ";
            if (!i % 10) {
                std::cout << std::endl;
            }
            *(rawData + i) = sample;
            i++;
        }
        
        //std::cout << *(zeroedOut + 1) << std::endl;
        
        free(rawData);
*/
  //if (result != size) {fputs ("Reading error",stderr); exit (3);}
    }
    fclose(audioRead);
    //fclose(write);
}

