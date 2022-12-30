#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
    /**
     * @brief funciones de unistd.h
     * 
     * ID proceso           getpid()
     * ID padre             getppid()
     * ID usuario real      getuid()
     * ID usuario efectvo   geteuid()
     * ID de grupo real     getgid()
     * ID grupo efectivo    getegid()
     * Nombre usuario       getlogin()  retorna puntero a cadena
     */

#include <pwd.h>
    /**
     * @brief funciones de pwd.h (password)
     * 
     * Password             getpwnam()  retorna puntero a estructura patron de password.
     * 
     */

void datos_login () {
    char *nom_acceso;
    struct passwd *puntero_dato;

    //Obtencion del nombre de acceso
    if((nom_acceso = getlogin()) == NULL){
        perror("getlogin");
        exit(EXIT_FAILURE);
    }

    printf("getlogin retorno %s\n", nom_acceso);

    //Obtencion de la contraseña para ese nombre de acceso
    if((puntero_dato = getpwnam(nom_acceso)) == NULL){
        perror("getpwnam");
        exit(EXIT_FAILURE);
    }
    printf("gecos: %s\n", puntero_dato->pw_gecos);

    exit(EXIT_SUCCESS);
}

int main (void) {
    printf("PID = %d\n", getpid());
    printf("PPID = %d\n", getppid()); //en windows este no va...
    exit(EXIT_SUCCESS);
}