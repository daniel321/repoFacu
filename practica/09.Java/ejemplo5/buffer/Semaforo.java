package org.tcp1.ejemplo5.buffer;

public class Semaforo {

	private int valor;
	
	public Semaforo ( int valorInicial ) {
		valor = valorInicial;
	}
	
	/**
	 * Resta una unidad al valor del semaforo
	 */
	public synchronized void p () {
		
		// si el valor del semaforo es 0 => el hilo debe bloquearse
		while ( valor == 0 )
			try {
				// el hilo libera el monitor y se bloquea
				wait ();
			} catch ( InterruptedException e ) {
				e.printStackTrace();
			}
			
		// cuando el valor no es cero => se resta una unidad
		valor --;
	}
	
	/**
	 * Suma una unidad al valor del semaforo
	 */
	public synchronized void v () {
		// se suma una unidad al semaforo y se notifica a los hilos que estaban bloqueados
		valor ++;
		notifyAll ();
	}
}
