package org.tcp1.ejemplo4.hilos;

import org.tcp1.ejemplo4.buffer.Buffer;

public class Consumidor implements Runnable {
	
	private Buffer buffer;
	private int vueltas;
	
	public Consumidor ( Buffer b,int vueltas ) {
		this.buffer = b;
		this.vueltas = vueltas;
	}

	@Override
	public void run() {
		
		for ( int i=0;i<vueltas;i++ ) {
			
			// calcular valor random a dormir
			int aDormir = calcularRandom ( 1,10 );
			
			// leer el valor del buffer
			int valor = buffer.getValor ();
			System.out.println ( "Consumidor: valor leido del buffer = " + valor + " (tiempo a dormir = " + aDormir + ")" );
			
			try {
				Thread.sleep ( aDormir*1000 );
			} catch (InterruptedException e) {}
		}
	}

	private int calcularRandom ( int max,int min ) {
		return (int)(Math.random()*(max-min))+min;		
	}
}
