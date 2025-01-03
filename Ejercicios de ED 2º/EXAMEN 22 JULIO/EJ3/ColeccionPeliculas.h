// NOMBRE Y APELLIDOS:
// USUARIO DEL JUEZ:

#ifndef _coleccionPeliculas_H
#define _coleccionPeliculas_H

#include "lista.h"
#include "DiccionarioHash.h"
#include "diccionario.h"
#include <string>
using namespace std;

// clases para las excepciones
class ECategoriaDuplicada {};  // excepción asociada a "an_categoria"

class ECategoriaNoExiste {}; // excepción asociada a "an_pelicula", "lista_por_nombre"
                             // y "lista_cronologicamente" 

class EPeliculaDuplicada {};  // excepción asociada a "an_pelicula"

typedef string tPelicula;  // tipo para representar las películas
typedef string tCategoria;  // tipo para representar las categorias

class ColeccionPeliculas {
public:
    ColeccionPeliculas(); // Operación "Crea"
    void an_categoria(const tCategoria& c);
    void an_pelicula(const tCategoria& c, const tPelicula& p);
    Lista<tPelicula> lista_por_nombre(const tCategoria& c) const;
    Lista<tPelicula> lista_cronologicamente(const tCategoria& c) const;
    void elimina_pelicula(const tPelicula& p);
private:
   // A COMPLETAR CON LOS DETALLES DE REPRESENTACION

    typedef struct {
        Diccionario<tPelicula, tCategoria> _orden_peliculas;
        Lista<tPelicula> _peliculas_de_la_categ;
        Lista<tPelicula>::Iterator _it_pelicula;
        DiccionarioHash<tPelicula, tCategoria> _peliculas;
    }tInfoCategoria;

    typedef DiccionarioHash<tCategoria, bool> tInfoPelicula;

    DiccionarioHash<tCategoria, tInfoCategoria> _categorias;
    DiccionarioHash<tPelicula, tInfoPelicula> _dic_peliculas;
};

  
#endif