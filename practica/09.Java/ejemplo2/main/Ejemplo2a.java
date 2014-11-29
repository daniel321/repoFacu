package org.tcp1.ejemplo2.main;

import org.tcp1.ejemplo2.contador.Contador;
import org.tcp1.ejemplo2.hilos.Hilo;

public class Ejemplo2a {

	public static void main ( String[] args ) {
		Contador contador = new Contador ();
		
		Thread hilo1 = new Thread ( new Hilo(contador) );
		Thread hilo2 = new Thread ( new Hilo(contador) );
		
		hilo1.start ();
		hilo2.start ();
	}

}
