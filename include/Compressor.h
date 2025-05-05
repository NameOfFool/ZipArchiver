#include <filesystem>
#include <zip.h>
#include <thread>
#include <atomic>

extern std::atomic<bool> interrupt_flag;


namespace fs = std::filesystem;

/**
 * Архивирует 1 файл в ZIP-архив.
 * @param file Название файла
 * @param zipname Название архива (example.zip)
 * @return 0 - успех, 1 - ошибка, 2 - прервано пользователем
 */
int zip_file(const char* file, const char* zipname);

/**
 * Извлекает 1 файл из ZIP-архив.
 * @param zipname Название архива (example.zip)
 * @param filename Название файла (должен быть в архиве)
 * @return 0 - успех, 1 - ошибка, 2 - прервано пользователем
 */
int unzip_file(const char* zipname, const char* filename);

void progress_callback(zip_t* archive, double percentage, void* ud);
int cancel_callback(zip_t* archive, void* ud);

