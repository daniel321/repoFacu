package org.tcp1.ejemplo3.buffer;

public class Buffer {

	private int valor;
	
	public Buffer () {
		valor = 0;
	}

	public synchronized int getValor () {
		try {
			wait ();
		} catch ( InterruptedException e ) {}
		return valor;
	}

	public synchronized void setValor ( int valor ) {
		this.valor = valor;
		notifyAll ();
	}

}
