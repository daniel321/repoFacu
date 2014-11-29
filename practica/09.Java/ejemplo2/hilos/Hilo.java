package org.tcp1.ejemplo2.hilos;

import java.util.Random;

import org.tcp1.ejemplo2.contador.Contador;

public class Hilo implements Runnable {
	
	private Contador contador;
	
	public Hilo ( Contador contador ) {
		this.contador = contador;
	}

	@Override
	public void run () {
		for ( int i=0;i<10;i++ ) {
			Random rand = new Random ();
			int cantidad = rand.nextInt ( 100 );
			System.out.println ( "Hilo " + Thread.currentThread().getId() + " incrementa en " + cantidad + " el contador" );
			contador.incrementar ( cantidad );
		}
	}

}
