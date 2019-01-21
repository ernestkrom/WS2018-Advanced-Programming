#include <iostream>
#include <string>
#include <unistd.h>
#include <stdio.h>

using namespace std;

void invokeManual() {
    cout << "USAGE: mytar [--store|--restore|--help] dest src {src}"
            "\n\t--store:    packs all src into [dest]"
            "\n\t--restore:  unpacks all files stored in [dest] into the current directory"
            "\n\t--help:     this screen";
}

int main(int argc, char *argv[]) {
    try {
        //operation
        string ops = argv[1];

        //identify current directory
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));

        //store src and dest locations
        auto src = string(cwd) + "/src";
        auto dest = string(cwd) + argv[2] + "/packed";

        if (ops == "--store") {

        } else if (ops == "--restore") {

        } else {
            invokeManual();
        }
    }
    catch (const exception &e) {
        cout << e.what() << endl;
        invokeManual();
    }
}