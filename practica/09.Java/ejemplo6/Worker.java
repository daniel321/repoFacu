package org.tcp1.ejemplo6;

import java.util.Arrays;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

public class Worker implements Runnable {
	
	private int posicionDelBuffer;
	private float[] buffer;
	private int cantidad;
	private CyclicBarrier barrera;
	private int vueltas;

	public Worker ( int posicion,float[] bufferInicial,int cantidad,CyclicBarrier barrera,int vueltas ) {
		this.posicionDelBuffer = posicion;
		this.buffer = bufferInicial;
		this.cantidad = cantidad;
		this.barrera = barrera;
		this.vueltas = vueltas;
	}

	@Override
	public void run () {
		for ( int i=0;i<this.vueltas;i++ ) {
			
			// se obtiene el resultado del calculo
			float resultado = procesarBuffer ();
			
			try {
				// se imprimen los datos en pantalla
				System.out.println ( "Vuelta " + (i+1) + " - Worker " + this.posicionDelBuffer + " - Buffer inicial " + Arrays.toString(this.buffer) + " - Resultado = " + resultado );
				
				// se espera a que todos terminen el calculo antes de actualizar el buffer
				this.barrera.await ();
				
				// se guarda el valor obtenido en la posicion correspondiente para la siguiente vuelta
				this.buffer[this.posicionDelBuffer] = resultado;
				
				// se espera a que todos terminen de escribir en el buffer antes de iniciar la siguiente vuelta
				this.barrera.await ();
				
			} catch ( InterruptedException e ) {
				e.printStackTrace();
			} catch ( BrokenBarrierException e ) {
				e.printStackTrace ();
			}
		}
	}
	
	private float procesarBuffer () {
		float resultado = 0;
		for ( int i=0;i<this.cantidad;i++ )
			resultado += this.buffer[i];
		
		return resultado;
	}

}
