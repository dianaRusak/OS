Лабораторная работа № 10

1) Предположим, что процесс открывает файл на чтение по единственной жесткой ссылке 
(hard link) на существующий файл. В процессе этого чтения другой процесс удаляет 
эту ссылку. Что случится с операцией чтения первым процессом? Она завершится успешно?
Написать программу и протестировать (также объяснить результат на основе документации). 

в операционных системах на базе ядра Linux вся информация о файле привязана не к его имени, 
а так называемому числовому индексному дескриптору. У каждого файла есть свой уникальный 
индексный дескриптор, к которому привязаны сведения об этом файле: в каких блоках диска 
хранится его содержимое, размер, время создания, модификации и др.

Индексные дескрипторы файлов хранятся в специальной таблице. Каждый логический и 
физический диск имеет собственную таблицу дескрипторов.

Именно номер индекса является истинным именем файла в системе. Мы можем их увидеть с 
помощью ключа -i команды ls.

![logo](https://i.ibb.co/SdQD3yh/2020-06-04-10-39-57.png)

К файлу test1.txt можно создать ещё одну ссылку и назвать её test2.txt. Это делается следующим образом:

ln test1.txt test2.txt

Теперь с помощью команды ls -i можно увидеть, что оба файла относятся к одному и тому же индексному дескриптору:

![logo](https://i.ibb.co/QvkdQJq/2020-06-04-10-51-40.png)

Имя файла, ссылающееся на его индексный дескриптор, называется жесткой ссылкой. 

Поскольку файл в операционной системе однозначно определяет только номер его дескриптора, 
а имя файла является лишь указателем-ссылкой на него, то очевидно таких ссылок можно создать множество.

Можно провести аналогию: перед населенным пунктом на трассе на него много указателей,
но все они указывают на одно и то же место.

Следствием механизма жестких ссылок Linux является то, что удаление жесткой ссылки на 
файл не приводит к удалению самого файла из системы при наличии у этого файла других 
жестких ссылок (имен файла). И это понятно, так как все жесткие ссылки равны между собой, 
независимо от времени создания, местонахождения в структуре каталогов и др.

Файл будет доступен системе, пока будет существовать хотя бы одна жесткая ссылка на него. 
В случае удаления всех ссылок, файл удалится из системы, так как станет просто недоступен.

Или, как сказано в документации:

    You can delete a file with unlink or remove.
    Deletion actually deletes a file name. If this is the file’s only name, then the 
    file is deleted as well. If the file has other remaining names (see Hard Links), 
    it remains accessible under those names. © https://www.gnu.org/software/libc/manual/html_node/Deleting-Files.html

"Вы можете удалить файл с отменой ссылки или удалить.
 Удаление фактически удаляет имя файла. Если это единственное имя файла, то файл также удаляется. 
 Если файл имеет другие оставшиеся имена (см. Жесткие ссылки), он остается доступным под этими именами."

Создаем программу для чтения файла в бесконечном цикле, для корректной работы
на каждой новой итерации передвигаем указатель в начало файла.
Внутри бесконечного цикла просто выводим счетчик символов.

Создаем программу для удаления ссылки. Она содержит метод unlink.

    int unlink(const char *fname)
    Описание: 
    
    Функция unlink() удаляет указанный файл из каталога. 
    В случае успеха функция возвращает 0, а при неудаче —1.
    
в clion запускаем программу с бесконечным циклом
в терминале запускаем программу удаления ссылки
видим, что файл test1.txt удален, но test2.txt еще жив и по-прежнему имеет номер индекса 
одинаковым с удаленным файлом.

2) Каково время выполнения программы, содержащей  2,000,000 инструкций на процессоре  
8 MHz, когда каждая инструкция занимает 4 цикла. 

Программа содержит 2,000,000 инструкций на процессоре, каждая инструкция занимает 4 цикла.  
Всего будет выполнено 

    2,000,000 * 4 = 8,000,000 операций. 

Тактовая частота процессора 8MHz = 8 000 000 Hz. 

Тактовая частота показывает нам, сколько процессор может произвести вычислений 
в единицу времени, а измеряется в:

    Hz = 1(с)^-1.

Исходя из определения  что процессор выполняет 8,000,000 вычислений в секунду.
  
Имеем:8,000,000 операций для вычисления, и скорость выполнения в 8,000,000 вычислений в секунду

Чтобы получить время выполнения просто поделим одно на другое

    8,000,000 / 8,000,000 = 1 (с)
    
Время выполнения программы = 1(с).


3) Рассмотреть систему, в которой виртуальный адрес 20 бит, а страница  1 KB. Сколько элементов в таблице страниц?

Необходимо отображать большое виртуальное адресное пространство в физическое, которое 
существенно меньшего размера. Пользовательский процесс должен иметь возможность 
осуществить запись по виртуальному адресу, а задача ОС – сделать так, чтобы записанная 
информация оказалась в физической памяти. В случае виртуальной памяти система 
отображения адресных пространств помимо трансляции адресов должна предусматривать 
ведение таблиц, показывающих, какие области виртуальной памяти в данный момент находятся 
в физической памяти и где именно размещаются.

Страничная память — способ организации виртуальной памяти, при котором единицей отображения 
виртуальных адресов на физические является регион постоянного размера (т. н. страница).

Из чего состоит виртуальный адрес страницы? 
Виртуальный адрес памяти может быть представлен парой (g, s), где 
g — номер сегмента, а s — смещение в сегменте. 
 
![logo](https://i.ibb.co/ts8H12h/2020-06-04-11-53-42.png)
 
При обычной организации таблицы страниц, логический адрес (для 32-разрядной архитектуры, 
при размере страницы 4 килобайта = 4096 байтов) разбивается на номер страницы (20 битов) 
и смещение внутри страницы (12 битов).
 
Размер виртуального адресса в битах = количеству бит под номер страницы + количество бит 
под смещение в странице => если хотим найти количество элементов, надо узнать количество 
бит отделяемых в виртуальном адрессе под номер страницы.

размер виртуального адресса в битах = 20 (условие)
количество бит под смещение в странице = log2(размер страницы) = log2(2^10) = 10 бит 

количество бит под номер страницы = 20 - 10 = 10 бит

Тогда возможное количество элементов в таблице страниц: 2^10 = 1024.

4) Рассмотреть алгоритмы диспетчеризации процессов (scheduling algorithms) по следующим критериям (метрикам)
(a) время ожидания (waiting time), 
(b) повышение приоритета "забытой" задачи (starvation), 
((c) время завершения (turnaround time), 
(d) вариативность времени завершения  (variance in turnaround time).
Какой из них приведет к высокой вариативности времени завершения?  


Управление процессами (диспетчеризация). Приоритеты процессов
Одной из важных задач, которую решает ОС является проблема, связанная с определением 
когда и каким процессам следует выделять ресурсы процессора — задача планирования 
загрузки процессоров. Существуют три уровня такого планирования

![logo](https://i.ibb.co/54cRX16/2020-06-04-12-26-42.png)

а) Планирование по принципу FIFO (first-in-first-out)
   
    Для всех процессов время ожидания в большинстве случиев является не минимальным, так как не оптимизируется.
   
   Принцип FIFO, «первый пришедший обслуживается первым», является наиболее простой 
   дисциплиной планирования. ЦП предоставляется процессам в порядке их прихода в 
   очередь готовности.
   
    вариативность времени завершения  (variance in turnaround time)
    большая, потому что процессы обслуживаются в порядке прихода в очередь готовности,
    поэтому перестановка влияет
    
    No starvation, потому что каждый процесс получает шанс быть выполненным через определенное время.
    Отсутствие приоритизации означает, что до тех пор, пока каждый процесс в конечном итоге завершается, нет голода
    
   После того, как процесс получает ЦП в свое распоряжение, он выполняется до завершения, 
   т.е. это дисциплина планирования без переключения, поэтому ее не рекомендуют использовать 
   в системах с разделением времени.
   Очередь типа FIFO
   
   ![logo](https://i.ibb.co/PN2bCRS/2020-06-04-12-34-43.png)
   
   Как правило, принцип FIFO редко используется самостоятельно в качестве основной 
   дисциплины обслуживания, чаще он комбинируется с другими дисциплинами.
   
б) Стратегия Shortest Job First (SJF)

С помощью этой стратегии планировщик организует процессы с наименьшим расчетным 
временем обработки, оставшимся следующим в очереди. Это требует дополнительных 
знаний или оценок времени, необходимого для завершения процесса. 

    Обеспечивает минимальное среднее время ожидания для заданного набора процессов.
    Общее время ожидания меньше, чем FIFO, однако, поскольку ни один процесс не 
    должен ждать окончания самого длинного процесса.

    Голодание возможно, особенно в загруженной системе с большим количеством 
    небольших процессов, которые выполняются.
    
    Для одного и того же набора доступных процессов нет никаких отклонений.

в)Round-robin scheduling
    
ППланировщик назначает фиксированную единицу времени для каждого процесса и 
циклически их просматривает. Если процесс завершается в течение этого отрезка 
времени, он завершается, иначе он переносится после предоставления шанса всем 
другим процессам. 

    время ожидания зависит от количества процессов, а не от средней длины процесса.
    
    Голодание никогда не может наступить, так как не дается никакого приоритета. 
    Порядок распределения единиц времени основан на времени прибытия процесса, аналогично FIFO.
    
    Для одного и того же набора доступных процессов нет никаких отклонений.
    
     
https://en.wikipedia.org/wiki/Scheduling_(computing)#First_come,_first_served
https://ru.qwe.wiki/wiki/Scheduling_(computing)
https://www.intuit.ru/studies/courses/641/497/lecture/11286?page=3