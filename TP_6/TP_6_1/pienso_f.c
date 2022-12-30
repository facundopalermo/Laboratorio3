#include "pienso.h"

/*funcion que se encarga de validar los parametros del main*/
int validarJugadores( int argc, char const *argv[]) {

    int jugadores = 0;

    if (argc == 2) {
        jugadores = atoi(argv[1]);
    } else if (argc < 2) {
        printf("Debe indicar la cantidad de jugadores como parametro al iniciar el juego.\n");
        return -1;
    } else if (argc > 2) {
        printf("Solo se admite un parametro para iniciar el juego: cantidad de jugadores.\n");
        return -1;
    }
    if ( jugadores < 1 ) {
        printf("La cantidad de jugadores no puede ser menor a 1\n");
        return -1;
    }

    return jugadores;
}

/*funcion que piensa los numeros. tabien la uso para el tiempo de espera*/
int piensoNumero (int desde, int hasta) {
    return rand() % (hasta - desde + 1) + desde;
}

/*funcion que busca en el array para no repetir numeros*/
int buscaNumero(int numero, int hasta, int *array){
    int i;
    for (i=0; i < hasta; i++){
        if (numero == array[i]){
            return 1;
        }
    }

    return 0;
}

/*funcion que retorna un numero aleatorio sin repetir. usa piensoNumero() y buscaNumero()*/
int piensoNumeroSinRepetir(int desde, int hasta, int *array){

    int numero=0;
    int cond = 1;
    do {
        numero = piensoNumero(desde, hasta);
        cond = buscaNumero(numero, hasta, array);
    } while (cond);

    return numero;
}

/*funcion de los jugadores*/
void * ThreadJugadores (void *parametros) {

    Datos *datos; /*puntero para estructura que contiene todos los datos para jugar*/
    int pensado[N_MAX];
    int jugar = 1; /*jugar: bandera de corte cuando alguien haya acertado. 1 true, 0 false.*/
    char mensaje[100];

    datos = (Datos *) parametros;

    /*carita triste si no gana. se retorna si pierde*/
    strcpy(mensaje, ":'(");
    
    while (jugar == 1) {

        pthread_mutex_lock(&mutex);
        /*"sección critica"
            mira si alguien ya adivinó.*/
            if((*datos->alguien_acerto) == 0) {
        
                pensado[datos->intentos] = piensoNumeroSinRepetir(N_MIN, N_MAX, pensado); /*guardo en el array, un numero pensado.*/
                /*el indice es la cantidad de intentos. en el primer intento es 0.
                por eso en el sig printf uso datos->intentos+1 (igual que jugador, como son indices, me gusta mas que muestre desde 1)*/
                printf("Jugador %d piensa el numero %d (intento: %d).\n", datos->jugador + 1, pensado[datos->intentos], datos->intentos + 1); 

                /*si el numero generado es igual al numero pensado y traido desde el main...*/
                if (pensado[datos->intentos] == datos->numero_pensado) {
                    *datos->alguien_acerto = datos->jugador; /*cambio el valor del puntero alguien_acerto (traido desde main)*/
                    strcpy(mensaje, "Soy un ganador!"); /*y cambio la carita triste por un "Soy un ganador!"*/
                }

                datos->intentos++;

            } else {
                jugar = 0; /*si ya adivinaron salgo del while.*/
            }
        /*fin "sección critica"*/
        pthread_mutex_unlock(&mutex);
        usleep(piensoNumero(ESPERA_MIN, ESPERA_MAX)*1000);
    }

    pthread_exit ((void *) mensaje);
}

/*funcion principal*/
void jugar(pthread_t *jugadores, int numero_pensado, int* alguien_acerto, int cant_jugadores) {

    int i = 0;
    pthread_attr_t atributos;
    Datos *datos; /*estructura que contiene todos los datos para jugar, y que se pasa a los jugadores*/

    pthread_mutex_init(&mutex, NULL);
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    datos = (Datos*) malloc (sizeof(Datos) * cant_jugadores);

    /*inicio a cada jugador.*/
    for ( i = 0; i < cant_jugadores; i++ ) {

        datos[i].jugador = i; /*el numero de jugador*/
        datos[i].numero_pensado = numero_pensado; /*el numero pensado por el main*/
        datos[i].alguien_acerto = alguien_acerto; /*el puntero a alguien_acerto que viene desde main*/
        datos[i].intentos = 0; /*cantidad de intentos*/

        if ( pthread_create (&jugadores[i], &atributos, ThreadJugadores, &datos[i]) != 0) {
            /*en caso de que algun jugador se arrepienta de jugar y no sea posible continuar.*/
            printf("Error al crear el thread para el jugador %d.\n", i);
            exit(EXIT_FAILURE);
        }

    }

    esperarandoJugadores (jugadores, cant_jugadores, datos); /*funcion que se encarga del pthread_join()*/
    free(datos);

}

/*funcion que se encarga del pthread_join()*/
void esperarandoJugadores (pthread_t *jugadores, int cant_jugadores, Datos *datos) {
    int i = 0;
    char *mensaje;
    mensaje = malloc(100);

    for (i = 0; i < cant_jugadores; i++) {
        pthread_join (jugadores[i], (void**) &mensaje);
        /*obtengo el mensaje de cada jugador, la carita triste o el ganador, y lo muestro*/

        printf("Jugador %d lo intentó %d veces. %s\n", i+1, datos[i].intentos, mensaje);
    }

    free(mensaje);
}