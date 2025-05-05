# ZipArchive


C++ Архиватор

# Описание
Простой архиватор, выполняющий 2 функции:
* Добавить 1 файл в архив
* Извлечь 1 файл из архива
# Особенности
* Кроссплатформенность
* Обработка больших файлов(больше 10ГБ)
* Процесс работы можно прервать в любой момент

# Основные требования
* Linux
* Windows
* [git](https://git-scm.com)
* [cmake](https://www.cmake.org)
* [gcc](https://gcc.gnu.org)

# Дополнительно(Если хотите компилятор, отличный от gcc):
* [clang](https://clang.llvm.org)
* [CLion](https://www.jetbrains.com/clion)
* [Cygwin](https://cygwin.com)
* [MSYS2](https://www.msys2.org)
* [MinGW](https://mingw-w64.org/doku.php)
* [Visual Studio](https://www.visualstudio.com)

# Сборка


### Загрузка репозитория
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
# Использование

### Windows
#### Добавление файла в архив 
```shell
ZipArchiver.exe a <original_file> <archive_file.zip>
```
#### Извлечение файла из архива
```shell
ZipArchiver.exe e <archive_file.zip> <original_file>
```
### Linux
#### Добавление файла в архив 
```bash
ZipArchiver a <original_file> <archive_file.zip>
```
#### Извлечение файла из архива
```bash
ZipArchiver e <archive_file.zip> <original_file>
```