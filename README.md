# WashTunnel

WashTunnel is an undergraduate project that involves Microchip Studio programming for an Automatic Tunnel Washer.

This project has been carried out using a prototype that models a typical car wash tunnel. This control systems learning platform is oriented towards experimentation with microprocessor systems. The control of this model has been carried out with an 8-bit microcontroller with AVR architecture, specifically the ATmega640.

## Content
**[1. Project Description](#1-project-description)**

  * [1.1. Final video](#1-final-video)
  * [1.2. Code](#12-code)
  * [1.3 Report](#13-report)

**[2. Acknowledgments](#2-acknowledgments)**


## 1. Project Description
### 1.1. Final video
(Loading... Please wait)

[![IROS 2019: FASTER: Fast and Safe Trajectory Planner for Flights in Unknown Environments](./imgs/washtunnel.gif)]
### 1.2. Code
#### **Salida (Exit Control):**
   - *Description*: This section handles the control of the car wash system's exit process. It likely includes logic for safely allowing vehicles to exit the car wash once the washing and drying processes are complete.
   - *Code*: **`salida.c`**

#### **Cinta (Conveyor Belt):**
   - *Description*: The conveyor belt section is responsible for the transportation of vehicles through the car wash. It likely contains the code for managing the movement of vehicles along the conveyor belt.
   - *Code*: **`cinta.c`**

#### **Parada de Emergencia (Emergency Stop):**
   - *Description*: This section is crucial for safety. It contains code for an emergency stop mechanism that can halt the car wash system's operation in case of a critical situation.
   - *Code*: **`emergencia.c`**

#### **Lavado Horizontal (Horizontal Washing):**
   - *Description*: This section involves the code for the horizontal washing process. It specifies how the car wash system cleans vehicles *horizontally*.
   - *Code*: **`lavado_horizontal.c`**

#### **Secado Horizontal (Horizontal Drying):**
   - *Description*: The horizontal drying section manages the process of drying vehicles *horizontally*. It includes code related to blowers or other drying mechanisms.
   - *Code*: **`secado_horizontal.c`**

#### **Entrada (Entry Control):**
   - *Description*: The entry control section oversees the entrance of vehicles into the car wash. It may include sensors and mechanisms to admit vehicles in an orderly fashion.
   - *Code*: **`entrada.c`**

#### **Lavado Vertical (Vertical Washing):**
   - *Description*: This section is responsible for the vertical washing process, ensuring that the car wash system effectively cleans vehicles in a *vertical* orientation.
   - *Code*: **`lavado_vertical.c`**
 
#### **Integration of the System**
In the **`main.c`** file, the integration of all these modules occurs.

In the code, the integration of the system is achieved through the use of a global `char` variable named ***ready.*** This variable, composed of 8 bits, stores the state of each part of the car wash tunnel. It is initialized to zero, and in the initial part of the main loop, each section of the model starts in *starting* mode with the aim of changing the corresponding bit in the ***ready*** variable from 0 to 1.

#### **Bit Assignments**

The specific bits assigned for each area of the model can be observed here:
```
/* Position of each "mode" in the Modes byte */
#define ENTRY_MOD   0
#define LV_MOD      1
#define LH_MOD      2
#define DRYER_MOD   3
#define LIGHT_MOD   4  // Not used
#define BELT_MOD    5
#define OUT_MOD     6
```

 These definitions are included at the end of the *"commonstuff.c"* file, which plays a crucial role in achieving more *abstract* and *functional* programming. Out of the eight bits in the ***ready*** variable, only seven are utilized, and the one corresponding to the *light mode (LIGHT MODE)* isn't ultimately needed. *Code snippet 17* demonstrates the ***ready*** variable being compared to the binary number *0b01101111*.


### 1.3. Report
The explanation of the model and its operation can be found in the document *Wash_Tunnel_model.pdf*. The *Final_Report.pdf* explains the distribution of the work among the members of the group and the proposed solution. It includes a large number of code snippets as well as the flowcharts created for its implementation. At the end of this memory there is a schematic of the microprocessor connection to the pins of the model.

## 2. Acknowledgments
First of all, I would like to thank the members of the team (Marı́a del Mar Martı́n, Celia Ramos, Juan Galvañ, Mario Gómez and Gonzalo Quirós) for their tireless work to bring this project to completion. Everything has been very easy with them. 

I would like to thank Jorge Portilla and Yago Tarroja professors of the Microprocessor Systems course (at [CEI](http://www.cei.upm.es/)) for their support and guidance during all the project. Special thanks to Yago Tarroja, author of the Tunnel Washer model guide.  


