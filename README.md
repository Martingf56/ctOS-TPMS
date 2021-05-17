# ctOS-TPMS
Este es en el respositorio de nuestro Trabajo de Fin de Grado para terminar nuestro Grado en Ingeniería Informática en la Universidad Complutense de Madrid. El proyecto lo hemos realizado conjuntamente Jorge María Martín([@jmm98sr](https://github.com/jmm98sr)), Alberto Rodriguez Fuentes([@bertoo9712](https://github.com/bertoo9712)) y Martín García Fuentes([@Martingf56](https://github.com/Martingf56)).

Este TFG es un estudio sobre las vulnerabilidades de la tecnología TPMS y el desarrollo de una aplicación capaz de recibir estas señales emitidas por los vehículos y a traves de ellas generar señales falsas con el fin de atacar a la ECU de la víctima. 

Este respositorio contiene el codigo de la aplicación desarrollada. Mientras que el estudio y la memoria del proyecto se subirá a la página web de la Facultad de Informática de la UCM.

## Prerequisitos
Esta aplicación ha sido desarrollada en el lenguaje **C** por lo tanto es multiplataforma. Pero no obstante recomendamos utilizar Sistemas Operativos basados en Linux, especialmente ejcutarlo en una Raspberry Pi con RaspiOS.

Para la escucha de señales hacemos uso del software [RTL_433](https://github.com/merbanan/rtl_433), por ello se precisa de una antena RTL-SDR capaz de escuchar en la frecuencia 433MHz. En nuestro caso usamos la antena [RTL-SDR de Noeelec]().

## Manual de Instalación
- Hay que instalar gcc.
- Instalar rtl_433.
- Instalar python cc1101
- Compilar el codigo con el make

## Como ejecutarlo y usar la herramienta
Ejecutar el codigo y se te abrirá la interfaz y ya estará corriendo la aplicación lista para usarla.

