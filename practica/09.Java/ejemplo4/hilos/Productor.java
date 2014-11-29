package org.tcp1.ejemplo4.hilos;

import org.tcp1.ejemplo4.buffer.Buffer;

public class Productor implements Runnable {
	
	private Buffer buffer;
	private int vueltas;
	
	public Productor ( Buffer b,int vueltas ) {
		this.buffer = b;
		this.vueltas = vueltas;
	}

	@Override
	public void run() {
		
		for ( int i=0;i<vueltas;i++ ) {
			
			// calcular valor random para guardar en el buffer
			int aGuardar = calcularRandom ( 1,100 );
			
			// calcular valor random a dormir
			int aDormir = calcularRandom ( 1,10 );
			
			buffer.setValor ( aGuardar );
			System.out.println ( "Productor: valor guardado en el buffer = " + aGuardar + " (tiempo a dormir = " + aDormir + ")" );
			
			try {
				Thread.sleep ( aDormir*1000 );
			} catch (InterruptedException e) {}
			
		}
	}

	private int calcularRandom ( int max,int min ) {
		return (int)(Math.random()*(max-min))+min;		
	}
}
