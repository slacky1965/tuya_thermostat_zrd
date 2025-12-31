## Краткое описание термостата с сигнатурой

	"_TZE204_szbxmorb"
	
### Внешний вид.

<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/model4.png"/>

### Настройки, доступные удаленно.

<img src="https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/images/thermostat_r0с_exposes.jpg"/>

### Расписание.

Расписание имеет 7 вхождений по 4 периода.

	1. Понельник.
	2. Вторник.
	3. Среда.
	4. Четверг.
	5. Пятница.
	6. Суббота.
	7. Воскресенье.

Один период - часы, минуты и температура включения.

### Note

Это следующая версия термостата [_TZE204_xyugziqv]("https://raw.githubusercontent.com/slacky1965/tuya_thermostat_zrd/refs/heads/main/doc/thermostats/tuya_thermostat_r04/README.md"). Судя по всему все тоже самое, что у предыдущей модели, за исключением - влажность добавили в `DataPoint` и теперь ее можно вытащить наружу. У предыдущей версии она была только на экране. Но точность этого датчика оставляет желать лучшего. Ну еще из нюансов - при изменении яркости она меняется в настройках, но не отрабатывает на устройстве, пока на нем самом кнопки не понажимать.
