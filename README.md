# YADROTestTask
Проблема из коммита [e85f14e](https://github.com/idigitallegacy/YADROTestTask/commit/e85f14e8f562ca6afa6281ce9e4837e4e8425b64) была решена простой заменой `argv[0]` на `argv[1]` :))

Также были замечены несколько дополнительных багов. Fixed as much, as I've seen.
## Инструкции по установке
### Linux
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
4. Соберите исходники:
```bash
cmake .
make
```
5. Запустите (см. раздел "Запуск приложения")

### Windows
1. [Скачайте архив](https://github.com/idigitallegacy/YADROTestTask/archive/refs/heads/dev.zip)
2. Распакуйте его.
3. Соберите исходники:
```shell
cd <Path_to_unpacked_archive>\YADROTestTask-dev
cmake .
make
```
4. Запустите (см. раздел "Запуск приложения")

## Запуск приложения
### Linux
Из той же директории, в которой выполнялась команда `make` выполните:
```bash
./TestTask "<path_to_csv_file>"
```
<path_to_csv_file> может быть и абсолютным, и относительным. Например:
```bash
./TestTask "/home/Test/SomeTest.csv"
./TestTask "./TestData/DefaultTest.csv"
```
### Windows
Из той же директории, в которой выполнялась команда `make` выполните:
```shell
./TestTask.exe "<path_to_csv_file>"
```
Гарантируется, что программа работает, по меньшей мере, с **абсолютным** <path_to_csv_file> (например, `C:\test\data.csv`). С относительным запустить не удалось.

## Тестовые данные
### Bundled
В репозитории в директории `TestData` лежат тестовые файлы. Каждый из них, кроме:
```
./Data/*
./DataSize/*
./DefaultTest.csv
```
Завершится с ошибкой, соответствующей названию файла. Гарантируется, что на файлах из категорий выше программа работает корректно (с оговоркой на порядок операторов сложения/умножения, пояснение см. в разделе "Известные проблемы"). Пояснения к файлам внутри `TestData`:
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
При выборе заголовка строки, разрешены только цифры. Пробелы и прочие символы не допускаются. Самая верхняя строка обязана быть пустой, остальные - обязаны быть непустыми.
Формально говоря, заголовки строки следуют правилу: `,<Row1>,<Row2>,...,<RowN>`, где `<RowN>` - строка, состоящая **исключительно** из символов набора `[0-9]`.

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

## Известные проблемы:
  - Между операторами в рамках ячейки не расставляются приоритеты (какой оператор встречен первым - тот и будет вычислен)
  - Нет проверки корректности названия переданного программе файла
  - Саморефенция (к примеру, A1: =B1; B1: =A1) проверяется ограничением на глубину рекурсии (что, естественно, не есть хорошо; однако в коде присутствуют "зарисовки" для нормального отлова таких циклов)
  - Адаптивность ввода недостаточна и не прощает ошибок и опечаток (например, в названии столбца `Cell ` (пробел в конце), а ячейка ссылается на `Cell`)
  - По моему мнению, "перегруженность" класса `Table`. Стоит разделить его, однако неясно, каким именно образом :)
  - Файлы в *.cpp, так как линковщик очень упорно ругался на Undefined Reference на объявленные и определенные методы/конструкторы. Как следствие, отказывался собирать программу.

## Устранение некоторых проблем/ошибок
#### Unable to open file
Проверьте правильность указания пути к файлу (см. раздел "Запуск приложения"). Также проверьте, чтобы он был доступен для чтения.
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
