/*
 * ruta.cpp
 *
 * Kiper, Cristian - padrón 100031.
 * Ligan, Cesar - padrón 101860.
 * Carbajal, Paulo - padrón 101311.
 * Bohn Valiere, Joaquin - padrón 102814.
 */

#include <iostream>
#include <ctime>
#include <sstream>
#include "camino.h"
#include "EasyBMP.h"
#include "EasyBMP_Font.h"
#include "EasyBMP_Geometry.h"

const int Camino::MAX_CONEXIONES = 3;
const int Camino::MAX_CONEXIONES_POR_TIPO = 7;
const double Camino::DISTANCIA_ABSURDA = 10000000;

Camino::Camino(Lista<Estacion*>* transportes) {
	this->camino = new Lista<Recorrido*>;
	this->transportes = transportes;
	this->conAuto = false;
	this->recorridoFinalDelCaminoMasCorto = NULL;
	this->distanciaFinal = DISTANCIA_ABSURDA;
	this->distanciaCaminar = 0;
}

Camino::~Camino() {
	limpiarCamino();
}

bool Camino::buscarRecorridoEnCamino(Recorrido* recorrido) {
	bool encontrado = false;
	this->camino->iniciarCursor();
	while (!encontrado && this->camino->avanzarCursor()) {
		if (recorrido == this->camino->obtenerCursor()) {
			encontrado = true;
		}
	}

	return encontrado;
}

unsigned int Camino::lineaEsta(Lista<Estacion*> &lista, Estacion* &buscada) {
	bool esta = false;
	int posicion = 0;

	lista.iniciarCursor();
	while(!esta && lista.avanzarCursor()) {
		posicion++;
		Estacion* e = lista.obtenerCursor();
		if (e->getLinea().compare(buscada->getLinea()) == 0) {
			esta = true;
		}
	}

	return (esta) ? posicion : 0;
}

bool Camino::verificarPrecondiciones() {
	bool verificado = true;
	if (this->transportes == NULL) {
		verificado = false;
	}

	return verificado;
}

void Camino::limpiarCamino() {
	if (!(this->camino == NULL || this->camino->estaVacia())) {
		this->camino->iniciarCursor();
		while (this->camino->avanzarCursor()) {
			delete this->camino->obtenerCursor();
		}
	}
	delete this->camino;
	this->camino = NULL;
}

void Camino::inicializarCamino() {
	limpiarCamino();
	this->camino = new Lista<Recorrido*>;
}

bool Camino::estoyCerca(Recorrido*& recorrido) {
	return (recorrido->getDestino()->getCoordenadas().distancia(this->destino) < this->distanciaCaminar);
}

void Camino::encontrarParadasCercanas(const Coordenadas& origen, Lista<Estacion*>& paradasOrigen) {
	double distancia;
	this->transportes->iniciarCursor();

	/* recorro la lista de medios de transporte buscando estaciones que esten a
	 * "distanciaCaminar" de distancia del origen
	 */
	while(this->transportes->avanzarCursor()) {
		Estacion* e = this->transportes->obtenerCursor();
		distancia = e->getCoordenadas().distancia(origen);

		/* si no uso el auto descarto los garajes */
		if (e->getTipo() != garaje || this->conAuto) {
			if (distancia < this->distanciaCaminar) {
				int posicion = lineaEsta(paradasOrigen, e);
				/* si la linea esta entre las candidatas pero esta estacion
				 * esta mas cerca que la anterior, la agrego */
				if (posicion > 0) {
					int distanciaVieja = paradasOrigen.obtenerCursor()->getCoordenadas().distancia(origen);
					if (distancia < distanciaVieja) {
						paradasOrigen.remover(posicion);
						paradasOrigen.agregar(e);
					}
				} else {
					/* si la linea no esta todavia dentro de las candidatas, la agrego */
					paradasOrigen.agregar(e);
				}
			}
		}
	}
}

Recorrido* Camino::generarRecorrido(Estacion* partida, double total, Recorrido* recorridoAnterior) {
	double distanciaAlDestino = DISTANCIA_ABSURDA;
	Estacion* llegada = NULL;
	Recorrido* recorrido = NULL;
	this->transportes->iniciarCursor();

	while(transportes->avanzarCursor()) {
		Estacion* e = this->transportes->obtenerCursor();

		if (e->getTipo() == partida->getTipo() && e->getLinea().compare(partida->getLinea()) == 0) {
			double distancia = e->getCoordenadas().distancia(this->destino);
			if (distancia < distanciaAlDestino
					&& partida->getCoordenadas().distancia(e->getCoordenadas()) > this->distanciaCaminar) {
				distanciaAlDestino = distancia;
				llegada = e;
			}
		}
	}

	if (llegada != NULL
			&& !partida->esIgual(llegada)
			&& this->destino.distancia(llegada->getCoordenadas()) <  this->destino.distancia(partida->getCoordenadas())) {
		recorrido = new Recorrido(partida, llegada, total, recorridoAnterior);
	}

	return recorrido;
}

Recorrido* Camino::crearRecorrido(Lista<Estacion*>& nuevosOrigenes, int cantidadPorTipo[], double distanciaTotal, Recorrido* recorrido) {
	Recorrido* nuevoRecorrido = NULL;
	Estacion* nuevoOrigen = nuevosOrigenes.obtenerCursor();

	cantidadPorTipo[nuevoOrigen->getTipo()]++;
	if (cantidadPorTipo[nuevoOrigen->getTipo()] < MAX_CONEXIONES_POR_TIPO) {
		nuevoRecorrido = this->generarRecorrido(nuevoOrigen, distanciaTotal, recorrido);
	}

	return nuevoRecorrido;
}

void Camino::agregarRecorrido(Recorrido* r, int conexiones) {
	int cantidadPorTipo[5] = {0, 0, 0, 0, 0};
	if (conexiones < MAX_CONEXIONES) {
		if (r != NULL && r->getDestino()->getCoordenadas().distancia(this->destino) > this->distanciaCaminar) {
			Lista<Estacion*> nuevosOrigenes;
			this->encontrarParadasCercanas(r->getDestino()->getCoordenadas(), nuevosOrigenes);
			nuevosOrigenes.iniciarCursor();
			while(nuevosOrigenes.avanzarCursor()) {
				Recorrido* nuevoRecorrido = this->crearRecorrido(nuevosOrigenes, cantidadPorTipo,r->getDistanciaTotal(), r);
				if (nuevoRecorrido != NULL) {
					r->getSiguientes()->agregar(nuevoRecorrido);
					this->agregarRecorrido(nuevoRecorrido, conexiones + 1);
				}
			}
		}
	}
}

void Camino::crearCaminoMasCorto() {
	this->camino->agregar(this->recorridoFinalDelCaminoMasCorto);
	Recorrido* aux = this->recorridoFinalDelCaminoMasCorto->getAnterior();
	while(aux != NULL) {
		this->camino->agregar(aux, 1);
		aux = aux->getAnterior();
	}
}

void Camino::limpiarRecorridos(Recorrido* recorrido) {
	if (recorrido != NULL) {
		recorrido->getSiguientes()->iniciarCursor();
		while(recorrido->getSiguientes()->avanzarCursor()) {
			this->limpiarRecorridos(recorrido->getSiguientes()->obtenerCursor());
		}
		if (!this->buscarRecorridoEnCamino(recorrido)) {
			delete recorrido;
		}
	}
}

bool Camino::generarCaminos(Coordenadas& origen, Coordenadas& destino, int distancia, bool conAuto) {
	bool caminoGenerado = false;

	if (!verificarPrecondiciones()) {
		return false;
	}

	Lista<Recorrido*> raices;
	int cantidadPorTipo[5] = {0, 0, 0, 0, 0};

	inicializarCamino();

	this->destino = destino;
	this->distanciaCaminar = distancia;
	this->conAuto = conAuto;

	Lista<Estacion*> estacionesOrigen;
	this->encontrarParadasCercanas(origen, estacionesOrigen);
	estacionesOrigen.iniciarCursor();
	while(estacionesOrigen.avanzarCursor()) {
		Recorrido* nuevoRecorrido = this->crearRecorrido(estacionesOrigen, cantidadPorTipo, 0, NULL);
		if (nuevoRecorrido != NULL) {
			raices.agregar(nuevoRecorrido);
		}
	}

	raices.iniciarCursor();
	while(raices.avanzarCursor()) {
		this->agregarRecorrido(raices.obtenerCursor(), 0);
	}

	raices.iniciarCursor();
	while(raices.avanzarCursor()) {
		this->buscarCaminoMasCorto(raices.obtenerCursor());
	}

	if (this->recorridoFinalDelCaminoMasCorto != NULL) {
		caminoGenerado = true;
		this->origen = origen;
		this->crearCaminoMasCorto();
	}

	raices.iniciarCursor();
	while(raices.avanzarCursor()) {
		this->limpiarRecorridos(raices.obtenerCursor());
	}

	return caminoGenerado;
}

void Camino::buscarCaminoMasCorto(Recorrido* r) {
	if (r != NULL) {
		if (this->estoyCerca(r)) {
			if (r->getDistanciaTotal() < this->distanciaFinal) {
				this->distanciaFinal = r->getDistanciaTotal();
				this->recorridoFinalDelCaminoMasCorto = r;
			}
		}
		r->getSiguientes()->iniciarCursor();
		while(r->getSiguientes()->avanzarCursor()) {
			this->buscarCaminoMasCorto(r->getSiguientes()->obtenerCursor());
		}
	}
}

void Camino::setTransportes(Lista<Estacion*> *&transportes) {
	this->transportes = transportes;
}

void Camino::imprimirCamino() {
	//std::cout << "Camino prefiriendo " << Estacion::TIPOS[this->preferencia] << ":" << std::endl;
	if (this->camino == NULL || this->camino->estaVacia()) {
		std::cout << "No hay camino." << std::endl;
	} else {
		std::string tiempo;
		std::stringstream strstream;
		strstream << std::time(0);
		strstream >> tiempo;

		this->camino->iniciarCursor();

		/*largo corresponde a una ubicacion dentro de la imagen bmp*/
		unsigned int largo=50, contador=1;

		/*se crea un archivo tipo bmp*/
		BMP imagen;
		int cantidad = this->camino->contarElementos();

		/*configura el tamanio de la imagen ajustandose a la cantidad
		 * de recorridos del camino */
		imagen.SetSize(640*cantidad,480);
		imagen.SetBitDepth(8);

		while(this->camino->avanzarCursor()) {
			Recorrido* recorrido = this->camino->obtenerCursor();

			/*colorearRecorrido agrega las estaciones a la imagen*/
			this->colorearRecorrido(imagen, recorrido, largo);

			/*mientras queden recorridos se agregan uniones entre ellos*/
			if(contador<(this->camino->contarElementos())){
				/*colorearTrayecto agrega dichas uniones*/
				this->colorearTrayecto(imagen, largo+395, largo+475);
			}

			/*se agregan los nombres de las estaciones de origen y destino*/
			this->agregarTextos(imagen, largo, contador, recorrido);

			/*se suma a largo el tamanio ocupado en la imagen de todo lo anterior
			 * para continuar desde alli en la proxima iteracion*/
			largo += 480;
			contador++;

			std::cout << Estacion::TIPOS[recorrido->getOrigen()->getTipo()] << " "
					<< recorrido->getOrigen()->getLinea()
					<< ": de " << recorrido->getOrigen()->getNombre()
					<< " hasta " << recorrido->getDestino()->getNombre() << std::endl;
		}

		std::cout << "Distancia: " << this->distanciaFinal << " metros." << std::endl << std::endl;

		/*se guarda la imagen en el archivo bmp*/
		std::cout << "Generando imagen..." << std::endl;
		std::string nombreArchivo = tiempo + ".bmp";
		imagen.WriteToFile(nombreArchivo.c_str());
		std::cout << "Imagen generada." << std::endl;
	}
	std::cout << std::endl;
}

bool Camino::esIgual(Camino*& camino) {
	bool sonIguales = true;

	if (camino == NULL || camino->camino == NULL) {
		sonIguales = false;
	}
	else if (this->camino->contarElementos() != camino->camino->contarElementos()) {
		sonIguales = false;
	} else {
		this->camino->iniciarCursor();
		camino->camino->iniciarCursor();

		while(sonIguales && this->camino->avanzarCursor()) {
			camino->camino->avanzarCursor();
			Recorrido* recorrido1 = this->camino->obtenerCursor();
			Recorrido* recorrido2 = camino->camino->obtenerCursor();

			if (!recorrido1->esIgual(recorrido2)) {
				sonIguales = false;
			}
		}
	}

	return sonIguales;
}


/* --------------- EASYBMP ---------------------*/


void Camino::colorearRecorrido(BMP& imagen, Recorrido* recorrido, unsigned int largo){
	/*se crea una paleta de colores*/
	ebmpBYTE azul, rojo, verde;
	/*configura los valores para la paleta de colores segun el tipo de estacion*/
	this->coloresSegunEstacion(azul, rojo, verde, recorrido->getOrigen());

	/*agrega las estaciones del recorrido a la imagen*/
	this->colorearEstaciones(azul,rojo, verde, imagen, largo);
	/*agrega la union entre las estaciones del recorrido*/
	this->colorearTrayecto(imagen, largo+155, largo+235);
}

void Camino::coloresSegunEstacion(ebmpBYTE& color1, ebmpBYTE& color2, ebmpBYTE& color3, Estacion* estacion){
	if(estacion->getTipo() == subte){
		color1 = 0;
		color2 = 150;
		color3 = 150;
	}else if(estacion->getTipo() == colectivo){
		color1 = 200;
		color2 = 0;
		color3 = 0;
	}else if(estacion->getTipo() == tren){
		color1 = 0;
		color2 = 100;
		color3 = 0;
	}else if(estacion->getTipo() == metrobus){
		color1 = 100;
		color2 = 100;
		color3 = 50;
	}else{
		color1 = 150;
		color2 = 0;
		color3 = 150;
	}
}

void Camino::colorearEstaciones(ebmpBYTE color1, ebmpBYTE color2, ebmpBYTE color3, BMP& imagen, unsigned int largo){
	/*agrega la estacion de origen del recorrido*/
	this->colorearEstacion(color1, color2, color3, imagen, largo, largo+150);
	/*agrega la estacion de destino del recorrido*/
	this->colorearEstacion(color1, color2, color3, imagen, largo+240, largo+390);
}

void Camino::colorearEstacion(ebmpBYTE color1, ebmpBYTE color2, ebmpBYTE color3, BMP& imagen, unsigned int iInicio, unsigned int iFinal){
	/*recorre pixel por pixel desde la ubicacion indicada hasta el final de ella
	 * y agrega el color que corresponda a cada pixel para colorear la estacion*/
	for(unsigned int i=iInicio; i<iFinal; i++){
		for(unsigned int j=200; j<280; j++){
			imagen(i,j)->Blue = color1;
			imagen(i,j)->Red = color2;
			imagen(i,j)->Green = color3;
		}
	}
}

void Camino::colorearTrayecto(BMP& imagen, unsigned int iInicio, unsigned int iFinal){
	/*recorre piexel por pixel desde la ubicacion indicada hasta el final de ella
	 * y agrega color para colorear la union entre estaciones*/
	for(unsigned int i=iInicio; i<iFinal; i++){
		for(unsigned int j=235; j<245; j++){
			imagen(i,j)->Blue = 0;
			imagen(i,j)->Red = 0;
			imagen(i,j)->Green = 200;
		}
	}
}

void Camino::agregarTextoAImagen(BMP& imagen, const char* texto, unsigned int x, unsigned int y){
	/*crea una paleta de colores*/
	RGBApixel fontColor;
	/*configura los valores de la paleta de colores*/
	fontColor.Red = 255; fontColor.Green = 0; fontColor.Blue = 0; fontColor.Alpha = 255;
	char textoAImprimir[50];
	/*se copia el texto del archivo a un puntero a char para agregar dicho texto a la imagen*/
	strcpy(textoAImprimir, texto);
	/*PrintString agrega el texto a la imagen en la ubicacion (x,y) con un tamanio de fuente
	 * 10 y la paleta de colores configurada*/
	PrintString(imagen, textoAImprimir, x, y, 10, fontColor);
	/*se libera la memoria*/
}

void Camino::agregarTextos(BMP& imagen,unsigned int largo, unsigned int contador, Recorrido* recorrido){
	/*si es la primera estacion del camino, toma la linea y el nombre de la estacion,
	 * y los agrega a la imagen*/
	if(contador==1){
		std::string lineaTransporte = recorrido->getOrigen()->getLinea();
		const char* linea = lineaTransporte.c_str();
		std::string nombreTransporte = recorrido->getOrigen()->getNombre();
		const char* nombre = nombreTransporte.c_str();
		this->agregarTextoAImagen(imagen, linea, largo, 290);
		this->agregarTextoAImagen(imagen, nombre, largo, 315);
	}
	/*el mismo proceso pero para la ultima estacion del camino*/
	if(contador==(this->camino->contarElementos())){
		std::string lineaTransporte = recorrido->getDestino()->getLinea();
		const char* linea = lineaTransporte.c_str();
		std::string nombreTransporte = recorrido->getDestino()->getNombre();
		const char* nombre = nombreTransporte.c_str();
		this->agregarTextoAImagen(imagen, linea, largo+240, 290);
		this->agregarTextoAImagen(imagen, nombre, largo+240, 315);
	}
}
