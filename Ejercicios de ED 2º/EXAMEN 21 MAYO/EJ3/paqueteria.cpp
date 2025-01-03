/**
  NOMBRE Y APELLIDOS:
  USUARIO DE DOMJUDGE USADO EN EL EXAMEN:
*/

#include "paqueteria.h"

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
Paqueteria::Paqueteria() {
    // A IMPLEMENTAR

}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
void Paqueteria::recepciona_paquete(IdPaquete id, string dir, float peso) {
    // A IMPLEMENTAR
    if (_paquetes.contiene(id)) {
        throw EPaqueteDuplicado();
    }
    else {
        tInfoPaquete infoPaquete;
        infoPaquete._dir = dir;
        infoPaquete._peso = peso;
        _paquetes.inserta(id, infoPaquete);
        _lista_paquetes.pon_ppio(id);
        Lista<IdPaquete>::Iterator it_paquete = _lista_paquetes.begin();
        _dic_iterator.inserta(id, it_paquete);
    }
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
void Paqueteria::info_paquete(IdPaquete id, string& dir, float& peso) const {
    // A IMPLEMENTAR
    DiccionarioHash<IdPaquete, tInfoPaquete>::ConstIterator cit_paquete = _paquetes.cbusca(id);
    if (cit_paquete != _paquetes.cend()) {
        dir = cit_paquete.valor()._dir;
        peso = cit_paquete.valor()._peso;
    }
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
bool Paqueteria::hay_paquetes() const {
    // A IMPLEMENTAR
    return !_lista_paquetes.esVacia();
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
void Paqueteria::primero_en_fila(IdPaquete& id) const {
    // A IMPLEMENTAR
    if (_lista_paquetes.esVacia()) {
        throw ENingunPaqueteEnEspera();
    }
    else {
        id = _lista_paquetes.ultimo();
    }
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
void Paqueteria::nuevo_camion(float peso) {
    // A IMPLEMENTAR
    _camiones.pon_ppio(peso);
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
void Paqueteria::primer_camion(float& peso) const {
    // A IMPLEMENTAR
    if (_camiones.esVacia()) {
        throw ENingunCamionEnEspera();
    }
    else {
        peso = _camiones.ultimo();
    }
}


void Paqueteria::elimina(IdPaquete id) {
    // A IMPLEMENTAR
    DiccionarioHash<IdPaquete, tInfoPaquete>::ConstIterator cit_paquete = _paquetes.cbusca(id);   
    DiccionarioHash<IdPaquete, it_paquetes>::ConstIterator cit_it_paquete = _dic_iterator.cbusca(id);

    if (cit_paquete != _paquetes.cend()) {
        _paquetes.borra(id);
        _lista_paquetes.eliminar(cit_it_paquete.valor());
        _dic_iterator.borra(id);
    }

}


Lista<IdPaquete> Paqueteria::carga_camion() {
    // A IMPLEMENTAR
    Lista<IdPaquete> lista_ids;
    if (_camiones.esVacia() || _lista_paquetes.esVacia()) {
        throw EErrorCarga();
    }
    else {
        int peso = _camiones.ultimo();
       
        DiccionarioHash<IdPaquete, tInfoPaquete>::ConstIterator cit_paquetes = _paquetes.cbusca(_lista_paquetes.ultimo());

        while (cit_paquetes != _paquetes.cend() && peso - cit_paquetes.valor()._peso >= 0){
            lista_ids.pon_final(cit_paquetes.clave());
            peso -= cit_paquetes.valor()._peso;
            cit_paquetes.next();
        }
        _camiones.quita_final();


        return lista_ids;
    }



    
}


   
