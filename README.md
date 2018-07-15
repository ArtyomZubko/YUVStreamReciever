# YUVStreamReciever
A simple raw video stream reciever via TCP/UDP protocol.
**Requires OpenCV lib.**

- Для просмотра стрима на ПК необходимо запустить catch_stream.sh и запустить стрим на Raspberry c помощью команды sudo stream.sh &
- Далее, для запуска стрима и работы с геймпадом с Raspberry необходимо запустить start_gamepad_server.sh, который уже лежит в домашней папке pi, и программу GamepadTCPClient на ПК, предварительно скомпилировав её и запустив бинарник, либо просто запустить из Qt Creator проект программы в режиме Run.

