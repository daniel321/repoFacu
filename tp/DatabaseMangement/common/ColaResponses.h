#ifndef COLARESP_H_
#define COLARESP_H_

#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <string>

template <class T,class T2> class ColaResp {
	private:
		key_t	clave;
		int	id;

	public:
		ColaResp ( const std::string& archivo,const char letra );
		~ColaResp();
		int escribir ( const T& dato ) const;
		int leer ( const int tipo,T* buffer ) const;
		int escribir ( const T2& dato ) const;
		int leer ( const int tipo,T2* buffer ) const;
		int destruir () const;
};

template <class T, class T2> ColaResp<T,T2> :: ColaResp ( const std::string& archivo,const char letra ) {
	this->clave = ftok ( archivo.c_str(),letra );
	if ( this->clave == -1 )
		perror ( "Error en ftok" );

	this->id = msgget ( this->clave,0777|IPC_CREAT );
	if ( this->id == -1 )
		perror ( "Error en msgget" );
}

template <class T, class T2> ColaResp<T,T2> :: ~ColaResp () {
}

template <class T, class T2> int ColaResp<T,T2> :: destruir () const {
	int resultado = msgctl ( this->id,IPC_RMID,NULL );
	return resultado;
}

template <class T, class T2> int ColaResp<T,T2> :: escribir ( const T& dato ) const {
	int resultado = msgsnd ( this->id,static_cast<const void*>(&dato),sizeof(T)-sizeof(long),0 );
	return resultado;
}

template <class T, class T2> int ColaResp<T,T2> :: escribir ( const T2& dato ) const {
	int resultado = msgsnd ( this->id,static_cast<const void*>(&dato),sizeof(T2)-sizeof(long),0 );
	return resultado;
}

template <class T, class T2> int ColaResp<T,T2> :: leer ( const int tipo,T* buffer ) const {
	int resultado = msgrcv ( this->id,static_cast<void *>(buffer),sizeof(T)-sizeof(long),tipo,0 );
	return resultado;
}

template <class T, class T2> int ColaResp<T,T2> :: leer ( const int tipo,T2* buffer ) const {
	int resultado = msgrcv ( this->id,static_cast<void *>(buffer),sizeof(T2)-sizeof(long),tipo,0 );
	return resultado;
}

#endif /* COLA_H_ */
