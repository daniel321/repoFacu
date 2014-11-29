package org.tcp1.ejemplo2.contador;

public class Contador {

	private int valor;
	
	public Contador () {
		valor = 0;
	}

	public int getValor() {
		return valor;
	}

	public void incrementar ( int cantidad ) {
		synchronized ( this ) {
			this.valor += cantidad;
			System.out.println ( "Contador: valor actual = " + this.valor );
		}
	}
	
	public static synchronized void escribirMensaje ( String mensaje ) {
		System.out.println ( "Mensaje del Contador" );
	}
}
