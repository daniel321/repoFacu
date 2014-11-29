package org.tcp1.ejemplo1.hilos;

public class HiloThread extends Thread {

	public void run () {
		System.out.println ( "Hola, soy el hilo " + Thread.currentThread().getId() + " y heredo de Thread" );
		System.out.println ( "Termine" );
	}
}
