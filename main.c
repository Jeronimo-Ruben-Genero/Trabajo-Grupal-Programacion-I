#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>
#define LIM 8
//paso 1. definir struct.
typedef struct {
    char Patente[LIM];
    char TipoServicio;
    int NumeroOrden;
    float Costo;
    bool Finalizo;
}t_auto;
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
t_auto IngresarDatos(t_auto a) {

    do {
        printf("Ingrese la patente del auto a revisar: ");
        fflush(stdin);
        scanf("%7s", a.Patente);
        for (int i = 0; i < strlen(a.Patente); i++) {
            a.Patente[i] = toupper(a.Patente[i]);
        }
        if (a.Patente[0] == '\0') {
            printf("La patente no existe\n");
        }
    }while (a.Patente[0] == '\0');

    do {
        printf("(A)Cambio de aceite.\n(M)Revision de motor.\n(C)Revision de chasis.\nSeleccione el servicio que desee: ");
        fflush(stdin);
        scanf(" %c", &a.TipoServicio);
        a.TipoServicio = toupper(a.TipoServicio);
        if (a.TipoServicio != 'A' && a.TipoServicio != 'M' && a.TipoServicio != 'C') {
            printf("El servicio seleccionado no es valido, ingrese nuevamente.\n");
        }
    }while (a.TipoServicio != 'A' && a.TipoServicio != 'M' && a.TipoServicio != 'C');

    do {
        printf("Introduzca el numero de orden: ");
        fflush(stdin);
        scanf("%d", &a.NumeroOrden);
        if (a.NumeroOrden < 1) {
            printf("El numero de ordenes no es valido, ingresar nuevamente.\n");
        }
    }while (a.NumeroOrden < 1);


    do {
        printf("Introduzca el costo del servicio: ");
        fflush(stdin);
        scanf("%f", &a.Costo);
        if (a.Costo <= 0) {
            printf("El costo del servicio no puede ser igual o menor a cero. Ingrese nuevamente.\n");
        }
    }while (a.Costo <= 0 );

    int respuesta;
    //use este int respuesta para poder usar %d y detectar como entero a 1 o 0 y asignarle true o false al booleano.
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
void AgregarOrden() {
    t_auto a;
    bool sigo=true;
    FILE *Service_De_Autos = fopen("Service_De_Autos.txt", "a");
    if (Service_De_Autos == NULL) puts("Error al abrir el archivo");
    else {
        while (sigo) {
            a=IngresarDatos(a);
            fprintf(Service_De_Autos,"%s %c %d %.2f %d\n", a.Patente, a.TipoServicio, a.NumeroOrden, a.Costo, a.Finalizo );
            sigo = continua();
        }
        fclose (Service_De_Autos);
    }



}
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
                //ListadoPendientes();
                break;
            }
            case 4: {
                //BuscarPatente();
                break;
            }
            case 5: {
               // SepararSericios();
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