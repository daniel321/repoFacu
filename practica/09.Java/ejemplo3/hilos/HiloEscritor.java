package org.tcp1.ejemplo3.hilos;

import java.util.Random;

import org.tcp1.ejemplo3.buffer.Buffer;

public class HiloEscritor implements Runnable {
	
	private Buffer buffer;
	private int vueltas;
	
	public HiloEscritor ( Buffer buffer,int vueltas ) {
		this.buffer = buffer;
		this.vueltas = vueltas;
	}

	@Override
	public void run () {
		for ( int i=0;i<vueltas;i++ ) {
			int aDormir = this.calcularRandom ( 10 );
			System.out.println ( "HiloEscritor: durmiendo " + aDormir + " segundos" );
			
			try {
				Thread.sleep ( 1000 * aDormir );
			} catch ( InterruptedException e ) {}
			
			int dato = this.calcularRandom ( 100 );
			System.out.println ( "HiloEscritor: escribiendo " + dato + " en el buffer" );
			buffer.setValor ( dato );
		}
	}
	
	private int calcularRandom ( int maximo ) {
		Random rand = new Random ();
		return rand.nextInt ( maximo );
	}

}
