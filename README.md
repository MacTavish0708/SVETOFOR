Микроконтроллер управления светофором
============================================
Алгоритм работы:
----------------

1. Реализовать дорожный (транспортный) светофор. Три цвета. Два режима

работы: - Выключенное состояние: каждую секунду моргает желтый смот.

-Включенное состояние:

* горит только зеленый сигнал 10 b. зеленый сигнал мигает 3 с.;

* зеленый сигнал мигает 3 с;

* гаснет зеленый, кагорается желтый (горит 2 с.);

* гаснет желтый, загорается красный (горит 10 с);

* загорается желтый и горит вместе с красным (горит 2 с.).

* гаснут желтый и красный и все повторяется с пункта

2. Реализовать пешеходный светофор и кнопку для пешеходо которую, пешеход уведомляет о желании перейти дорогу (эта часть в коде закомментирована).

* пока не нажата кнопка, горит красный сигнал • при нажатии кнопки пешеходный светофор ждет 10 секунд. пока
дорожный светофор приключиться на красный:

* загорается зеленый (горит 4 с.);

* Зеленый начинает моргать (5 с.);

* загорается красный; транспортный светофор переходит в рабочий режим:

В течение заданного промежутка времени после зеленого на пешеходном светофоре нажатие кнопки пешеходом не запускает алгоритм перехода. (20 с.) Алгоритм перехода запускается в таком случае только по истечению заданного времени.