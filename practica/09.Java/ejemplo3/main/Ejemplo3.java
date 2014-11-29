package org.tcp1.ejemplo3.main;

import org.tcp1.ejemplo3.buffer.Buffer;
import org.tcp1.ejemplo3.hilos.HiloEscritor;
import org.tcp1.ejemplo3.hilos.HiloLector;

public class Ejemplo3 {

	private static final int VUELTAS = 5;

	public static void main ( String[] args ) {
		Buffer buffer = new Buffer ();
		
		Thread hiloLector = new Thread ( new HiloLector(buffer,VUELTAS) );
		Thread hiloEscritor = new Thread ( new HiloEscritor(buffer,VUELTAS) );
		
		hiloLector.start ();
		hiloEscritor.start ();
	}

}
