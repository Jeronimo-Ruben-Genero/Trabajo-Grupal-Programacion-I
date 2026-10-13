#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>
#define LIM 8 //Caracteres patente + nulo \0


//Funcion que define la estructura
typedef struct {
    char Patente[LIM];
    char TipoServicio;
    int NumeroOrden;
    float Costo;
    bool Finalizo;
}t_auto;

//Funcion que pregunta al usuario si desea continuar
bool continua() {
    char continua;
    bool eleccion;

    do{
        printf("si (S).\nno (N).\nDesea continuar: ");
        scanf(" %c", &continua);
        continua=toupper(continua);
        if(continua!='N'&&continua!='S'){
            printf("La respuesta no es valida.\nIngrese nuevamente.");
        }

    }while(continua!='N'&&continua!='S');

    if(continua=='N'){
        eleccion=false;
    }else{
        eleccion=true;
    }
    return eleccion;
}

//Funcion para ingresar los datos de un nuevo servicio
t_auto IngresarDatos(t_auto a) {

    do {
        printf("Ingrese la patente del auto a revisar: ");
        fflush(stdin);
        scanf("%7s", a.Patente);
        for (int i = 0; i < strlen(a.Patente); i++) {
            a.Patente[i] = toupper(a.Patente[i]); //Convierte a mayusculas
        }
        if (a.Patente[0] == '\0') {
            printf("La patente no existe\n");
        }
    }while (a.Patente[0] == '\0');

    // Validar tipo de servicio
    do {
        printf("(A)Cambio de aceite.\n(M)Revision de motor.\n(C)Revision de chasis.\nSeleccione el servicio que desee: ");
        fflush(stdin);
        scanf(" %c", &a.TipoServicio);
        a.TipoServicio = toupper(a.TipoServicio);
        if (a.TipoServicio != 'A' && a.TipoServicio != 'M' && a.TipoServicio != 'C') {
            printf("El servicio seleccionado no es valido, ingrese nuevamente.\n");
        }
    }while (a.TipoServicio != 'A' && a.TipoServicio != 'M' && a.TipoServicio != 'C');

    //Validar N° de orden
    do {
        printf("Introduzca el numero de orden: ");
        fflush(stdin);
        scanf("%d", &a.NumeroOrden);
        if (a.NumeroOrden < 1) {
            printf("El numero de ordenes no es valido, ingresar nuevamente.\n");
        }
    }while (a.NumeroOrden < 1);

    //Validar costo del servicio
    do {
        printf("Introduzca el costo del servicio: ");
        fflush(stdin);
        scanf("%f", &a.Costo);
        if (a.Costo <= 0) {
            printf("El costo del servicio no puede ser igual o menor a cero. Ingrese nuevamente.\n");
        }
    }while (a.Costo <= 0 );

    int respuesta; //use este int respuesta para poder usar %d y detectar como entero a 1 o 0 y asignarle true o false al booleano.
    // Desea continuar?
    do {
        printf("(1) Si.\n(0) No.\nIndique si el servicio ha finalizado: ");
        scanf("%d", &respuesta);

        if (respuesta != 0 && respuesta != 1) {
            printf("El servicio no es valido, ingresar nuevamente.\n");
        }

    } while (respuesta != 0 && respuesta != 1);

    a.Finalizo = respuesta;


    return a;
}

//Agrega ordenes al archivo txt
void AgregarOrden() {
    t_auto a;
    bool sigo=true;
    FILE *Service_De_Autos = fopen("Service_De_Autos.txt", "a");
    if (Service_De_Autos == NULL) puts("Error al abrir el archivo");
    else {
        while (sigo) {
            a=IngresarDatos(a);
            //Guarda los datos en una nueva linea
            fprintf(Service_De_Autos,"%s %c %d %.2f %d\n", a.Patente, a.TipoServicio, a.NumeroOrden, a.Costo, a.Finalizo );
            sigo = continua();
        }
        fclose (Service_De_Autos);
    }

}

//Imprime en pantalla el listado completo
void ListadoCompleto() {
    char Patente[LIM];
    char Tipo;
    int Orden;
    float costo;
    int finalizado;
    FILE *Service_De_Autos = fopen ("Service_De_Autos.txt", "r");
    if (Service_De_Autos == NULL) puts("Error al abrir el archivo");
    else {
        printf("PATENTE\tSERVICIO\t\tORDEN\tCOSTO\t\tFINALIZADO\n");
        while (fscanf(Service_De_Autos, "%7s %c %d %f %d",
              Patente, &Tipo, &Orden, &costo, &finalizado) == 5) {
            printf("%s\t", Patente);

            //Imprime el nombre del servicio segun el caracter ingresado
            switch (Tipo) {
                case 'A':
                    printf("Cambio de aceite\t");
                    break;
                case 'M':
                    printf("Revision de motor\t");
                    break;
                case 'C':
                    printf("Revision de chasis\t");
                    break;
            }

            printf("%d\t%.2f\t", Orden, costo);

            if (finalizado == 1) {
                printf("Si\n");
            } else {
                printf("No\n");
            }
        }

        fclose(Service_De_Autos);
    }
    return;
    }

//Listado de servicios pendientes
void ListadoPendientes() {
    char Patente[LIM];
    char Tipo;
    int Orden;
    float costo;
    int finalizado;

    FILE *Service_De_Autos = fopen("Service_De_Autos.txt", "r");

    if (Service_De_Autos == NULL) {
        puts("Error al abrir el archivo");
    } else {
        printf("PATENTE\tSERVICIO\t\tORDEN\tCOSTO\t\tFINALIZADO\n");

        while (fscanf(Service_De_Autos, "%7s %c %d %f %d",
                      Patente, &Tipo, &Orden, &costo, &finalizado) == 5) {

            //Filtro para incluir solo los no terminados
            if (finalizado == 0) {
                printf("%s\t", Patente);

                switch (Tipo) {
                    case 'A':
                        printf("Cambio de aceite\t");
                        break;
                    case 'M':
                        printf("Revision de motor\t");
                        break;
                    case 'C':
                        printf("Revision de chasis\t");
                        break;
                }

                printf("%d\t%.2f\tNo\n", Orden, costo);
            }
                      }

        fclose(Service_De_Autos);
    }
    return;
}

// Funcion que busca los servicios por patente
void BuscarPatente() {
    // Declaración de variables
    char patenteBuscada[LIM];
    char Patente[LIM];
    char Tipo;
    int Orden;
    float costo;
    int finalizado;
    bool encontrado = false;

    // Pide la patente y la convierte a mayusculas
    printf("Ingrese la patente que desea buscar: ");
    scanf("%7s", patenteBuscada);

    for (int i = 0; patenteBuscada[i] != '\0'; i++) {
        patenteBuscada[i] = toupper(patenteBuscada[i]);
    }

    // Abre el archivo
    FILE *Service_De_Autos = fopen("Service_De_Autos.txt", "r");

    if (Service_De_Autos == NULL) {
        printf("Error al abrir el archivo.\n");
    } else {
        printf("Servicios correspondientes a la patente %s:\n", patenteBuscada);
        printf("PATENTE\tSERVICIO\t\tORDEN\tCOSTO\t\tFINALIZADO\n");

        // Lee el archivo registro por registro (5 campos)
        while (fscanf(Service_De_Autos, "%7s %c %d %f %d", Patente, &Tipo, &Orden, &costo, &finalizado) == 5) {

            // Si coincide la patente, muestra el detalle del servicio
            if (strcmp(patenteBuscada, Patente) == 0) {
                encontrado = true;

                printf("%s\t", Patente);

                // Muestra la descripción según el tipo de servicio
                switch (Tipo) {
                    case 'A':
                        printf("Cambio de aceite\t");
                        break;
                    case 'M':
                        printf("Revision de motor\t");
                        break;
                    case 'C':
                        printf("Revision de chasis\t");
                        break;
                }

                printf("%d\t%.2f\t", Orden, costo);

                // Muestra si el trabajo está finalizado o no
                if (finalizado == 1) {
                    printf("Si\n");
                } else {
                    printf("No\n");
                }
            }
        }

        // Si no la encontró devuelve el error
        if (encontrado == false) {
            printf("No se encontraron servicios para esa patente.\n");
        }

        // Cierra el archivo
        fclose(Service_De_Autos);
    }
}

//Menu de las opciones
void menu () {
    int menu;

    do {
        printf("(1)Agregar orden de servicio.\n(2)Mostrar en pantalla listado de servicios.\n(3)Mostrar en pantalla listado de servicios pendientes.");
        printf("\n(4)Buscar un servicio por patente.\n(5)Separar servicios finalizados y pendientes en dos archivos.\n(0)Salir.");
        printf("\nIntroduzca su eleccion: ");
        scanf("%d", &menu);

        switch (menu) {
            case 1: {
                AgregarOrden();
                break;
            }
            case 2: {
                ListadoCompleto();
                break;
            }
            case 3: {
                ListadoPendientes();
                break;
            }
            case 4: {
                BuscarPatente();
                break;
            }
            case 5: {
               // SepararServicios();
                break;
            }
            case 0: {
                printf("El programa ha finalizado.");
                break;
            }
            default: {
                printf("Opcion invalida. Ingrese nuevamente.\n");
                break;
            }
        }
    }while (menu!=0);

    return;
}

int main() {
    //paso 2. iniciar menu
    menu();



    return 0;
}