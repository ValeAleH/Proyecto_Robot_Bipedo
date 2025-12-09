# Robot Bípedo 

## Descripción del proyecto
Este proyecto consiste en el desarrollo de un robot bípedo controlado por una placa ESP32, 
el cual utiliza un sensor MPU9250 para medir aceleración, giroscopio y orientación espacial.
El objetivo principal es lograr estabilidad, locomoción básica y control eficiente del robot 
mediante programación en sistemas embebidos.
El robot cuenta con piezas diseñadas e impresas en 3D y un sistema de control programado en C/C++.

## Objetivos
Diseñar e implementar un robot bípedo de seis grados de libertad, controlado mediante
un sistema embebido basado en ESP32 y FreeRTOS, incorporando modelado cinemático, con fines académicos y experimentales 
para la implementacion de robotica dinamica.


## Diagrama del sistema / Arquitectura
## Diagrama de Estados
![c72de5f9-b10e-4230-a639-70ab263a1b59](https://github.com/user-attachments/assets/be1a9a4e-76ec-4142-9d24-2a8d2239e7ae)

## Diagrama 3D
![172cc056-5a7b-4607-a823-49468f11fc29](https://github.com/user-attachments/assets/ce01f0dc-eb40-48f0-83bc-44ac319b39b0) 

## Tecnologías utilizadas
### Hadware
- Microcontrolador: ESP32
- Sensor de movimiento: MPU9250
- PCA9685
- Jumpers
- Protoboard
### Software
- Lenguaje de programación: C / C++
- Diseño mecánico: Solidwords
- Control: Lógica embebida y lectura de sensores
- Entorno de desarrollo: Arduino IDE / VS Code
- Control de versiones: Git y GitHub

### Tareas necesarias

El robot bípedo utiliza un conjunto de tareas concurrentes implementadas en FreeRTOS, permitiendo ejecutar funciones críticas en tiempo real y garantizando estabilidad durante la marcha. Cada tarea tiene un propósito específico, una prioridad definida y un periodo de ejecución acorde a su importancia dentro del sistema embebido.

1. Task_IMU – Lectura del sensor inercial (Alta prioridad)
- Lee acelerómetro, giroscopio y magnetómetro del MPU9250.
- Corre cada 5–10 ms.
- Envia datos filtrados mediante una cola a las tareas de control.
- Es la tarea con mayor prioridad para asegurar respuesta rápida ante cambios de orientación.

2. Task_GaitPlanner – Generación de trayectorias y movimiento
- Calcula los ángulos deseados de cadera, rodilla y tobillo.
- Implementa la planificación de marcha en 6 GDL.
- Corre cada 10–20 ms.
- Envía los ángulos articulados a la tarea de control de servos.

3. Task_ServoControl – Control de servomotores (Alta prioridad)
- Convierte ángulos a pulsos PWM.
- Envía las señales al controlador PCA9685.
- Verifica límites articulares para prevenir daño mecánico.
- Asegura movimiento fluido y determinista.

4. Task_Safety – Seguridad y protección del sistema
- Detecta caídas o valores fuera de rango.
- Apaga los servos si es necesario (modo emergencia).
- Prioridad media.

5. Task_Posture – Control de postura (Reposo / Erguido)
Esta tarea administra los estados posturales principales del robot y garantiza una transición segura entre movimientos:
Estado REPOSO:
- Coloca las articulaciones en una posición neutra con los servos relajados para evitar consumo innecesario y estrés mecánico.
Estado ERGUIDO (Stand-Up):
- Eleva gradualmente el robot hasta la postura vertical, alineando cadera, rodilla y tobillo siguiendo una secuencia segura.
- Gestiona el cambio de estados mediante una cola o un evento enviado desde Bluetooth u otra interfaz.
- Prioridad media-alta, ya que afecta directamente la estabilidad inicial del robot.

## Esquema de conexión
<img width="613" height="368" alt="Captura de pantalla 2025-12-09 100521" src="https://github.com/user-attachments/assets/5a9d2384-039c-460f-a5b7-774b3faed6af" />
<img width="392" height="232" alt="Captura de pantalla 2025-12-09 100414" src="https://github.com/user-attachments/assets/3e9115f2-caf2-41db-bb35-f1f4922ba470" />


## Integrantes del equipo y roles
- Valeria Alejandra Hoyos Tovar – Programación y control del sistema
- Roberth Williams Ruiz Condori – Diseño estructural y armado del robot
- Sergio Alejandro Mercado Vallejos – Integración electrónica y pruebas


