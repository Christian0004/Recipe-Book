#include <iostream>
#include <fstream>
#include <Windows.h>

#include "SLList.hpp"
#include "DLList.hpp"
#include "Ingredient.hpp"
#include "Recipe.hpp"
#include "Name.hpp"

using namespace std;

int main() {

    DLList<Recipe> RecipeList;
    SLList<Ingredient> IngredientList;

    int op = 0, op2 = 0, preparationTime = 0, pos = 0;

    string category, name, lastName, recipeName, recipeType, procedure, ingName, measureUnit;

    float ingAmount = 0, ingCan = 0;

    Recipe auxiliarRecipe;
    Name auxiliarName;
    Ingredient auxiliarIngredient;
    DLList<Recipe>::Position aux = nullptr;

    while(op != 14){
        system("cls");
        cout << "\n----------------------------------------------------------------------------------------" << endl;
        cout << "\n\t\t\t\t\tRecetario" << endl;
        cout << "\n----------------------------------------------------------------------------------------" << endl;
        cout << "1. Mostrar lista de recetas" << endl;
        cout << "2. Agregar receta" << endl;
        cout << "3. Buscar receta" << endl;
        cout << "4. Eliminar una receta" << endl;
        cout << "5. Eliminar recetario" << endl;
        cout << "6. Ordenar recetas" << endl;
        cout << "7. Agregar ingrediente a una receta" << endl;
        cout << "8. Eliminar ingrediente de una receta" << endl;
        cout << "9. Eliminar todos los ingredientes de una receta" << endl;
        cout << "10. Modificar la cantidad de un ingrediente" << endl;
        cout << "11. Modificar el procedimiento de una receta" << endl;
        cout << "12. Guardar recetario en disco" << endl;
        cout << "13. Leer recetario de disco" << endl;
        cout << "14. Salir del programa" << endl << endl;
        cout << "Seleccione una opcion: ";
        cin >> op;
        fflush(stdin);

        switch(op) {
        case 1: {

            Sleep(1000);
            system("cls");
            auxiliarName.initialize();
            auxiliarRecipe.initialize();
            auxiliarIngredient.initialize();
            IngredientList.initialize();

            cout << "\n--------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\tMostrar Recetario" << endl;
            cout << "\n--------------------------------------------------------------------------------" << endl;

            cout << "\n1. Mostrar todas las recetas" << endl;
            cout << "2. Filtrar por categoria: " << endl;
            cout << "Seleccione una opcion: ";
            cin >> op2;
            fflush(stdin);

            if(op2 == 1){

                cout << RecipeList.toString() << endl;

            } else {

                cout << "\nIngresa la categoria: ";
                getline(cin, category);
                fflush(stdin);
                DLList<Recipe>::Position i = RecipeList.getFirstPos();

                while(i != nullptr){

                    auxiliarRecipe = RecipeList.retrieve(i);
                    recipeType = auxiliarRecipe.getRecipeType();
                    if(recipeType == category){
                        cout << auxiliarRecipe.toString() << endl;
                        cout << endl;
                    }
                    i = RecipeList.getNextPos(i);
                }
            }

            cout << "\nPresione enter para volver . . . " << endl;
            getchar();
            Sleep(500);

        break;
        }

        case 2: {

            Sleep(1000);
            system("cls");
            auxiliarName.initialize();
            auxiliarRecipe.initialize();
            auxiliarIngredient.initialize();
            IngredientList.initialize();

            cout << "\n--------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\tAgregar una Receta" << endl;
            cout << "\n--------------------------------------------------------------------------------" << endl;

            cout << "\nIngrese el nombre del autor: ";
            getline(cin, name);
            auxiliarName.setName(name);
            fflush(stdin);

            cout << "\nIngrese el apellido del autor: ";
            getline(cin, lastName);
            fflush(stdin);
            auxiliarName.setLastName(lastName);
            auxiliarRecipe.setAuthor(auxiliarName);

            cout << "\nIngrese el tiempo de preparacion (en minutos): ";
            cin >> preparationTime;
            auxiliarRecipe.setPreparationTime(preparationTime);
            fflush(stdin);

            cout << "\nIngrese el nombre de la receta: ";
            getline(cin, recipeName);
            auxiliarRecipe.setRecipeName(recipeName);
            fflush(stdin);

            cout << "\nIngrese el tipo de la receta: ";
            getline(cin, recipeType);
            auxiliarRecipe.setRecipeType(recipeType);
            fflush(stdin);

            cout << "\nIngrese el procedimiento de la receta: ";
            getline(cin, procedure);
            auxiliarRecipe.setProcedure(procedure);
            fflush(stdin);

            cout << "\nIngrese la cantidad de ingredientes: ";
            cin >> ingAmount;
            fflush(stdin);
            int i = 0;
            while (i < ingAmount){

                SLList<Ingredient>::Position aux = IngredientList.getFirstPos();
                auxiliarIngredient.initialize();
                cout << "\nIngrese el nombre del ingrediente " << i + 1 << ": ";
                getline(cin, ingName);
                auxiliarIngredient.setIngredient(ingName);
                fflush(stdin);
                cout << "\nIngrese la cantidad del ingrediente " << i + 1 << ": ";
                cin >> ingCan;
                auxiliarIngredient.setAmount(ingCan);
                fflush(stdin);
                cout << "\nIngrese la unidad de medida del ingrediente " << i + 1 << ": ";
                getline(cin, measureUnit);
                auxiliarIngredient.setMeasureUnit(measureUnit);
                fflush(stdin);
                cout << endl << endl;
                IngredientList.insertData(aux, auxiliarIngredient);
                i++;

            }

            auxiliarRecipe.setIngredientsList(IngredientList);
            cout << "\nIngrese la posicion de insercion: ";
            cin >> pos;
            fflush(stdin);

            if(RecipeList.isEmpty()){

                RecipeList.insertData(nullptr, auxiliarRecipe);

            } else {

                aux = RecipeList.getIndex(pos);
                RecipeList.insertData(aux, auxiliarRecipe);
            }

            cout << "\nPresione enter para volver . . . " << endl;
            getchar();
            Sleep(500);

        break;
        }

        case 3: {

            Sleep(1000);
            system("cls");
            auxiliarName.initialize();
            auxiliarRecipe.initialize();
            auxiliarIngredient.initialize();
            IngredientList.initialize();

            cout << "\n--------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\tBuscar una Receta" << endl;
            cout << "\n--------------------------------------------------------------------------------" << endl;

            cout << "\n1. Buscar por nombre" << endl;
            cout << "2. Buscar por categoria" << endl;
            cout << "Seleccione una opcion: ";
            cin >>op2;
            fflush(stdin);
            if (op2 == 1){

                cout << "\nIngresa el nombre de la receta: ";
                getline(cin, recipeName);
                fflush(stdin);
                auxiliarRecipe.setRecipeName(recipeName);
                aux = RecipeList.linealSearch(auxiliarRecipe, Recipe::compByName);

            } else {

                cout << "\nIngresa la categoria de la receta: ";
                getline(cin, recipeType);
                fflush(stdin);
                auxiliarRecipe.setRecipeType(recipeType);
                aux = RecipeList.linealSearch(auxiliarRecipe, Recipe::compByType);

            }

            if (aux == nullptr){

                cout << "\nNo se ha encontrado niguna receta" << endl;

            } else {

                cout << "\nLa receta es: " << endl;
                cout << RecipeList.retrieve(aux).toString();

            }

            cout << "\nPresione enter para volver . . . " << endl;
            getchar();
            Sleep(500);

        break;
        }

        case 4: {

            Sleep(1000);
            system("cls");
            auxiliarName.initialize();
            auxiliarRecipe.initialize();
            auxiliarIngredient.initialize();
            IngredientList.initialize();

            cout << "\n--------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\tEliminar una Receta" << endl;
            cout << "\n--------------------------------------------------------------------------------" << endl;

            cout << "\nIngresa el nombre de la receta: ";
            getline(cin, recipeName);
            fflush(stdin);
            auxiliarRecipe.setRecipeName(recipeName);

            aux = RecipeList.linealSearch(auxiliarRecipe, Recipe::compByName);
            RecipeList.deleteData(aux);

            cout << "\nSe ha eliminado la receta " << auxiliarRecipe.getRecipeName() << endl;

            cout << "\nPresione enter para volver . . . " << endl;
            getchar();
            Sleep(500);

        break;
        }

        case 5: {

            Sleep(1000);
            system("cls");
            cout << "\n--------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\tEliminar Recetario" << endl;
            cout << "\n--------------------------------------------------------------------------------" << endl;

            RecipeList.deleteAll();
            cout << "\nSe ha eliminado el recetario" << endl;

            cout << "\nPresione enter para volver . . . " << endl;
            getchar();
            Sleep(500);

        break;
        }

        case 6: {

            Sleep(1000);
            system("cls");
            auxiliarName.initialize();
            auxiliarRecipe.initialize();
            auxiliarIngredient.initialize();
            IngredientList.initialize();

            cout << "\n--------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\tOrdenar Recetas" << endl;
            cout << "\n--------------------------------------------------------------------------------" << endl;

            cout << "\n1. Ordenar por nombre" << endl;
            cout << "2. Ordenar por tiempo de preparacion" << endl;
            cout << "Seleccione una opcion: ";
            cin >> op2;
            fflush(stdin);

            if (op2 == 1) {

                RecipeList.quickSort(Recipe::compByName);
                cout << "\nSe ha ordenado el recetario por nombre" << endl;

            } else {

                RecipeList.quickSort(Recipe::compByPreparationTime);
                cout << "\nSe ha ordenado el recetario por tiempo de preparacion" << endl;
            }

            cout << "\nPresione enter para volver . . . " << endl;
            getchar();
            Sleep(500);

        break;
        }

        case 7: {

            Sleep(1000);
            system("cls");
            auxiliarName.initialize();
            auxiliarRecipe.initialize();
            auxiliarIngredient.initialize();
            IngredientList.initialize();

            cout << "\n------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\tAgregar un Ingrediente" << endl;
            cout << "\n------------------------------------------------------------------------------------" << endl;

            cout << "\nIngresa el nombre del ingrediente: ";
            getline(cin, ingName);
            fflush(stdin);
            auxiliarIngredient.setIngredient(ingName);

            cout << "\nIngresa la cantidad del ingrediente: ";
            cin >> ingCan;
            fflush(stdin);
            auxiliarIngredient.setAmount(ingCan);

            cout << "\nIngresa la unidad de medida del ingrediente: ";
            cin >> measureUnit;
            fflush(stdin);
            auxiliarIngredient.setMeasureUnit(measureUnit);

            cout << "\nIngresa el nombre de la receta en donde se agregara el ingrediente: ";
            getline(cin, recipeName);
            fflush(stdin);
            auxiliarRecipe.setRecipeName(recipeName);

            aux = RecipeList.linealSearch(auxiliarRecipe, Recipe::compByName);

            auxiliarRecipe = RecipeList.retrieve(aux);

            IngredientList = auxiliarRecipe.getIngredientsList();
            SLList<Ingredient>::Position aux2 = IngredientList.getFirstPos();

            IngredientList.insertData(aux2, auxiliarIngredient);
            auxiliarRecipe.setIngredientsList(IngredientList);
            RecipeList.insertData(aux, auxiliarRecipe);
            RecipeList.deleteData(aux);

            cout << "\nSe ha agregado el ingrediente " << auxiliarIngredient.getIngredient()
            << " en la receta " << auxiliarRecipe.getRecipeName() << endl;

            cout << "\nPresione enter para volver . . . " << endl;
            getchar();
            Sleep(500);

        break;
        }

        case 8: {

            Sleep(1000);
            system("cls");
            auxiliarName.initialize();
            auxiliarRecipe.initialize();
            auxiliarIngredient.initialize();
            IngredientList.initialize();

            cout << "\n-----------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\tEliminar un Ingrediente" << endl;
            cout << "\n-----------------------------------------------------------------------------------" << endl;

            cout << "\nIngresa el nombre de la receta a la que se le eliminara un ingrediente: ";
            getline(cin, recipeName);
            auxiliarRecipe.setRecipeName(recipeName);
            fflush(stdin);

            aux = RecipeList.linealSearch(auxiliarRecipe, Recipe::compByName);
            auxiliarRecipe = RecipeList.retrieve(aux);
            IngredientList = auxiliarRecipe.getIngredientsList();

            cout << "\nIngresa el nombre del ingrediente a eliminar: ";
            getline(cin, ingName);
            auxiliarIngredient.setIngredient(ingName);
            fflush(stdin);

            SLList<Ingredient>::Position deletePos = IngredientList.linealSearch(auxiliarIngredient, Ingredient::compareByName);

            IngredientList.deleteData(deletePos);
            auxiliarRecipe.setIngredientsList(IngredientList);
            RecipeList.insertData(aux, auxiliarRecipe);
            RecipeList.deleteData(aux);

            cout << "\nSe ha eliminado el ingrediente " << auxiliarIngredient.getIngredient()
            << " en la receta " << auxiliarRecipe.getRecipeName() << endl;

            cout << "\nPresione enter para volver . . . " << endl;
            getchar();
            Sleep(500);


        break;
        }

        case 9: {

            Sleep(1000);
            system("cls");
            auxiliarName.initialize();
            auxiliarRecipe.initialize();
            auxiliarIngredient.initialize();
            IngredientList.initialize();

            cout << "\n--------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\tEliminar Todos los Ingredientes" << endl;
            cout << "\n--------------------------------------------------------------------------------" << endl;

            cout << "\nIngresa el nombre de la receta a la que se le eliminaran los ingredientes: ";
            getline(cin, recipeName);
            auxiliarRecipe.setRecipeName(recipeName);
            fflush(stdin);

            aux = RecipeList.linealSearch(auxiliarRecipe, Recipe::compByName);

            auxiliarRecipe = RecipeList.retrieve(aux);
            IngredientList = auxiliarRecipe.getIngredientsList();
            IngredientList.deleteAll();
            auxiliarRecipe.setIngredientsList(IngredientList);
            RecipeList.insertData(aux, auxiliarRecipe);
            RecipeList.deleteData(aux);

            cout << "\nSe han eliminado los ingredientes de la receta " << auxiliarRecipe.getRecipeName() << endl;

            cout << "\nPresione enter para volver . . . " << endl;
            getchar();
            Sleep(500);

        break;
        }

        case 10: {

            Sleep(1000);
            system("cls");
            auxiliarName.initialize();
            auxiliarRecipe.initialize();
            auxiliarIngredient.initialize();
            IngredientList.initialize();

            cout << "\n--------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\tModificar Cantidad de Ingrediente" << endl;
            cout << "\n--------------------------------------------------------------------------------" << endl;

            cout << "\nIngresa el nombre de la receta a la que se le modificara la cantidad del ingrediente: ";
            getline(cin, recipeName);
            fflush(stdin);
            auxiliarRecipe.setRecipeName(recipeName);

            aux = RecipeList.linealSearch(auxiliarRecipe, Recipe::compByName);

            auxiliarRecipe = RecipeList.retrieve(aux);
            IngredientList = auxiliarRecipe.getIngredientsList();

            cout << "\nIngresa el nombre del ingrediente al que se le modificara la cantidad: ";
            getline(cin, ingName);
            fflush(stdin);
            auxiliarIngredient.setIngredient(ingName);

            SLList<Ingredient>::Position aux2 = IngredientList.linealSearch(auxiliarIngredient, Ingredient::compareByName);
            auxiliarIngredient = IngredientList.retrieve(aux2);

            cout << "\nIngresa la nueva cantidad del ingrediente: ";
            cin >> ingCan;
            fflush(stdin);
            auxiliarIngredient.setAmount(ingCan);

            IngredientList.insertData(aux2, auxiliarIngredient);
            IngredientList.deleteData(aux2);

            auxiliarRecipe.setIngredientsList(IngredientList);
            RecipeList.insertData(aux, auxiliarRecipe);
            RecipeList.deleteData(aux);

            cout << "\nSe ha actualizado la cantidad del ingrediente " << auxiliarIngredient.getIngredient()
            << " en la receta " << auxiliarRecipe.getRecipeName() << endl;

            cout << "\nPresione enter para volver . . . " << endl;
            getchar();
            Sleep(500);

        break;
        }

        case 11: {

            Sleep(1000);
            system("cls");
            auxiliarName.initialize();
            auxiliarRecipe.initialize();
            auxiliarIngredient.initialize();
            IngredientList.initialize();

            cout << "\n--------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\tModificar Procedimiento de Receta" << endl;
            cout << "\n--------------------------------------------------------------------------------" << endl;

            cout << "\nIngresa el nombre de la receta a la que se le modificara el procedimiento: ";
            getline(cin, recipeName);
            fflush(stdin);
            auxiliarRecipe.setRecipeName(recipeName);

            aux = RecipeList.linealSearch(auxiliarRecipe, Recipe::compByName);

            auxiliarRecipe = RecipeList.retrieve(aux);

            cout << "\nIngresa el nuevo procedimiento: ";
            getline(cin, procedure);
            fflush(stdin);
            auxiliarRecipe.setProcedure(procedure);

            RecipeList.insertData(aux, auxiliarRecipe);
            RecipeList.deleteData(aux);

            cout << "\nSe ha modificado el procedimiento de la receta " << auxiliarRecipe.getRecipeName() << endl;

            cout << "\nPresione enter para volver . . . " << endl;
            getchar();
            Sleep(500);

        break;
        }

        case 12: {

            Sleep(1000);
            system("cls");
            auxiliarName.initialize();
            auxiliarRecipe.initialize();
            auxiliarIngredient.initialize();
            IngredientList.initialize();

            cout << "\n--------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\tGuardar en Disco" << endl;
            cout << "\n--------------------------------------------------------------------------------" << endl;

            if (RecipeList.isEmpty()) {
                cout << "\nNo hay recetas para guardar . . ." << endl;
                Sleep(500);
                system("cls");
                break;
            }

            cout << "\nEscribiendo recetario en disco . . ." << endl;
            Sleep(1500);
            RecipeList.writeToDisk("recetario.txt");
            cout << "El recetario se ha guardado correctamente" << endl;
            cout << "\nPresione enter para volver . . . " << endl;
            getchar();
            Sleep(500);

        break;
        }

        case 13: {

            Sleep(1000);
            system("cls");
            auxiliarName.initialize();
            auxiliarRecipe.initialize();
            auxiliarIngredient.initialize();
            IngredientList.initialize();

            cout << "\n--------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\tLeer de Disco" << endl;
            cout << "\n--------------------------------------------------------------------------------" << endl;
            cout << "\nLeyendo del disco . . ." << endl;
            RecipeList.readFromDisk("recetario.txt");
            Sleep(1500);

            cout << "\nContenido del recetario: " << endl;
            cout << RecipeList.toString() << endl;

            cout << "\nPresione enter para volver . . . " << endl;
            getchar();
            Sleep(500);

        break;
        }

        case 14: {

            cout << "\nSaliendo del programa . . ." << endl;
            break;

        break;
        }

        default:

            cout << "\nSeleccione una opcion valida . . ." << endl;
            cout << "\nPresione enter para volver . . . " << endl;
            getchar();
            Sleep(500);
        }
    }

    return 0;

}
