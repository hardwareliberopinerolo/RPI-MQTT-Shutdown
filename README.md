# RPI MQTT Shutdown
Shutdown RaspberryPi by MQTT

# Compilazione Demone
Caricare la libreria libmosquitto-dev

```
sudo apt-get install -y libmosquitto-dev
```

Compilazione il codice C

```
cc -o mqtt_shutdown  mqtt_shutdown.c -lmosquitto
```

# Procedura per attivare Demone 

```
sudo cp mqtt_shutdown /usr/local/bin
sudo chmod +x /usr/local/bin/mqtt_shutdown
sudo cp mqtt_shutdown.service /etc/systemd/system/
sudo chmod 640 /etc/systemd/system/mqtt_shutdown.service
sudo systemctl enable mqtt_shutdown
sudo systemctl start mqtt_shutdown
```

Verificare che il Demone sia attivo

```
sudo systemctl status mqtt_shutdown.service
```
