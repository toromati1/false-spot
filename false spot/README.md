# ps5-bgm-player

Proyecto para hacer un reproductor de musica en segundo plano para PS5 con jailbreak, como alternativa a Spotify (que no funciona sin PSN).

## Estado

Por ahora solo hay un ELF de prueba (`main.c`) que toca un tono de 440 Hz por 10 segundos. Sirve para comprobar si se puede abrir un puerto de audio BGM y que suene a la vez que un juego.

El codigo esta sin probar y las firmas de las funciones de audio estan escritas de memoria (API de PS4), asi que puede que haya que ajustarlas.

## Compilar

Se necesita el SDK de https://github.com/ps5-payload-dev/sdk

    export PS5_PAYLOAD_SDK=/opt/ps5-payload-sdk
    make

Para enviarlo a la consola:

    export PS5_HOST=ip_de_la_ps5
    export PS5_PORT=9021
    make test

En `main.c`, `PORT_TYPE` es 1 para BGM o 0 para el puerto normal.

## Pendiente

- Confirmar que el audio BGM se mezcla con el de un juego
- Decodificar MP3
- Mini servidor web para controlarlo desde el celular
