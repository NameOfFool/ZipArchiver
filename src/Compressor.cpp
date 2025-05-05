#include <iostream>
#include <fstream>
#include <indicators/progress_bar.hpp>
#include <Compressor.h>

namespace fs = std::filesystem;
std::atomic<bool> interrupt_flag(false);

int zip_file(const char* file, const char* zipname) {

	zip_t* archive;
	int err;


	archive = zip_open(zipname, ZIP_CREATE, &err);
	if (archive == NULL) {
		std::cerr << "Failed to create archive:" << err << std::endl;
		return 1;
	}

	try {
		if (!std::filesystem::exists(file)) {
			throw std::runtime_error("Failed to open file");
			return 1;
		}
		std::ifstream in(file, std::ios::binary | std::ios::ate);

		indicators::ProgressBar bar{
			indicators::option::BarWidth{50},
			indicators::option::ShowPercentage{true},
			indicators::option::ShowElapsedTime{true}
		};

		std::cout << "Progress:";
		zip_register_progress_callback_with_state(archive, 0.01, progress_callback, nullptr, &bar);
		zip_register_cancel_callback_with_state(archive, cancel_callback, nullptr, nullptr);

		zip_source_t* source = zip_source_file(archive, file, 0, ZIP_LENGTH_TO_END);

		if (source == nullptr) {
			throw std::runtime_error("Failed to add file in archive");
		}
		auto result = zip_file_add(archive, file, source, ZIP_FL_ENC_UTF_8);
		if (result < 0) {
			zip_source_free(source);
			throw std::runtime_error("Failed to add file in archive");
		}


		if (zip_close(archive)) {
			std::cerr << "Failed to save archive" << std::endl;
			return 1;
		}
		if (interrupt_flag) {
			std::remove(zipname);
			return 2;
		}
	}

	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		zip_discard(archive);
		zip_close(archive);
		std::remove(zipname);
		return 1;
	}
	return 0;
}

int unzip_file(const char* zipname, const char* filename) {
	zip_t* archive;
	int err;
	archive = zip_open(zipname, ZIP_CREATE, &err);

	std::string outputDir = std::string(zipname).substr(0, std::string(zipname).rfind("."));

	if (archive == NULL) {
		std::cerr << "Failed to create archive:" << err << std::endl;
		return 1;
	}

	try {
		fs::create_directory(outputDir.c_str());

		zip_int64_t numEntities = zip_get_num_entries(archive, 0);
		struct zip_stat stat;
		zip_stat_init(&stat);
		zip_stat(archive, filename, 0, &stat);

		zip_file_t* file = zip_fopen(archive, filename, 0);

		indicators::ProgressBar bar{
			indicators::option::BarWidth{50},
			indicators::option::ShowPercentage{true},
			indicators::option::ShowElapsedTime{true}
		};

		std::cout << "Extracting:" << stat.name;

		fs::path outputPath = fs::path(outputDir.c_str()) / stat.name;
		fs::create_directories(outputPath.parent_path());
		std::ofstream out(outputPath, std::ios::binary);
		if (!out) {
			zip_fclose(file);
			throw std::runtime_error(std::string("Failed to create file: ") + outputPath.string());
			return 1;
		}
		const size_t buffer_size = 10 * 1024 * 1024;
		std::vector<char> buffer(buffer_size);
		zip_int64_t n;
		while ((n = zip_fread(file, buffer.data(), buffer_size))) {
			if (interrupt_flag) {
				zip_fclose(file);
				out.close();
				std::cout << "Interrupted" << std::endl;
				std::remove(outputPath.string().c_str());
				std::remove(outputDir.c_str());
				return 2;
			}
			out.write(buffer.data(), n);
			auto s = buffer_size;
			bar.set_progress((double)fs::file_size(outputPath) / stat.size * 100);
		}
		zip_fclose(file);
		out.close();
		std::cout << "Extracted:" << outputPath << std::endl;
		zip_close(archive);
	}

	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		zip_discard(archive);
		zip_close(archive);
		std::remove(zipname);
		return 1;
	}
	return 0;
}
void progress_callback(zip_t* archive, double percentage, void* ud) {
	auto* bar = static_cast<indicators::ProgressBar*>(ud);
	bar->set_progress(percentage * 100);
}
int cancel_callback(zip_t* archive, void* ud) {
	if (interrupt_flag) {
		std::cout << "Interrupted" << std::endl;
		return 1;
	}
	return 0;
}