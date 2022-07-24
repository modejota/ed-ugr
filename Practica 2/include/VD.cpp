template <class T>
void VD<T>::clear(){
	n=0;
}

template <class T>
void VD<T>::resize(int nuevo_tam){
	T *aux=new T[nuevo_tam];
	int minimo=(n<nuevo_tam)? n:nuevo_tam;
	for(int i=0; i<minimo; i++)
		aux[i]=datos[i];
	reservados=nuevo_tam;
	n=minimo;
	delete []datos;
	datos=aux;
}

template <class T>
void VD<T>::Copiar(const VD<T> &original){
	reservados=original.reservados;
	n=original.n;
	datos=new T[reservados];
	for(int i=0; i<n; i++)
		datos[i]=original.datos[i];
}

template <class T>
VD<T>::VD(int tam){
	reservados=tam;
	n=0;
	datos=new T[tam];
}

template <class T>
VD<T>::VD(const VD<T> &original){
	Copiar(original);
}

template <class T>
VD<T>::~VD(){
	if(datos!=0){
		delete []datos;
		datos = 0;
	}
}

template <class T>
VD<T> & VD<T>::operator=(const VD<T> &original){
	if(this!=&original){
		if(datos!=0)
			delete[] datos;
		Copiar(original);
	}
	return *this;
}

template <class T>
void VD<T>::Insertar(const T & dato, int pos) {
	if(n == reservados)
		resize(2*reservados);
	for(int i = n; i > pos; i--) 	
		datos[i] = datos[i-1];
	datos[pos] = dato;
	n++;
}

template <class T>
void VD<T>::Borrar(int pos) {
	for(int i = pos; i < n-1; i++) 
		datos[i] = datos[i+1];
	n--;
	if(n < reservados/4)
		resize(reservados/2);
}





