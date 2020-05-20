# SCE-Esercitazioni
Esercitazioni del corso di **S**istemi di **C**ontrollo **E**mbedded. 

## Riferimenti ed utilità

### Software e Ambienti di Sviluppo
* [STM32Cube](https://www.st.com/en/ecosystems/stm32cube.html)
* [Mbed online compiler](https://ide.mbed.com/compiler)
* [Mbed Studio](https://os.mbed.com/studio)

### Hardware -suggerito-
* [STM32 Nucleo-F446RE](https://www.st.com/en/evaluation-tools/nucleo-f446re.html)
* [Kit Sensori](https://amzn.to/3e01LHP)
* Motori DC
    * [Motori DC + ruote](https://amzn.to/3bMl9Xr)
    * [Motore DC + encoder](https://amzn.to/3bO7Bug)
    * [Motore DC + encoder](https://www.pololu.com/product/4750)
    * [Driver Motore DC L9110](https://amzn.to/2ZfGqpF)
    * [Driver Motore DC L298N](https://amzn.to/3gaJQ3l)
* [Servomotore](https://amzn.to/3cGYQDI)
    * [Servomotore 20Kg/cm](https://amzn.to/2TlYNWd)
    * [Coppia Servomotori 11Kg/cm](https://amzn.to/2LF6PFl)
    * [Mini servomotore](https://amzn.to/36huzsY)

### Documentazione
* [Nucleo 64 - User Manual](https://www.st.com/resource/en/user_manual/dm00105823-stm32-nucleo-64-boards-mb1136-stmicroelectronics.pdf)
* [STM32F446xx - Reference Manual](https://www.st.com/resource/en/reference_manual/dm00135183-stm32f446xx-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf)
* [STM32F446xC/E - Datasheet](https://www.st.com/resource/en/datasheet/stm32f446mc.pdf)
* [STM32 Cortex M4 Programming Manual](https://www.st.com/resource/en/programming_manual/dm00046982-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf)
* [STM32 Description of STM32F4 HAL and LL drivers](https://www.st.com/resource/en/user_manual/dm00105879-description-of-stm32f4-hal-and-ll-drivers-stmicroelectronics.pdf)
* [Developing applications on STM32Cube with RTOS - User Manual](https://www.st.com/resource/en/user_manual/dm00105262-developing-applications-on-stm32cube-with-rtos-stmicroelectronics.pdf)

### Libri
* [**The Definitive Guide to ARM Cortex-M3 and Cortex-M4 Processors** | Joseph Yiu](https://www.amazon.it/Definitive-Guide-Cortex®-M3-Cortex®-M4-Processors/dp/0124080820)
* [**DC Motors, Speed Controls, Servo Systems** | Sam Stuart](https://www.elsevier.com/books/dc-motors-speed-controls-servo-systems/stuart/978-0-08-021714-7)
* [**Embedded Control System Design: A Model Based Approach** | Alexandru Forrai](https://www.amazon.it/Embedded-Control-System-Design-Approach/dp/3642285945)

### Header pinout
* [CN5 Header Pinout](HeadersPinout.md#CN5-Header-Pinout)
* [CN6 Header Pinout](HeadersPinout.md#CN6-Header-Pinout)
* [CN7 Header Pinout](HeadersPinout.md#CN7-Header-Pinout)
* [CN10 Header Pinout](HeadersPinout.md#CN10-Header-Pinout)


## Indice degli argomenti trattati
* [Attuatori per sistemi di controllo Embedded](https://github.com/p-ansatz/SCE-Esercitazioni/tree/master/Esercitazione1-MotoriDC#esercitazione-1)
    * [Motori DC a Spazzole](https://github.com/p-ansatz/SCE-Esercitazioni/tree/master/Esercitazione1-MotoriDC#motori-cc-a-spazzole-bdcm)
        * [Controllo di un Motore DC](https://github.com/p-ansatz/SCE-Esercitazioni/tree/master/Esercitazione1-MotoriDC#controllo-di-un-motore-a-spazzole)
    * [ServoMotori](https://github.com/p-ansatz/SCE-Esercitazioni/tree/master/Esercitazione1-MotoriDC#servomotori)
        * [Controllo di un ServoMotore](https://github.com/p-ansatz/SCE-Esercitazioni/tree/master/Esercitazione1-MotoriDC#controllo-di-un-servomotore)
