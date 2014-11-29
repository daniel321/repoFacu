package org.tcp1.ejemplo1.hilos;

public class HiloRunnable implements Runnable {

	@Override
	public void run () {
		System.out.println ( "Hola, soy el hilo " + Thread.currentThread().getId() + " e implemento Runnable" );
		System.out.println ( "Termine" );
	}

}
