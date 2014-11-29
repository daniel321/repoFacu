package org.tcp1.ejemplo2.main;

import org.tcp1.ejemplo2.contador.Contador;
import org.tcp1.ejemplo2.hilos.Hilo;

public class Ejemplo2b {

	public static void main ( String[] args ) {
		Contador contador1 = new Contador ();
		Contador contador2 = new Contador ();
		
		Thread hilo1 = new Thread ( new Hilo(contador1) );
		Thread hilo2 = new Thread ( new Hilo(contador2) );
		
		hilo1.start ();
		hilo2.start ();
	}
}
