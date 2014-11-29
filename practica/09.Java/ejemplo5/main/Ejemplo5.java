package org.tcp1.ejemplo5.main;

import org.tcp1.ejemplo5.buffer.Buffer;
import org.tcp1.ejemplo5.buffer.Semaforo;
import org.tcp1.ejemplo5.hilos.Consumidor;
import org.tcp1.ejemplo5.hilos.Productor;

public class Ejemplo5 {

	private static final int VUELTAS = 5;

	public static void main ( String[] args ) {
		
		Buffer buffer = new Buffer ();
		Semaforo semaforoLectura = new Semaforo ( 0 );
		Semaforo semaforoEscritura = new Semaforo ( 1 );
		
		Thread thrProductor = new Thread ( new Productor(buffer,semaforoLectura,semaforoEscritura,VUELTAS) );
		Thread thrConsumidor = new Thread ( new Consumidor(buffer,semaforoLectura,semaforoEscritura,VUELTAS) );
		
		thrProductor.start ();
		thrConsumidor.start ();

		try {
			thrProductor.join ();
			thrConsumidor.join ();
			System.out.println ( "*** Fin del programa" );
		} catch ( InterruptedException e ) {
			e.printStackTrace();
		}
	}

}
