package org.tcp1.ejemplo3.hilos;

import org.tcp1.ejemplo3.buffer.Buffer;

public class HiloLector implements Runnable {
	
	private Buffer buffer;
	private int vueltas;
	
	public HiloLector ( Buffer buffer,int vueltas ) {
		this.buffer = buffer;
		this.vueltas = vueltas;
	}

	@Override
	public void run () {
		for ( int i=0;i<vueltas;i++ ) {
			System.out.println ( "HiloLector: esperando por el dato" );
			int dato = buffer.getValor ();
			System.out.println ( "HiloLector: dato leido del buffer = " + dato );
		}
	}

}
