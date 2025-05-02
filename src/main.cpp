#include <iostream>
#include <zip.h>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

bool zip_file(const char* file, const char* zipname) {
	zip_t* archive;
	int err;	
	archive = zip_open(zipname, ZIP_CREATE, &err);
	if (archive == NULL) {
		zip_error_t error;
		zip_error_init_with_code(&error, err);
		//TODO add output
		zip_error_fini(&error);
		return false;
	}

	if (!std::filesystem::exists(file)) {
		std::cerr << "Failed to open file" << std::endl;
		return false;
	}
	std::ifstream in(file, std::ios::binary);//TODO add if-> error
	std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

	zip_source_t* source = zip_source_buffer(archive, content.c_str(), content.size(), 0);
	if (source == nullptr) {
		std::cerr << "Failed to add file in archive:" << std::endl;
		return false;
	}
	if (zip_file_add(archive, file, source, ZIP_FL_ENC_UTF_8) < 0) {
		zip_source_free(source);
		std::cerr << "Failed to add file in archive:" << std::endl;
		return false;
	}


	zip_close(archive);	
	return true;
}

bool unzip_file(const char* zipname, const char* outputDir) {
	zip_t* archive;
	int err;
	archive = zip_open(zipname, ZIP_CREATE, &err);
	if (archive == NULL) {
		zip_error_t error;
		zip_error_init_with_code(&error, err);
		//TODO add output
		zip_error_fini(&error);
		return false;
	}
	fs::create_directory(outputDir);

	zip_int64_t numEntities = zip_get_num_entries(archive, 0);
	for (zip_int64_t i = 0; i < numEntities; i++) {
		struct zip_stat stat;
		zip_stat_init(&stat);
		zip_stat_index(archive, i, 0, &stat);

		zip_file_t* file = zip_fopen_index(archive, i, 0);

		fs::path outputPath = fs::path(outputDir) / stat.name;
		fs::create_directories(outputPath.parent_path());
		std::ofstream out(outputPath, std::ios::binary);
		if (!out) {
			zip_fclose(file);
			std::cerr << "Failed to create file: " << outputPath << std::endl;
			continue;
		}
		char buf[4096];
		zip_int64_t n;
		while ((n = zip_fread(file, buf, sizeof(buf)))) {
			out.write(buf, n);
		}
		zip_fclose(file);
		out.close();
		std::cout << "Extracted:" << outputPath << std::endl;
	}
	zip_close(archive);

	return true;
}
int main(int argc, char* argv[]) {
	zip_file("example.txt", "example.zip");
	unzip_file("example.zip", "ex");
	return 0;
}