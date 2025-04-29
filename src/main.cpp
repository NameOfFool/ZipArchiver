#include <iostream>
#include <zip.h>

int main(int argc, char* argv[]) {
    zip_t* archive;
    int err;
    char* name = "example.txt";
    archive = zip_open("example.zip", ZIP_CREATE, &err);
    if(archive == NULL){
        zip_error_t error;
        zip_error_init_with_code(&error, err);
        fprintf(stderr, "cannot open zip archive '%s': %s\n",
            name, zip_error_strerror(&error));
        zip_error_fini(&error);
        return -1;
    }
    else {
        zip_source_t* s;
        const char buf[] = "teststring";

        if ((s = zip_source_buffer(archive, buf, sizeof(buf), 0)) == NULL ||
            zip_file_add(archive, name, s, ZIP_FL_ENC_UTF_8) < 0) {
            zip_source_free(s);
            printf("error adding file: %s\n", zip_strerror(archive));
        }
        zip_close(archive);
    }
	return 0;
}