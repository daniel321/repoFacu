package org.tcp1.ejemplo1.main;

import org.tcp1.ejemplo1.hilos.HiloRunnable;
import org.tcp1.ejemplo1.hilos.HiloThread;

public class Ejemplo1 {

	public static void main ( String[] args ) {
		HiloThread hilo1 = new HiloThread ();
		Thread hilo2 = new Thread ( new HiloRunnable() );
		
		hilo1.start ();
		hilo2.start ();
	}

}
