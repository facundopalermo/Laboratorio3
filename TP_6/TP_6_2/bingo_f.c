#include "bingo.h"

/*Funcion que se encarga de validar los parametros del main*/
int validarJugadores( int argc, char const *argv[]) {

    int jugadores = 0;

    if (argc == 2) {
        jugadores = atoi(argv[1]);
    } else if (argc < 2) {
        printf("Debe indicar la cantidad de jugadores como parametro al iniciar el juego.\n");
        exit(EXIT_FAILURE);
    } else if (argc > 2) {
        printf("Solo se admite un parametro para iniciar el juego: cantidad de jugadores.\n");
        exit(EXIT_FAILURE);
    }

    if ( jugadores < 1 ) {
        printf("La cantidad de jugadores no puede ser menor a 1\n");
        exit(EXIT_FAILURE);
    }

    return jugadores;
}

/*Funcion para numeros aleatorios.*/
int numeroAleatorio (int desde, int hasta) {
    return rand() % (hasta - desde + 1) + desde;
}

/*Funcion que busca en el array para no repetir numeros*/
int buscaNumero(int numero, int hasta, int *array){
    int i;
    for (i=0; i < hasta; i++){
        if (numero == array[i]){
            return 1;
        }
    }

    return 0;
}

/*Funcion que retorna un numero aleatorio sin repetir. Se usa para generar los cartones y para el Bombo*/
int numeroSinRepetir(int desde, int hasta, int *array){

    int numero=0;
    int cond = 1;
    do {
        numero = numeroAleatorio(desde, hasta);
        cond = buscaNumero(numero, hasta, array);
    } while (cond);

    return numero;
}

/*funcion que genera el carton del jugador*/
void escogerCarton(int carton[]) {
    int i = 0;
    for( i = 0; i < N_CARTON; i++ ) {
        carton[i] = numeroSinRepetir(N_MIN, N_MAX, carton);
    }
}

/* Funcion que muestra el carton luego de escogerlo*/
void mostrarCarton(int carton[], int jugador) {
    int i = 0;
    printf("Carton del jugador %d:\t", jugador + 1);
    for (i = 0; i < N_CARTON; i++) {
        printf("[%.2d] ", carton[i]);
    }
    printf("\n");
}

/*Funcion que busca el numero que salió en el bombo, y lo busca en su carton*/
int mirarCarton(int bolilla, int carton[]) {
    return buscaNumero(bolilla, N_CARTON, carton);
}

/*Funcion de los jugadores*/
void * ThreadJugadores(void * parametros) {
    int carton[N_CARTON] = {0};
    Datos *datos;
    int cant_aciertos = 0;
    int bolilla = 0; /*indice para acceder dentro del vector de numeros generados por el Bombo*/
    char aciertos[100]; /*para retornar la cantidad de aciertos*/

    datos = (Datos*)parametros;

    escogerCarton(carton); /*escoge un carton entre los muchos que se podrian generar!*/

    /*priorizo el hilo para mostrar el carton y no se mezclen los numeros*/
    pthread_mutex_lock(&mutex);
        mostrarCarton(carton, datos->jugador); /*muestra carton*/
    pthread_mutex_unlock(&mutex);

    /*mientras no haya ganador*/
    while (g_carton_lleno == 0) {

        pthread_mutex_lock(&mutex);

            if( (datos->bolillas[bolilla]) != 0 ) { /*verifica que haya caido una bolilla, si es 0, aun no cayó*/
                if( mirarCarton(datos->bolillas[bolilla], carton) == 1 ) { /*si cayó, la busca en su carton y si lo tiene lo marca*/
                    cant_aciertos++;
                    printf("\tJugador %d acertó el número %d\n", datos->jugador+1,
                    datos->bolillas[bolilla]);
                    printf("\t - Jugador %d dice: me faltan %d números!\n", datos->jugador+1, N_CARTON - cant_aciertos);
                }
                bolilla++; /*se prepara para mirar el proximo numero que salga*/
            }

            /*si alcanzó el numero de acietos...Bingo!*/
            if( cant_aciertos == N_CARTON ) {
                g_carton_lleno = datos->jugador;
                printf("\nJugador %d dice: BINGO!!\n\n", datos->jugador + 1);
            }

        pthread_mutex_unlock(&mutex);
        usleep(TIEMPO*100);
    }

    sprintf(aciertos, "%d", cant_aciertos); /*para retornar la cantidad de aciertos*/
    pthread_exit ((void *) aciertos);
}

void crearHilo (pthread_t * hilo, void *(*funcion)(void *), void * datos) {

    pthread_attr_t atributos;
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    if ( pthread_create (hilo, &atributos, funcion, datos) != 0 ) { 
        printf("Error al crear el thread para el hilo.\n");
        exit(EXIT_FAILURE);
    }

}

/*funcion principal del main*/
void jugar(pthread_t *jugadores, int cant_jugadores, int *bolillas) {

    int i = 0;
    /*pthread_attr_t atributos;*/
    Datos *datos;

    pthread_mutex_init(&mutex, NULL);
    /*pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);*/

    datos = (Datos*) malloc (sizeof (Datos)*cant_jugadores);

    for ( i = 0; i < cant_jugadores; i++ ) {

        /*inicializo los datos a pasar a cada jugador. solo va su identificacion y el puntero al vector de las bolillas*/
        datos[i].jugador = i;
        datos[i].bolillas = bolillas;

        crearHilo(&jugadores[i], ThreadJugadores, &datos[i]);

        /*if ( pthread_create (&jugadores[i], &atributos, ThreadJugadores, &datos[i]) != 0 ) {
            en caso de que algun jugador se arrepienta de jugar y no sea posible continuar.
            printf("Error al crear el thread para el jugador %d.\n", i);
            exit(EXIT_FAILURE);
        }*/
    }

    /*este sleep es para dar tiempo a los jugadores a escoger sus cartones y mostrarlos*/
    sleep(2);
    /*a jugar! .. gira el bombo*/
    girarBombo(bolillas);

    esperarandoJugadores (jugadores, cant_jugadores); /*funcion que se encarga del pthread_join()*/
    free (datos);
}

void girarBombo(int *bolillas) {

    int bolilla = 0; /*indice*/

    /* si aun no hay ganador*/
    while( g_carton_lleno == 0 ) {

        pthread_mutex_lock(&mutex);
            
            /*genera un numero sin repetir y lo coloca en el vector*/
            bolillas[bolilla] = numeroSinRepetir(N_MIN, N_MAX, bolillas);
            printf("\nGira el bombo y sale el numero... %d!\n",bolillas[bolilla]);
            bolilla++;

        pthread_mutex_unlock(&mutex);
        usleep(numeroAleatorio(T_MIN, T_MAX)*100);
    }

}

char * esperarThread (pthread_t hilo) {
    char *mensaje = NULL;
    pthread_join (hilo, (void**) &mensaje);
    return mensaje;
}

/*funcion que se encarga del pthread_join()*/
void esperarandoJugadores (pthread_t *jugadores, int cant_jugadores) {
    int i = 0;
    char *aciertos = NULL;

    for (i = 0; i < cant_jugadores; i++) {
        /*pthread_join (jugadores[i], (void**) &aciertos);*/
        /*obtengo la cantida de aciertos de cada jugador, y lo muestro*/
        aciertos = esperarThread(jugadores[i]);
        printf("El jugador %d logró marcar %s números\n", i+1, aciertos);
    }
}