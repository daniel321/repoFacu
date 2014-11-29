package org.tcp1.ejemplo4.main;

import org.tcp1.ejemplo4.buffer.Buffer;
import org.tcp1.ejemplo4.hilos.Consumidor;
import org.tcp1.ejemplo4.hilos.Productor;

public class Ejemplo4 {

	private static final int VUELTAS = 5;

	public static void main(String[] args) {
		
		Buffer buffer = new Buffer ();
		
		Thread productor = new Thread ( new Productor(buffer,VUELTAS) );
		Thread consumidor = new Thread ( new Consumidor(buffer,VUELTAS) );
		
		productor.start ();
		consumidor.start ();

		try {
			productor.join ();
			consumidor.join ();
			System.out.println ( "*** Fin del programa" );
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

}
