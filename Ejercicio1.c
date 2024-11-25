#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"

// Configuración de los pines para los LEDs y los botones
#define LEDS_PORTN GPIO_PORTN_BASE   // Puerto para los LEDs (PN0, PN1)
#define LEDS_PORTF GPIO_PORTF_BASE   // Puerto para los LEDs (PF0, PF1)
#define BUTTON_ADVANCE GPIO_PIN_0    // Botón de avance (PJ0)
#define BUTTON_BACK GPIO_PIN_1       // Botón de retroceso (PJ1)

// Variable global para el contador (de 0 a 4)
uint8_t contador = 0;

// Función para configurar los puertos
void configurar_puertos(void) {
    // Habilitar los periféricos de los puertos GPION, GPIOF, y GPIOJ
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);

    // Esperar hasta que los periféricos estén listos
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) {}
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) {}
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ)) {}

    // Configurar los pines de los LEDs como salida
    GPIOPinTypeGPIOOutput(LEDS_PORTN, 0x03);  // PN0, PN1 como salida (2 LEDs)
    GPIOPinTypeGPIOOutput(LEDS_PORTF, 0x11);  // PF0, PF1 como salida (2 LEDs)
    
    // Configurar los pines de los botones como entrada con resistencia pull-up
    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, BUTTON_ADVANCE | BUTTON_BACK);
    GPIOPadConfigSet(GPIO_PORTJ_BASE, BUTTON_ADVANCE | BUTTON_BACK, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}

// Función para actualizar el estado de los LEDs según el contador
void actualizar_leds(void) {
    // Apagar todos los LEDs antes de actualizar
    GPIOPinWrite(LEDS_PORTN, 0x03, 0);
    GPIOPinWrite(LEDS_PORTF, 0x11, 0);

    // Encender LEDs según el valor de 'contador'
    if (contador == 0) {
        // Todos apagados
        GPIOPinWrite(LEDS_PORTN, 0x03, 0);
        GPIOPinWrite(LEDS_PORTF, 0x11, 0);
    } else if (contador == 1) {
        // Encender el primer LED (PN0)
        GPIOPinWrite(LEDS_PORTN, 0x03, 0x02);  // PN0 encendido
    } else if (contador == 2) {
        // Encender los dos primeros LEDs (PN0, PF0)
        GPIOPinWrite(LEDS_PORTN, 0x03, 0x03);  // PN0 y PN1 encendidos
    } else if (contador == 3) {
        // Encender tres LEDs (PN0, PF0, PF1)
        GPIOPinWrite(LEDS_PORTF, 0x11, 0x10);  // PF0 y PF1 encendidos
        GPIOPinWrite(LEDS_PORTN, 0x03, 0x03);  // PN0 encendido
    } else if (contador == 4) {
        // Todos los LEDs encendidos
        GPIOPinWrite(LEDS_PORTN, 0x03, 0x03);  // PN0 y PN1 encendidos
        GPIOPinWrite(LEDS_PORTF, 0x11, 0x11);  // PF0 y PF1 encendidos
    }
}

// Función para manejar los botones de avance y retroceso
void manejar_botones(void) {
    // Si se presiona el botón de avance (PJ0), incrementar el contador
    if (GPIOPinRead(GPIO_PORTJ_BASE, BUTTON_ADVANCE) == 0) {
        // Incrementar contador (0 a 4)
        if (contador < 4) {
            contador++;
        } else {
            contador = 0;  // Reiniciar a 0
        }
        SysCtlDelay(2000000);  // Delay para evitar rebote de botones
    }

    // Si se presiona el botón de retroceso (PJ1), decrementar el contador
    if (GPIOPinRead(GPIO_PORTJ_BASE, BUTTON_BACK) == 0) {
        // Decrementar contador (4 a 0)
        if (contador > 0) {
            contador--;
        } else {
            contador = 4;  // Reiniciar a 4
        }
        SysCtlDelay(2000000);  // Delay para evitar rebote de botones
    }
}

// Función principal
int main(void) {
    // Configuración de la velocidad del sistema
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN);

    // Configurar los puertos
    configurar_puertos();

    // Bucle principal
    while (1) {
        manejar_botones();  // Leer los botones
        actualizar_leds();   // Actualizar el estado de los LEDs
    }

    return 0;
}
