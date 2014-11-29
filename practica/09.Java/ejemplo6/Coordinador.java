package org.tcp1.ejemplo6;

import java.util.concurrent.CyclicBarrier;

public class Coordinador {
	
	private static final int CANTIDAD_VUELTAS = 5;
	
	private float buffer[];
	private int cantidad;
	private CyclicBarrier barrera;

	public Coordinador ( float[] bufferInicial,int cantidad ) {
		this.barrera = new CyclicBarrier ( cantidad );
		this.buffer = bufferInicial;
		this.cantidad = cantidad;
	}
	
	public void procesar () {
		
		Thread workers[] = new Thread[this.cantidad];
		
		// se lanzan los hilos
		for ( int i=0;i<this.cantidad;i++ ) {
			workers[i] = new Thread ( new Worker(i,buffer,cantidad,barrera,CANTIDAD_VUELTAS) );
			workers[i].start ();
		}
		
		// se espera a que terminen los hilos
		for ( int i=0;i<this.cantidad;i++ ) {
			try {
				workers[i].join ();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		
		System.out.println ( "Coordinador: se termino el trabajo" );
	}

}
