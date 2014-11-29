package org.tcp1.ejemplo4.buffer;

public class Buffer {
	
	private int valor;
	private boolean disponible;
	
	public Buffer () {
		valor = 0;
		disponible = false;
	}

	public synchronized int getValor () {
		
		// el consumidor toma el monitor
		while ( disponible == false ) {
			try {
				wait ();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		
		disponible = false;
		notifyAll ();
		
		return valor;
		// el consumidor libera el monitor
	}
	
	public synchronized void setValor ( int v ) {
		
		// el productor toma el monitor
		while ( disponible == true ) {
			try {
				wait ();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		
		valor = v;
		disponible = true;
		notifyAll ();
		// el productor libera el monitor
	}
}
