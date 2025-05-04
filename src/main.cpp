#include "Compressor.h"
#include <csignal>
#include <atomic>
#include <iostream>


void handle_sigint(int) {
	interrupt_flag = true;
}


int main(int argc, char* argv[]) {
	signal(SIGINT, handle_sigint);
	int result = 1;
	if (argc != 4) {
		std::cerr << "Usage: ZipArchive a <original_file> <archive_file.zip>" << std::endl << "or" << std::endl;
		std::cerr << "ZipArchive e <archive_file.zip> <original_file>" << std::endl;
		return 1;
	}
	if (std::string(argv[1]) == "a") {
		std::string original_file = argv[2];
		std::string archive_file = argv[3];
		result = zip_file(original_file.c_str(), archive_file.c_str());
	}
	else if (std::string(argv[1]) == "e") {
		std::string archive_file = argv[2];
		std::string original_file = argv[3];
		result = unzip_file(archive_file.c_str(), original_file.c_str());
	}
	else {
		std::cerr << "Usage: ZipArchive a <original file> <archive file>" << std::endl << "or" << std::endl;
		std::cerr << "ZipArchive e <archive file> <original file>" << std::endl;
		return 1;
	}
	switch (result) {
	case 0: std::cout << "Success!" << std::endl; break;
	case 2: std::cout << "Interrupted, operation was canceled." << std::endl; break;
	default: std::cerr << "Error!" << std::endl;
	}

	return 0;
}
