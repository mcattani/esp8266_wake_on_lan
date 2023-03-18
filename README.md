# esp8266_wake_on_lan
Repositorio del proyecto de prueba de envío de paquete WOL utilizando un ESP8266.

WOL o *Wake on Lan* es un estándar de redes que permite encender la pc de manera remota. En mi caso, que utilizo Gnu-Linux como sistema operativo, no tuve que hacer más que habilitar la opción de *wake on lan* en el *BIOS* de la pc.

> Wake-on-LAN está implementado utilizando un paquete especialmente diseñado llamado "Paquete mágico", el cual es enviado a todos los equipos en la red, entre ellos el dispositivo a ser encendido. El "paquete mágico" contiene la dirección MAC del equipo destino, un identificador numérico que tiene cada Tarjeta de Red u otros dispositivos de red en la computadora, que posibilita ser reconocido dentro de la red. (...) Si un "paquete mágico" es recibido y está direccionado a la dirección MAC del dispositivo, la Tarjeta de Red envía la señal a la fuente de energía o tarjeta madre para iniciar el encendido del sistema, muy similar a lo que acontece cuando se presiona el botón de encendido. [Fuente: Wikipedia](https://es.wikipedia.org/wiki/Wake_on_LAN) 

Para este proyecto entonces usaremos la placa **NodeMCU 8266**, dos leds de diferente color (en mi caso usé un led RGB) y un pulsador. La idea es que el ESP8266 se conecte a nuestro router (nos señale con los leds cuando se está conectando y cuando la conexión ha sito establecida exitosamente) y cuando presionamos el pulsador se envía el *paquete mágico*.

Como siempre el código está bastante comentado para que en cada paso se entienda lo que estamos haciendo. 

En este link: [https://thenerdyapprentice.blogspot.com/](https://thenerdyapprentice.blogspot.com/)   pueden encontrar la entrada completa del proyecto. 
