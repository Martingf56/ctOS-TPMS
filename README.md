# ctOS-TPMS
Este es el respositorio de nuestro Trabajo de Fin de Grado para terminar nuestro Grado en Ingeniería Informática en la Universidad Complutense de Madrid. El proyecto lo hemos realizado conjuntamente Jorge María Martín([@jmm98sr](https://github.com/jmm98sr)), Alberto Rodriguez Fuentes([@bertoo9712](https://github.com/bertoo9712)) y Martín García Fuentes([@Martingf56](https://github.com/Martingf56)).

Este TFG es un estudio sobre las vulnerabilidades de la tecnología TPMS y el desarrollo de una aplicación capaz de recibir estas señales emitidas por los vehículos y a traves de ellas generar señales falsas con el fin de atacar a la ECU de la víctima. 

Este respositorio contiene el codigo de la aplicación desarrollada. Mientras que el estudio y la memoria del proyecto se subirá a la página web de la Facultad de Informática de la UCM.

####  Visualización de la aplicación

![Pantalla principal CtOs](/img/CapturaPantallaPrincipalInterfazCtOs.png "Pantalla de inicio interfaz de CtOS")

___

## Prerequisitos
Esta aplicación ha sido desarrollada en el lenguaje **C** por lo tanto es multiplataforma. Pero no obstante recomendamos utilizar Sistemas Operativos basados en Linux, especialmente ejcutarlo en una Raspberry Pi con RaspiOS.

Para la escucha de señales hacemos uso del software [RTL_433](https://github.com/merbanan/rtl_433), por ello se precisa de una antena RTL-SDR capaz de escuchar en la frecuencia 433MHz. En nuestro caso usamos la antena RTL-SDR [NESDR SMArt v4 Bundle](https://www.nooelec.com/store/sdr/sdr-receivers/nesdr-smart.html) de Noeelec.

A la hora de enviar hacemos uso de un transceptor con el chip Ti CC1101. Este lo tenemos conectado mediante los puertos GPIO a una Raspberry Pi 3, haciendo uso de los pines usado por el protocolo SPI.

## Manual de Instalación para Ubuntu
Para el correcto funcionamiento de la aplicación es necesario instalar varias herramientas de las que se hace uso durante la ejecución.

#### GCC 
Es necesario tener instalado GCC(GNU Compiler Collection) para compilar el programa.

    $ sudo apt-get install gcc

#### Antena RTL-SDR
Es necesario instalar la antena RTL-SDR para poder recibir las señales TPMS. En nuestro caso hacemos uso de la antena RTL-SDR SMArt v4 que tiene su propio [manual de instalación](https://www.nooelec.com/store/downloads/dl/file/id/72/product/294/nesdr_installation_manual_for_ubuntu.pdf) que recomendamos seguir paso a paso.

#### RTL-433
Este es un proyecto para realizar la escucha de señales TPMS. 

    $ sudo apt-get install rtl_433 

Para mayor información consultar el [repositorio](https://github.com/merbanan/rtl_433).

#### Python CC1101
Hacemos uso de la librería [python-cc1101](https://github.com/fphammerle/python-cc1101) para conectarse al chip y transmitir una señal.

    $ pip install cc1101-python
    
Para más información visitá el repositorio o en la página del proyecto en [PyPi](https://pypi.org/project/cc1101-python/).

#### ctOS
Para compilar el programa haciendo uso del [MAKEFILE](/makefile).
    
    $ sudo make all 
    
Para eliminarlo.

    $ sudo make clean

## Como ejecutarlo y usar la herramienta
En esta sección se explicará como ejecutar la herramienta. Despues de realizar todos los pasos de instalación el ejecutable debería estar listo para su ejecución. Importante utilizar siempre la última versión del código.

Una vez generado el programa, se ejecuta como cualquier ejecutable en Linux.

    $ ./ctOS
    
 **Importante siempre ejecutarlo con la antena conectada**
 
 Cuando se ejecute el archivo se abrirá la interfaz gráfica y la aplicación estará lista para usarla.

___

## ¿Como colaborar?
Puedes colaborar con este proyecto libremente.

Lo que buscamos principalmente es ampliar el número de vehículos que se puedan atacar. Para ayudar hemos creado una carpeta en el repositorio que se llama Debug que contiene un [script](/Debug/debugDatagramRTL.sh) para depurar tramas. Recibe por parámetro un datagrama en bits de una señal, haciendo uso de [tx_tools](https://github.com/triq-org/tx_tools/tree/master/src) genera la señal y se la pasa al software de **rtl_433** para poder comprobar si la señal se genera correctamente. 

