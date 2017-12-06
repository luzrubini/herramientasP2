#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"
#include "funciones.h"
#include <string.h>

int parserTarea(FILE* pFile , ArrayList* listaTarea)
{
    char descripcion[25],prioridad[20],demora[20];
    Tareas* tarea;

    if(listaTarea!=NULL)
    {
        pFile=fopen("tar.csv","r");
        if(pFile!=NULL)
        {
            while(!feof(pFile))
            {
                fscanf(pFile, "%[^,],%[^,],%[^\n]\n",descripcion,prioridad,demora);
                tarea=tarea_new();
                strcpy(tarea->descripcion,descripcion);
                tarea->prioridad=atoi(prioridad);
                tarea->demora=atoi(demora);

                al_add(listaTarea,tarea);
           }
        }
    }
    fclose(pFile);

    return 0;
}
Tareas* tarea_new(void)
{

    Tareas*returnAux=NULL;
    returnAux=(Tareas*)malloc(sizeof(Tareas));
    return returnAux;

}
void tareas_print(Tareas* this)
{
    char prioridad[20];
    if(this!=NULL)
    {
        if(this->prioridad==1)
        {
            strcpy(prioridad,"Alta");
        }
        else
        {
            strcpy(prioridad,"Baja");
        }
        printf("%s\t\t%s\t\t%d\n",this->descripcion,prioridad,this->demora);
    }
}
int tarea_compare(void* tareaA,void* tareaB)
{
    int retorno=0;
    if(((Tareas*)tareaA)->demora<((Tareas*)tareaB)->demora)
    {
        retorno=1;
    }
    if(((Tareas*)tareaA)->demora>((Tareas*)tareaB)->demora)
    {
        retorno=-1;
    }
    return retorno;
}
void parserTareaPorPrioridad(ArrayList* tareas,ArrayList* tareasPAlta,ArrayList* tareasPBaja)
{
    int i;
    Tareas* tarea;
    for(i=0;i<al_len(tareas);i++)
    {
        tarea=(Tareas*) al_get(tareas,i);
        if(tarea->prioridad==1)
        {
            al_add(tareasPAlta,tarea);
        }
        else
        {
            al_add(tareasPBaja,tarea);
        }
    }
    mostrarListaPro(tareas);
    mostrarListaPro(tareasPAlta);
    mostrarListaPro(tareasPBaja);
}
void mostrarListaPro(ArrayList* lista)
{
    int i;
    Tareas* aux;
    system("pause");
    system("cls");
    printf("LISTA DE TAREAS\n\n");
    for(i=0; i<lista->len(lista); i++)
    {
        aux=lista->get(lista,i);
        printf("%d)",i);
        tareas_print(aux);
    }
}
