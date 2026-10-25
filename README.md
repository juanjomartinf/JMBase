# JMBase
Base for Juanjo's projects

## WiFi y servidores locales

Cada sketch registra sus redes con `JMBaseWiFi::addNetwork(ssid, password)`.
JMBase utiliza los tres primeros octetos de la puerta de enlace para calcular
el broker MQTT (`192.168.Y.20:1883`) y Home Assistant (`192.168.Y.21:8123`).

Desde 1.8.5 se actualizan los destinos al recuperar WiFi, aunque la conexion
inicial haya fallado o la red haya cambiado. `JMBaseMQTT::loopMQTT()` debe
seguir ejecutandose en el `loop()` del sketch.

## Ruta del firmware HTTP/OTA

Los sketches existentes conservan `/local/firmware/0.bin` por defecto.
Para elegir otro archivo, llamar en `setup()`:

```cpp
bool rutaValida = JMBaseMQTT::setFirmwarePath(
  "/local/firmware/caldera-xiao/1.0.0/firmware.bin"
);
```

La funcion acepta una ruta absoluta del HA local, no una URL completa.
Rechaza rutas vacias, espacios, controles, barras invertidas, consultas y
fragmentos; si devuelve `false`, mantiene la ruta anterior.
`getFirmwarePath()` devuelve la ruta y `getFirmwareURL()` la URL con el HA
de la red actual. La seleccion reside en RAM: cada firmware debe establecer
su propia ruta en `setup()`; no se hereda del sketch de preparacion.

La orden sigue siendo el mensaje `UPDATE` en `<topic>/_Debug`, **sin retain**.
Para la ruta del ejemplo, copiar el binario de aplicacion a
`/config/www/firmware/caldera-xiao/1.0.0/firmware.bin` en Home Assistant.
La descarga utiliza un cliente TCP separado del de MQTT.

Estos cambios no incorporan rollback automatico, firma de firmware ni
validacion del proyecto de destino. La ruta debe apuntar al binario de
aplicacion adecuado para el dispositivo, nunca a una imagen completa de flash.
