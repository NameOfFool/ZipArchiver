#include <filesystem>
#include <zip.h>
#include <thread>
#include <atomic>

extern std::atomic<bool> interrupt_flag;


namespace fs = std::filesystem;

/**
 * ���������� 1 ���� � ZIP-�����.
 * @param file �������� �����
 * @param zipname �������� ������ (example.zip)
 * @return 0 - �����, 1 - ������, 2 - �������� �������������
 */
int zip_file(const char* file, const char* zipname);

/**
 * ��������� 1 ���� �� ZIP-�����.
 * @param zipname �������� ������ (example.zip)
 * @param filename �������� ����� (������ ���� � ������)
 * @return 0 - �����, 1 - ������, 2 - �������� �������������
 */
int unzip_file(const char* zipname, const char* filename);

void progress_callback(zip_t* archive, double percentage, void* ud);
int cancel_callback(zip_t* archive, void* ud);

