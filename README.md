# YADROTestTask
![Build and test](https://github.com/idigitallegacy/YADROTestTask/actions/workflows/test-build.yml/badge.svg)

Проблема из коммита [e85f14e](https://github.com/idigitallegacy/YADROTestTask/commit/e85f14e8f562ca6afa6281ce9e4837e4e8425b64) была решена простой заменой `argv[0]` на `argv[1]` :))

Также были замечены несколько дополнительных багов. Fixed as much, as I've seen.
## Инструкции по установке
После скачивания проекта, не отключайтесь от интернета. Внутри `CMakeLists.txt` используется `fetchContent()` для определения библиотеки `googletest`. Во время сборки могут быть показаны следующие предупреждения:
```
CMake Warning (dev) at E:/CLion 2023.1.3/bin/cmake/win/x64/share/cmake-3.25/Modules/FetchContent.cmake:1284 (message):
  The DOWNLOAD_EXTRACT_TIMESTAMP option was not given and policy CMP0135 is
  not set.  The policy's OLD behavior will be used.  When using a URL
  download, the timestamps of extracted files should preferably be that of
  the time of extraction, otherwise code that depends on the extracted
  contents might not be rebuilt if the URL changes.  The OLD behavior
  preserves the timestamps from the archive instead, but this is usually not
  what you want.  Update your project to the NEW behavior or specify the
  DOWNLOAD_EXTRACT_TIMESTAMP option with a value of true to avoid this
  robustness issue.
Call Stack (most recent call first):
  CMakeLists.txt:7 (FetchContent_Declare)
This warning is for project developers.  Use -Wno-dev to suppress it.
```
Просто проигнорируйте их.
### Linux
Программа под Linux запускалась как из-под IDE CLion, так и из терминала (следуя указанным ниже инструкциям).

0. Убедитесь, что установлены `g++` и `cmake`. Если их нет:
```bash
sudo apt install g++
sudo apt install cmake
```
1. Создайте папку: 
```bash
mkdir testing_app
cd testing_app
```
2. Скачайте архив:
```bash
wget https://github.com/idigitallegacy/YADROTestTask/archive/refs/heads/dev.tar.gz
```
3. Распакуйте его:
```bash
tar -xvf dev.tar.gz
cd YADROTestTask-dev
```
4. Если необходимо, измените константы в `cfg.h` (например, константу `TEST_DATA_PATH` для запуска GTest).
5. Соберите исходники:
```bash
cmake .
make
```
6. Запустите (см. раздел ["Запуск приложения"](https://github.com/idigitallegacy/YADROTestTask/tree/dev#%D0%B7%D0%B0%D0%BF%D1%83%D1%81%D0%BA-%D0%BF%D1%80%D0%B8%D0%BB%D0%BE%D0%B6%D0%B5%D0%BD%D0%B8%D1%8F))

### Windows
Программа под Windows запускалась только из-под IDE CLion.

1. [Скачайте архив](https://github.com/idigitallegacy/YADROTestTask/archive/refs/heads/dev.zip)
2. Распакуйте его.
3. Если необходимо, измените константы в `cfg.h` (например, константу `TEST_DATA_PATH` для запуска GTest).
4. Соберите исходники:
```shell
<Path_to_cmake_executable>\cmake.exe <Path_to_unpacked_archive>\YADROTestTask-dev
<Path_to_make_executable>\make.exe <Path_to_unpacked_archive>\YADROTestTask-dev
```
5. Запустите (см. раздел ["Запуск приложения"](https://github.com/idigitallegacy/YADROTestTask/tree/dev#%D0%B7%D0%B0%D0%BF%D1%83%D1%81%D0%BA-%D0%BF%D1%80%D0%B8%D0%BB%D0%BE%D0%B6%D0%B5%D0%BD%D0%B8%D1%8F))

## Запуск приложения
### Linux
#### Main
Из той же директории, в которой выполнялась команда `make` выполните:
```bash
./TestTask "<path_to_csv_file>"
```
<path_to_csv_file> может быть и абсолютным, и относительным. Например:
```bash
./TestTask "/home/Test/SomeTest.csv"
./TestTask "./TestData/DefaultTest.csv"
```
#### GTest
Для проверки целостности установки, из той же директории, в которой выполнялась команда `make` выполните:
```bash
./TestTaskTest
```
Учтите, что, возможно, потребуется изменить константу `TEST_DATA_PATH` в файле `cfg.h` (в корне репозитория) на абсолютный путь, соответствующий директории `TestData` репозитория. Эта константа необходима только для запуска GTest-приложения и не влияет на работу основного консольного приложения.
### Windows
#### Main
Из той же директории, в которой выполнялась команда `make` выполните:
```shell
.\TestTask.exe "<path_to_csv_file>"
```
Гарантируется, что программа работает, по меньшей мере, с **абсолютным** <path_to_csv_file> (например, `C:\test\data.csv`). С относительным запустить не удалось.
#### GTest
Для проверки целостности установки, из той же директории, в которой выполнялась команда `make` выполните:
```bash
.\TestTaskTest.exe
```
Учтите, что, возможно, потребуется необходимо изменить константу `TEST_DATA_PATH` в файле `cfg.h` (в корне репозитория) на путь, соответствующий директории `TestData` репозитория. Эта константа необходима только для запуска GTest-приложения и не влияет на работу основного консольного приложения.

## Тестовые данные
### Bundled
В репозитории в директории `TestData` лежат тестовые файлы. Каждый из них, кроме:
```
./Data/*
./DataSize/*
./DefaultTest.csv
```
Завершится с ошибкой, соответствующей названию файла. Гарантируется, что на файлах из категорий выше программа работает корректно (с оговоркой на порядок операторов сложения/умножения, пояснение см. в разделе ["Известные проблемы"](https://github.com/idigitallegacy/YADROTestTask/tree/dev#%D0%B8%D0%B7%D0%B2%D0%B5%D1%81%D1%82%D0%BD%D1%8B%D0%B5-%D0%BF%D1%80%D0%BE%D0%B1%D0%BB%D0%B5%D0%BC%D1%8B)). Пояснения к файлам внутри `TestData`:
- `./DefaultTest.csv` - тест из условия
- `./Data/*` - обычные тестовые данные, проверяющие корректность вычислений
- `./DataSize/*` - тестовые данные, проверяющие работу таблицы на различных размерах данных
- `./Logic/*` - тестовые данные, проверяющие обработку логических ошибок (самореференция, деление на ноль и пр.)
- `./WrongInput/*` - тестовые данные, проверяющие обработку ошибок, связанных со вводом (например, `+A1+C1` вместо `=A1+C1`)
### Custom
При составлении тестовых данных, пожалуйста, следуйте оговоренному формату. А именно:

#### Разделители
Разделителями в таблице считаются символы `,`. В конце каждой строки входного файла разделитель обязан отсутствовать.

#### Заголовки столбца
При выборе заголовка столбца, разрешены только латинские заглавные и строчные символы. Пробелы и прочие символы не допускаются. Самый левый столбец обязан быть пустым, остальные - обязаны быть непустыми.

Формально говоря, заголовки столбца следуют правилу: `,<Col1>,<Col2>,...,<ColN>`, где `<ColN>` - строка, состоящая **исключительно** из символов набора `[A-Z]` или `[a-z]`.

#### Заголовки строки
Заголовок строки обязан быть в начале строки. При выборе заголовка строки, разрешены только цифры. Пробелы и прочие символы не допускаются. Самая верхняя строка обязана быть пустой, остальные - обязаны быть непустыми.
Формально говоря, заголовки строки следуют правилу:
```
,<Col1>,...<ColN>
<Row1>,<Cell_11>,...<Cell_1N>
.
.
.
<RowM>,<Cell_M1>...,<Cell_MN>
```
где:
- `<ColN>` - заголовок столбца;
- `<RowN>` - заголовок строки. Строка, состоящая **исключительно** из символов набора `[0-9]`;
- `<Cell_MN>` - значение ячейки `M`-ой строки `N`-ого столбца

#### Ячейки
Количество ячеек по горизонтали обязано совпадать с количеством непустых заголовков столбцов. Количество ячеек по вертикали, соответственно, с количеством непустых заголовков строк.

Значение ячейки обязано быть непустым. Пробелы, точки и прочие неоговоренные символы не допускаются.

##### Численные ячейки
При введении численных ячеек, разрешены только цифры.

##### Формульные ячейки
При введении формульных ячеек, разрешены только символ `=` (причем исключительно в начале строки), буквы, цифры и операторы из списка: `+ - / *`.

Учтите, что в формульных ячейках невозможно записать числовое значение. Иначе говоря, формула `=500+500` будет интерпретирована как "Ячейка "500" + Ячейка "500"", что приведет к ошибке `InvalidCellAddressException`.

Чтобы указать в формульной ячейке числовое значение, запишите его в другой ячейке и предоставьте ссылку на нее. Для формулы `=500+500`, она может быть преобразована в `=A2+A2`, ячейка `A2` будет числовой, а ее значение будет равно `500`.

## Дополнительный функционал
Программа умеет работать не только с ячейками вида `=ARG1<op>ARG2`, но и с произвольным числом (`=ARG1<op1>...<op_N>ARG_(N+1)`). Однако, при такой записи ячеек, на составителя данных возлагается ответственность правильного порядка следования операторов (условно, если записано `=ARG1+ARG2*ARG3`, будет выполнено сначала **сложение**, потом - умножение), в виду того, что в рамках тестового задания это сделать довольно сложно :)
  
Программа рассчитана не только на int, но и на любые целочисленные типы данных (к примеру, long long). С небольшими доработками, программа может быть масштабирована на, в том числе, числа с плавающей точкой.

Кроме того, если программа встречает ошибку в вводе, она умеет ее классифицировать и указывать строку/ячейку, в которой допущена (по логике программы) ошибка.

Также не рекомендую проверять чересчур большие объемы данных. На примере таблицы 100х100 (без ссылочных ячеек, только значения), она выполнялась в течение секунды (возможно, из-за медленного вывода `std::cout`).

## Известные проблемы
  - Между операторами в рамках ячейки не расставляются приоритеты (какой оператор встречен первым - тот и будет вычислен)
  - Производительность на уровне "не торт". Таблицу размером 100х100, судя по результатам GTest, программа обрабатывает в течение 1.914 секунды.
  - Нет проверки корректности названия переданного программе файла
  - Непрямая саморефенция (к примеру, A1: =B1; B1: =A1) проверяется ограничением на глубину рекурсии (что, естественно, не есть хорошо; однако в коде присутствуют "зарисовки" для нормального отлова таких циклов)
  - Адаптивность ввода недостаточна и не прощает ошибок и опечаток (например, в названии столбца `Cell ` (пробел в конце), а ячейка ссылается на `Cell`)
  - По моему мнению, "перегруженность" класса `Table`. Стоит разделить его, однако неясно, каким именно образом :)
  - Файлы в *.cpp, так как линковщик очень упорно ругался на Undefined Reference на объявленные и определенные методы/конструкторы. Как следствие, отказывался собирать программу.

## Устранение некоторых проблем/ошибок
#### Unable to open file
Проверьте правильность указания пути к файлу (см. раздел ["Запуск приложения"](https://github.com/idigitallegacy/YADROTestTask/tree/dev#%D0%B7%D0%B0%D0%BF%D1%83%D1%81%D0%BA-%D0%BF%D1%80%D0%B8%D0%BB%D0%BE%D0%B6%D0%B5%D0%BD%D0%B8%D1%8F)). Также проверьте, чтобы он был доступен для чтения.
#### Too few rows/columns
Проверьте правильность данных внутри csv-файла. Учтите также, что следующая таблица:
```
,A,B
1,2,
2,2,3
```
**НЕ эквивалентна**:
```
,A,B
1,2,0
2,2,3
```
#### Zero division reached
Ошибка деления на ноль. Учтите, что если в ячейке (после всех вычислений) в знаменателе стоит, к примеру, `0.5`, это также приведет к выбросу ошибки деления на ноль (так как дробные числа преобразуются в целые отбрасыванием дробной части при вычислении).
#### Self-referenced cell
Если вы на 100% уверены, что это не самореференсная ячейка, увеличьте константу `MAX_RECURSION_DEPTH` внутри файла `cfg.h` (находится в корне репозитория). По умолчанию, вычисления производятся до 100-й запрошенной ячейки.
#### Долгое выполнение программы
Программа опирается на хеш-таблицу. Если количество данных кратно превосходит 1000, стоит увеличить константу `TABLE_MAX_ELEMENTS` (чтобы не получать асимтотику хуже `O(n^2)`) внутри файла `cfg.h` (находится в корне репозитория). По умолчанию, в таблице максимум 1000 элементов по горизонтали и столько же по вертикали.
