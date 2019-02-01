#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>

using namespace std;

void invokeManual() {
    printf("USAGE: mytar [--store|--restore|--help] dest src {src}"
           "\n\t--store:    packs all src into [dest]"
           "\n\t--restore:  unpacks all files stored in [dest] into the current directory"
           "\n\t--help:     this screen\n");
}

int main(int argc, char *argv[]) {
    try {
        //operation
        string ops = argv[1];

        if (ops == "--store") {
            // open a file to store all others in it
            FILE *tarFile = fopen(argv[2], "wb");
            for (int i = 3; i < argc; i++) {
                printf("%s %s\n", argv[i], "stored");
                // open a file to read it's content
                FILE *srcFile = fopen(argv[i], "rb");
                if (srcFile != nullptr) {
                    // position the file pointer to the end of the file
                    fseek(srcFile, 0, SEEK_END);
                    // length of the file
                    size_t len = ftell(srcFile);
                    auto buffer = (char *) malloc((len + 1) * sizeof(char));
                    // reset the file pointer to the start of the file
                    rewind(srcFile);
                    fread(buffer, len, 1, srcFile);
                    // allocate memory and build a file header
                    auto fileHeader = (char *) malloc((60) * sizeof(char));
                    sprintf(fileHeader, "%zd%c%s%s", len, '-', argv[i], ":\0");

                    // finds the position in the file after the seperator(:)
                    // and writes the file content at that position
                    auto dpos = (char *) memchr(fileHeader, '\0', 60);
                    fwrite(fileHeader, dpos - fileHeader, 1, tarFile);
                    fwrite(buffer, len, 1, tarFile);
                }
                // closes the stored files
                fclose(srcFile);
            }
            // closes the packed file containing header and content
            // information of the other files
            fclose(tarFile);
            printf("stored");

        } else if (ops == "--restore") {
            // open the file to restore
            FILE *srcFile = fopen(argv[2], "rb");
            // array to store the file names
            char fName[50];
            // position the file pointer to the end of the file
            fseek(srcFile, 0, SEEK_END);
            // length of the file
            long len = ftell(srcFile);
            auto buffer = (char *) malloc((len + 1) * sizeof(char));
            // helper pointers
            char *dpos, *npos = buffer, *spos;
            // reset the file pointer to the start of the file
            rewind(srcFile);
            // store the whole file content in the buffer variable
            fread(buffer, len, 1, srcFile);
            // define the delimiter to seperate header information from data
            char delimiter = ':';

            do {
                size_t fileSize = strtol(npos, &spos, 10);
                // find position of first delimiter in the file content (60 because name<=50 and filesize<=10 bytes)
                dpos = (char *) memchr(npos, delimiter, 60);
                // copy name to file name (Parameter: target variable to store the copy,
                //position of the first char in the string,
                //size of the string)
                strncpy(fName, spos + 1, dpos - spos);
                // mark the end of the file name with a \0
                fName[dpos - spos - 1] = '\0';
                // print file name
                printf("%s", fName);
                // new line
                printf("\n");
                // restore a file
                FILE *newFile = fopen(fName, "wb");
                fwrite(dpos + 1, fileSize, 1, newFile);
                fclose(newFile);
                // calculate the new file position to find the next delimiter
                npos = dpos + fileSize + 1;
                // while there is data to restore in the srcFile
            } while (dpos != nullptr);
            fclose(srcFile);


        } else {
            invokeManual();
        }
    }
    catch (const exception &e) {
        printf("%s\n", e.what());
        invokeManual();
    }
    return 0;
}