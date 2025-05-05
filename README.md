# ZipArchive


C++ ���������

# ��������
������� ���������, ����������� 2 �������:
* �������� 1 ���� � �����
* ������� 1 ���� �� ������
# �����������
* ��������������������
* ��������� ������� ������(������ 10��)
* ������� ������ ����� �������� � ����� ������

# �������� ����������
* Linux
* Windows
* [git](https://git-scm.com)
* [cmake](https://www.cmake.org)
* [gcc](https://gcc.gnu.org)

# �������������(���� ������ ����������, �������� �� gcc):
* [clang](https://clang.llvm.org)
* [CLion](https://www.jetbrains.com/clion)
* [Cygwin](https://cygwin.com)
* [MSYS2](https://www.msys2.org)
* [MinGW](https://mingw-w64.org/doku.php)
* [Visual Studio](https://www.visualstudio.com)

# ������


### �������� �����������
```shell
git clone https://github.com/NameOfFool/ZipArchiver
cd ZipArchiver
```

### Linux
```shell
./install_linux.sh
cd install
```

### Windows
```shell
./install_windows.bat
cd install
```
# �������������

### Windows
#### ���������� ����� � ����� 
```shell
ZipArchiver.exe a <original_file> <archive_file.zip>
```
#### ���������� ����� �� ������
```shell
ZipArchiver.exe e <archive_file.zip> <original_file>
```
### Linux
#### ���������� ����� � ����� 
```bash
ZipArchiver a <original_file> <archive_file.zip>
```
#### ���������� ����� �� ������
```bash
ZipArchiver e <archive_file.zip> <original_file>
```