#ifndef __GLOBALES_H
#define __GLOBALES_H

    #include "./semaforo.h"
    #include "./memcomp.h"
    #include "./mensaje.h"

    #define CLAVE_BASE 33
    #define ARCHIVO_BASE "/bin/ls"

    #define MAX_OPERACIONES 5 // para el bucle del banco
    #define CANT_CAJEROS 3 //cantidad de cajeros maximos, totalmente arbitrario

    #define VERDE 1
    #define ROJO 0

    typedef struct cajero {
        int id;
        int iniciado;
    }Cajero;

    typedef enum {
        BANCO,
        CAJERO //no se usa en este programa ya que se admite mas de un cajero
    }Buzones;

    //codigos de errores que se pasan por mensaje cuando falla una operacion.
    typedef enum {
        ERR_CLIENTE_NOT_FOUND,
        ERR_SALDO_INSUFICIENTE,
        ERR_MONTO_INCORRECTO
    }Errores;

    typedef enum {
        EVT_CONSULTA_SALDO, //consultar saldo (COD_CLIENTE)
        EVT_DEPOSITO, //realizar deposito (COD_CLIENTE|IMPORTE)
        EVT_EXTRACCION, //realizar extraccion (COD_CLIENTE|IMPORTE)
        EVT_RTA_SALDO, // muestra saldo (COD_CLIENTE|SALDO)
        EVT_RTA_SALDO_NOK, // responde saldo error (COD_CLIENTE|ERROR)
        EVT_RTA_DEPOSITO_OK, //muestra deposito -> saldo (COD_CLIENTE|SALDO)
        EVT_RTA_DEPOSITO_NOK, // responde deposito -> error (COD_CLIENTE|ERROR)
        EVT_RTA_EXTRACCION_OK, //muestra extraccion -> saldo (COD_CLIENTE|SALDO)
        EVT_RTA_EXTRACCION_NOK // responde extraccion -> saldo error (COD_CLIENTE|ERROR)
    }Eventos;
    
#endif